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

constexpr int INF = 2000000010;
constexpr ll LLINF = 9000000000000000010LL;

constexpr ll MOD = 1e9+7;

// Color the subtree at u with colors in 
// {1..k} and u with 1.
ll col(int u, int k, const vvi &C) {
	ll ways = 1LL;
	for (int v : C[u]) {
		ll vways = col(v, k, C);
		ways = (k-1) * ways % MOD * vways % MOD;
	}
	return ways;
}

ll cnt(int k, const vvi &C) {
	return k * col(0, k, C) % MOD;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, k;
	cin >> n >> k;
	
	vvi C(n);
	for (int i = 1, p; i < n; ++i)
		cin >> p, C[p].push_back(i);

	// Inverses
	vi I(n+1, 1LL);
	for (int i = 2; i <= n; ++i)
		I[i] = (MOD - (MOD/i) * I[MOD%i] % MOD) % MOD;

	vi f(n+1, 1LL), fi(n+1, 1LL);
	for (int i = 2; i <= n; ++i)
		f[i] = (i * f[i-1]) % MOD,
		fi[i] = (I[i] * fi[i-1]) % MOD;

	ll ans = 0LL;
	for (int e = k; e > 1; --e) {
		ll nck = f[k] * fi[e] % MOD * fi[k-e] % MOD;
		if ((k - e) % 2 == 1)
			nck = (MOD - nck) % MOD;
		ans = (ans + nck * cnt(e, C) % MOD) % MOD;
	}

	cout << ans << endl;
	
	return 0;
}
