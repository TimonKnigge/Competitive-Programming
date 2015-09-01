#include <iostream> // strings/streams
#include <string>
#include <sstream>
#include <vector> // datastructures
#include <list>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <bitset>
#include <tuple> // quick compare
#include <cstdio> // utils
#include <numeric>
#include <iterator>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <cassert>

using namespace std;
using ll = long long;
using ii = pair<int,int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
constexpr int  INF = 1e9+1; // < 1e9 - -1e9
constexpr ll LLINF = 1e18+1;

struct Tarjan {
	vvi &edges;
	int V, counter = 0, C = 0;
	vi index, lowlink;
	vb instack;
	stack<int> st;
	Tarjan(vvi &e) : edges(e), V(e.size()), index(V, -1),
		lowlink(V, -1), instack(V, false) { }

	void visit(int u, vi &com) {
		lowlink[u] = index[u] = counter++;
		st.push(u); instack[u] = true;
		for (auto &&v : edges[u]) {
			if (index[v] == -1) {
				visit(v, com);
				lowlink[u] = min(lowlink[u], lowlink[v]);
			} else if (instack[v]) {
				lowlink[u] = min(lowlink[u], index[v]);
			}
		}
		if (lowlink[u] == index[u]) {
			while(true) {
				int v = st.top(); st.pop();
				instack[v] = false;
				com[v] = C;
				if (u == v) break;
			}
			C++;
		}
	}
	int find_sccs(vi &com) {
		com.assign(V, -1);
		C = 0;
		for (int u = 0; u < V; ++u) if (index[u] == -1) visit(u, com);
//	else cout << u << " - "<< n[u] << endl;
		return C;
	}
};

struct TwoSAT {
	int n;
	vvi imp;
	Tarjan tj;
	TwoSAT(int _n) : n(_n), imp(2 * _n, vi()), tj(imp) { }
	void add_implies(int c1, bool v1, int c2, bool v2) {
		int u = 2 * c1 + (v1 ? 1 : 0);
		int v = 2 * c2 + (v2 ? 1 : 0);
		imp[u].push_back(v);
		if ((u^1) != v) imp[v^1].push_back(u^1);
	}
	void add_or(int c1, bool v1, int c2, bool v2) {
		add_implies(c1, !v1, c2, v2);
	}
	void add_xor(int c1, bool v1, int c2, bool v2) {
		add_or(c1, v1, c2, v2);
		add_or(c1, !v1, c2, !v2);
	}
	void add_true(int c1, bool v1) {
		add_implies(c1, !v1, c1, v1);
	}

	bool solvable() {
		vi com;
		tj.find_sccs(com);
		for (int i = 0; i < n; ++i) {
//			cout << (i / 4) << ' ' << (i % 4) << ' ' << com[2*i] << ' ' << com[2*i+1] << endl;
			if (com[2 * i] == com[2 * i + 1]) return false;
		}
		return true;
	}
};

#define LEFT(i) (4*(i))
#define RIGHT(i) (4*(i)+1)
#define UP(i) (4*(i)+2)
#define DOWN(i) (4*(i)+3)

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int T; cin >> T; for (int t = 1; t <= T; ++t) {
	
	int n, m;
	cin >> n >> m;
	vector< vector<int> > board(n, vector<int>(m, 0));
	int id = 1, white = 0, black = 0;
	for (int i = 0; i<n; ++i) {
		string s; cin >> s;
		for (int j = 0; j < m; ++j) {
			if (s[j] == '.') continue;
			if (s[j] == 'W') {
				board[i][j] = id++;
				white++;
			}
			if (s[j] == 'B') {
				board[i][j] = -1;
				black++;
			}
		}
	}

	if (black * 2 != white) {
		cout << "NO" << endl;
		continue;
	}
	if (black == 0) {
		cout << "YES" << endl;
		continue;
	}
	
	TwoSAT ts(4 * (1 + id));
	bool sat = true;
	for (int i = 0; sat && i < n; ++i) {
		for (int j = 0; sat && j < m; ++j) {
			if (board[i][j] == 0) continue;
			if (board[i][j] > 0) {
				id = board[i][j];
				ts.add_or(LEFT(id), false, RIGHT(id), false);
				ts.add_or(LEFT(id), false, UP(id), false);
				ts.add_or(LEFT(id), false, DOWN(id), false);
				ts.add_or(UP(id), false, DOWN(id), false);
				ts.add_or(UP(id), false, RIGHT(id), false);
				ts.add_or(DOWN(id), false, RIGHT(id), false);
			}
			if (board[i][j] == -1) {
				// Find left
				bool L = (i > 0 && board[i-1][j] > 0);
				bool R = (i < n-1 && board[i+1][j] > 0);
				if (!L && !R) sat = false;
				if (L && !R) ts.add_true(RIGHT(board[i-1][j]), true);
				if (!L && R) ts.add_true(LEFT(board[i+1][j]), true);
				if (L && R) ts.add_xor(RIGHT(board[i-1][j]), true, LEFT(board[i+1][j]), true);
				
				// Find up
				bool U = (j > 0 && board[i][j-1] > 0);
				bool D = (j < m-1 && board[i][j+1] > 0);
				if (!U && !D) sat = false;
				if (U && !D) ts.add_true(DOWN(board[i][j-1]), true);
				if (!U && D) ts.add_true(UP(board[i][j+1]), true);
				if (U && D) ts.add_xor(DOWN(board[i][j-1]), true, UP(board[i][j+1]), true);
			}
		}
	}

	sat = sat && ts.solvable();
	cout << (sat ? "YES" : "NO") << endl;
	
	} return 0;
}
