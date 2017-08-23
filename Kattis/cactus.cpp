#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
using ll = long long;
using ld = long double;
using ii = pair<ll, ll>;
using vi = vector<ll>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

template<class T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<class TIn, class TOut = null_type>
using order_tree = tree<TIn, TOut, less<TIn>, rb_tree_tag,
	tree_order_statistics_node_update>;

constexpr int INF = 1000000010;
constexpr ll LLINF = 1000000000000000010LL;

void dfs(int u, vvi &E, vi &addsub, vi &subsub, vi &vlof, vi &col,
		bool &cross) {
	col[u] = 1LL;
	for (int v : E[u]) {
		if (col[v] == 0LL) {
			// new tree edge
			dfs(v, E, addsub, subsub, vlof, col, cross);
			addsub[u] += addsub[v];
		} else if (col[v] == 1LL) {
			// back edge wooo
			addsub[u]++;
			subsub[v]++;
		} else if (col[v] == 2LL) {
			// cross edge booo
			cross = true;
		}
	}
	addsub[u] -= subsub[u];
	vlof[u] += addsub[u];
	col[u] = 2LL;
}
void dfs2(int u, vvi &E, vi &r) {
	r[u] = 1LL;
	for (int v : E[u]) if (!r[v]) dfs2(v, E, r);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, m;
	cin >> n >> m;
	vvi E(n, vi()), RE(n, vi());
	while (m--) {
		int u, v;
		cin >> u >> v;
		E[u].push_back(v);
		RE[v].push_back(u);
	}

	vi addsub(n, 0LL), subsub(n, 0LL), color(n, 0LL), rch(n, 0LL), vlof(n, 0LL);
	bool cross = false;
	dfs(0, E, addsub, subsub, vlof, color, cross);
	dfs2(0, RE, rch);

	bool answer = !cross;
	for (int i = 0; i < n; ++i)
		answer = answer && color[i] == 2LL && rch[i] == 1LL && vlof[i] == ll(i != 0);
	cout << (answer ? "YES" : "NO") << endl;

	return 0;
}
