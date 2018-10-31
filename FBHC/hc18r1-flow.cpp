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

void solve(int t) {
	int N;
	cin >> N;
	string G[3];
	cin >> G[0] >> G[1] >> G[2];

	vi dp[3];
	dp[0].assign(N+1, 0);
	dp[1].assign(N+1, 0);
	dp[2].assign(N+1, 0);
	dp[0][0] = 1LL;

	for (int i = 0; i < N; ++i) {
		dp[0][i] %= MOD;
		dp[1][i] %= MOD;
		dp[2][i] %= MOD;
		if (G[0][i] == '.' && G[1][i] == '.')
			dp[0][i+1] += dp[1][i],
			dp[1][i+1] += dp[0][i];
		if (G[2][i] == '.' && G[1][i] == '.')
			dp[2][i+1] += dp[1][i],
			dp[1][i+1] += dp[2][i];
	}

	cout << "Case #" << t << ": " << dp[2][N] << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int T;
	cin >> T;
	for (int t = 1; t <= T; ++t) solve(t);
	cout << flush;
	
	return 0;
}
