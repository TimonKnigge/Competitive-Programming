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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	vvi C(n, vi(n));
	for (vi &c : C) for (ll &v : c) cin >> v;

	constexpr ll MOD = 1e9+7;

	vvi dp(n, vi(n, 0LL));
	for (int l = n - 1; l >= 0; --l) {
		dp[l][l] = 1LL;
		for (int r = l + 1; r < n; ++r) {
			if (!C[l][r]) continue;
			ll cnt = 0LL;
			for (int i = l; i < r; ++i)
				cnt = (cnt + dp[l][i] * dp[i+1][r]) % MOD;
			for (int i = r; i < n; ++i)
				dp[l][i] = (dp[l][i] + cnt * dp[r][i]) % MOD;
		}
	}

	cout << dp[0][n-1] << endl;
	
	return 0;
}
