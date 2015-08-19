#include <iostream>
#include <iomanip>
#include <vector>	       
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <bitset>
#include <algorithm>
#include <functional>
#include <string>
#include <string.h>  // Include for memset!
#include <complex>
#include <random>
#define _USE_MATH_DEFINES
#include <math.h>

const int INF = 2000000000;	                 // 9
const long long LLINF = 9000000000000000000LL;  // 18
const long double LDINF = 1e300;

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<bool> vb;
typedef long long ll;
typedef long double ld;

void dfs1(int u, vvi &edges, vb &marked, stack<int> &st) {
	marked[u] = true;
	for (int v : edges[u]) {
		if (marked[v]) continue;
		dfs1(v, edges, marked, st);
	}
	st.push(u);
}
int counter = 0;
void dfs2(int u, vvi &edges, vb &marked, vi &component) {
	marked[u] = true;
	for (int v : edges[u]) {
		if (marked[v]) continue;
		dfs2(v, edges, marked, component);
	}
	component[u] = counter;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	string alph;
	cin >> alph;
	int n, m;
	cin >> n >> m;
	
	// pos i true = 2 * i, pos i false = 2 * i + 1
	vvi edges(2 * n, vi()), edges_rev(2 * n, vi());
	vvi adj(2 * n, vi(2 * n, false));
	for (int i = 0; i < m; ++i) {
		int _x, _y;
		char _xs, _ys;
		cin >> _x >> _xs >> _y >> _ys;
		bool xt = (_xs == 'V'), yt = (_ys == 'V');
		int u = 2 * (_x - 1) + (xt ? 1 : 0);
		int v = 2 * (_y - 1) + (yt ? 1 : 0);
		edges[u].push_back(v);
		if ((v^1) != u) edges[v^1].push_back(u^1);
		edges_rev[v].push_back(u);
		if ((v^1) != u) edges[u^1].push_back(v^1);
		adj[u][v] = adj[v^1][u^1] = true;
	}
	string str;
	cin >> str;

	vb marked(2 * n, false);
	stack<int> st;
	for (int i = 0; i < 2 * n; ++i) {
		if (!marked[i]) dfs1(i, edges, marked, st);
	}
	marked.assign(2 * n, false);
	vi component(2 * n, -1);
	counter = 0;
	while (!st.empty()) {
		int u = st.top(); st.pop();
		if (!marked[u]) { counter++; dfs2(u, edges_rev, marked, component); }
	}

	bool sat = true;
	for (int i = 0; i < n; ++i) {
		if (component[2 * i] == component[2 * i + 1])
			sat = false;
	}

	if (sat) {
		vvi bycomp(counter - 1, vi());
		for (int i = 0; i < 2 * n; ++i) bycomp[component[i]].push_back(i);

		for (int b = 0; b < 2 * n; ++b)
		for (int a = 0; a < 2 * n; ++a)
		for (int c = 0; c < 2 * n; ++c)
			adj[a][c] = adj[a][c] || (adj[a][b] && adj[b][c]);
		sat = true;
		vb canV(n, false), canC(n, false);
		for (int i = 0; i < n; ++i) {
			canV[i] = !adj[2 * i + 1][2 * i];
			canC[i] = !adj[2 * i][2 * i + 1];
			if (!canV[i] && !canC[i]) sat = false;
		}
		if (!sat) { cout << -1 << endl; return 0; }
	
		for (int j = n - 1; j >= 0; --j) {
			int v = int(str[j] - 'a') + 1;
			while (v < alph.length() && ((alph[v] == 'V' && !canV[j]) || (alph[v] == 'C' && !canC[j]))) v++;
			if (v >= alph.length()) {
				for (int i = j; i < n; ++i) str[i] = 'a';
				if (j == 0) { sat = false; break; }
				j--;
			} else {
				str[j] = char(v);
			}
			
			
		}
		if (sat) cout << str << endl;
		else cout << -1 << endl;
		
	} else cout << -1 << endl;
	
	return 0;
}
