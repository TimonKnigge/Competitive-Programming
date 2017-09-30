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

constexpr ll MOD = 1e9+7;

void padd(ll &v, ll a, ll b) {
	v = (v + a * b % MOD) % MOD;
}

void dfs(int u, int p, vvi &E, int m, int k, int x, vector<vvi> &dp) {
	for (int v : E[u]) if (v != p) dfs(v, u, E, m, k, x, dp);
	for (int t = 0; t < 3; ++t) {
		dp[t][0][u] = 1LL;
		for (int v : E[u]) {
			if (v == p) continue;
			vi ndp(x+1, 0LL);
			for (int c = x; c >= 0; --c)
					for (int ct = 0; ct + c <= x; ++ct) {
						ll tot = 0LL;
						if (t == 0)
							tot = dp[0][ct][v]+dp[1][ct][v]+dp[2][ct][v];
						if (t == 1)
							tot = dp[0][ct][v];
						if (t == 2)
							tot = dp[0][ct][v]+dp[2][ct][v];
						padd(ndp[c+ct], dp[t][c][u], tot);
					}
			for (int i = 0; i <= x; ++i) dp[t][i][u] = ndp[i];
		}
		ll amt = (t == 0 ? k-1 : (t == 1 ? 1 : m-k));
		for (int c = 0; c <= x; ++c)
			dp[t][c][u] = (dp[t][c][u] * amt) % MOD;
	}
	for (int i = x - 1; i >= 0; --i) swap(dp[1][i][u], dp[1][i+1][u]);
	dp[1][0][u] = 0;
/*
	cerr << "Printing for " << u << endl;
	for ( int t = 0; t < 3; ++t ) {
		cerr << " type " << t << endl;
		for (int i = 0; i <= x; ++i)
			cerr << "  " << i << " -> " << dp[t][i][u] << endl;
	}
*/
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n, m;
	cin >> n >> m;

	vvi E(n, vi());
	for (int i = 0; i + 1 < n; ++i) {
		int u, v;
		cin >> u >> v;
		--u; --v;
		E[u].push_back(v);
		E[v].push_back(u);
	}

	int k, x;
	cin >> k >> x;

	vector<vvi> dp(3, vvi(x+1, vi(n, 0LL)));
	dfs(0, -1, E, m, k, x, dp);

	ll ans = 0LL;
	for (int i = 0; i <= x; ++i)
		for (int t = 0; t < 3; ++t)
			ans = (ans + dp[t][i][0]) % MOD;
	cout << ans << endl;
	
	return 0;
}
