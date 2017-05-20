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
using ii = pair<ll, ll>;
using vi = vector<ll>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

int k;
using T = pair<ii, pair<ii, ii>>;
T combine(T l, T r) {
	return {{l.first.first+r.first.first,
		 l.first.second+r.first.second},
		{{l.second.first.first+r.second.first.first,
		  l.second.first.second+r.second.first.second},
		 {l.second.second.first+r.second.second.first,
		  l.second.second.second+r.second.second.second}}};
}
T addone(T v) {
	ll tot, vals[5];
	tot = v.first.first;
	vals[0] = v.first.second;
	vals[1] = v.second.first.first;
	vals[2] = v.second.first.second;
	vals[3] = v.second.second.first;
	vals[4] = v.second.second.second;
	tot += vals[0];
	for (int i = k - 1; i > 0; --i)
		swap(vals[i], vals[i - 1]);
	return {{tot, vals[0]}, {{vals[1], vals[2]}, {vals[3], vals[4]}}};
}
void pt(char c, int u, T t) {
	cout << c << ' ' << u << ": ((" << t.first.first << "," << t.first.second;
	cout << "), ((" << t.second.first.first << ",";
	cout << t.second.first.second << "),(";
	cout << t.second.second.first << ",";
	cout << t.second.second.second << ")))" << endl;
}

void dfs1(int u, int p, vvi &E, vector<T> &subtree) {
	subtree[u] = {{0LL, 1LL}, {{0LL, 0LL}, {0LL, 0LL}}};
	for (ll v : E[u]) {
		if (v == p) continue;
		dfs1(v, u, E, subtree);
		subtree[u] = combine(subtree[u], addone(subtree[v]));
	}
//	pt('s', u, subtree[u]);
}

void dfs2(int u, int p, vvi &E, vector<T> &subtree, T top, ll &ans) {
	int N = E[u].size();	
	vector<T> suffix(N, {{0LL, 0LL}, {{0LL, 0LL}, {0LL, 0LL}}});
	for (int i = N - 1; i >= 0; --i) {
		int v = E[u][i];
		if (v != p)
			suffix[i] = addone(subtree[v]);
		if (i + 1 < N)
			suffix[i] = combine(suffix[i], suffix[i + 1]);
	}
//	pt('t', u, top);
	
	// Ourselves:
	T self = combine(top, suffix[0]);
	ans += self.first.first;
	top = combine(top, {{0LL, 1LL}, {{0LL, 0LL}, {0LL, 0LL}}});
	for (int i = 0; i < N; ++i) {
		if (E[u][i] == p) continue;
		T down = top;
		if (i + 1 < N)
			down = combine(down, suffix[i + 1]);
		dfs2(E[u][i], u, E, subtree, addone(down), ans);
		top = combine(top, addone(subtree[E[u][i]]));
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n >> k;
	
	vvi E(n, vi());
	for (int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		--a; --b;
		E[a].push_back(b);
		E[b].push_back(a);
	}
	
	T def = {{0LL, 0LL}, {{0LL, 0LL}, {0LL, 0LL}}};
	vector<T> subtree(n, def);
	dfs1(0, -1, E, subtree);
	
	ll ans = 0LL;
	dfs2(0, -1, E, subtree, def, ans);
	
	ans /= 2LL;
	cout << ans << endl;
	
	return 0;
}
