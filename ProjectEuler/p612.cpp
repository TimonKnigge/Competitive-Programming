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

constexpr ll MOD = 1000267129LL;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	ll fac[21], nCk[21][21], dp[21][21];
	fac[0] = fac[1] = 1LL;
	for (ll n = 2LL; n <= 20LL; ++n)
		fac[n] = (n * fac[n - 1]) % MOD;
	for (ll i = 0LL; i <= 20LL; ++i)
		nCk[0][i] = 0LL, nCk[i][0] = 1LL;
	for (ll n = 1LL; n <= 20LL; ++n)
		for (ll k = 1LL; k <= 20LL; ++k)
			nCk[n][k] = (nCk[n - 1][k] + nCk[n - 1][k - 1]) % MOD;
	for (ll n = 0LL; n <= 20LL; ++n)
		dp[n][0] = ll(n == 0LL),
		dp[n][1] = ll(n != 0LL),
		dp[0][n] = ll(n == 0LL);
	for (ll n = 1LL; n <= 20LL; ++n)
		for (ll d = 2LL; d <= 20LL; ++d) {
			dp[n][d] = 0LL;
			for (ll k = 1LL; k <= n; ++k)
				dp[n][d] = (dp[n][d] + nCk[n-1][k-1] * dp[n-k][d-1]) % MOD;
		}

	int N;
	cin >> N;

	vi C(1 << 10, 0LL);
	for (int ds = 1; ds <= N; ++ds) {
		for (int m = 1; m < (1 << 10); ++m) {
			for (int d = 1; d < 10; ++d) {
				int f = __builtin_popcount(m&~(1<<d));
				for (int e = 0; e + f <= 10; ++e) {
					ll add = nCk[10-f][e]*dp[ds-1][e+f] % MOD * fac[f+e] % MOD;
					C[m] = (C[m] + add) % MOD;
				}
			}
		}
	}

	ll ans = 0LL, twoinv = (MOD + 1) / 2;
	for (int m = 1; m < (1 << 10); ++m) {
		ll pw = (__builtin_popcount(m) % 2 == 1 ? 1 : MOD-1);
		ll prs = (C[m] * (C[m] - 1) % MOD + MOD) % MOD;
		ans = (ans + pw * prs % MOD) % MOD;
	}
	cout << (ans * twoinv % MOD) << endl;

	return 0;
}
