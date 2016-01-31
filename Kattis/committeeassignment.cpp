#include <iostream> 
#include <cstdio>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <bitset>
#include <numeric>
#include <iterator>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <cassert>

using namespace std;
using ll = long long;
using ld = long double;
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

int fmap(int &id, map<string, int> &mp, string &s) {
	auto it = mp.find(s);
	if (it != mp.end()) return it->second;
	else {
		mp.insert({s, id});
		++id;
		return id - 1;
	}
}

int recurse(int u, vvi &el, vi &col, int N, int maxC) {
	if (u == N) return maxC;
	
	int mn = INF;
	for (int c = 0; c < min(mn, N); ++c) {
		bool f = true;
		for (int i = 0, s = int(el[u].size()); f && i < s; ++i) {
			f = f && c != col[el[u][i]];
		}
		if (f) {
			col[u] = c;
			mn = min(mn, recurse(u + 1, el, col, N, max(maxC, c)));
		}
	}
	return mn;
}

void reorder(vvi &e) {
	int N = int(e.size());
	
	int u = 0;
	for (int v = 1; v < N; ++v)
		if (e[u].size() < e[v].size()) u = v;
	
	vi M(N, -1);
	int id = 0;
	
	stack<int> q;
	for (int i = 0; i < N; ++i) if (e[i].size() > 0) q.push(i);
	q.push(u);
	
	while (!q.empty()) {
		int a = q.top();
		q.pop();
		if (M[a] >= 0) continue;
		M[a] = id;
		++id;
		for (int b : e[a]) if (M[b] < 0) q.push(b);
	}
	vvi e2(id, vi());
	
	for (int a = 0; a < N; ++a)
		for (int b : e[a])
			if (M[a]>M[b]) e2[M[a]].push_back(M[b]);
	e = e2;
}

bool solve() {
	int N, M;
	cin >> N >> M;
	if (N == 0 && M == 0) return false;
	
	int id = 0;
	map<string, int> idmap;
	vvi el(N, vi());
	
	while (M--) {
		string n1, n2;
		cin >> n1 >> n2;
		int id1 = fmap(id, idmap, n1);
		int id2 = fmap(id, idmap, n2);
		el[id1].push_back(id2);
		el[id2].push_back(id1);
	}
//	cerr << "Read names." << endl;
	reorder(el);
//	cerr << "Reordered."<<endl;
	
	vi col(N, -1);
	cout << (1 + recurse(0, el, col, int(el.size()), 0)) << endl;
	
	return true;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	while (solve()) ;
	
	return 0;
}
