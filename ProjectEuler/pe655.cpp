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
using vd = vector<ld>;

template<class T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<class TIn, class TOut = null_type>
using order_tree = tree<TIn, TOut, less<TIn>, rb_tree_tag,
	tree_order_statistics_node_update>;
// .find_by_order(int r) and .order_of_key(TIn v)

constexpr int INF = 2000000010;
constexpr ll LLINF = 9000000000000000010LL;
constexpr ld PI = acos(-1);

constexpr ll M = 10000019LL;
vi p10;

void solve() {
	p10.push_back(1);
	for (int p = 1; p <= 40; ++p)
		p10.push_back(10 * p10.back() % M);
	
	vvi dp(35, vi(M));
	for (int d = 0; d < 10; ++d)
		dp[1][d]++,
		dp[2][d*11]++;

	ll ans = 0LL;
	for (int d = 1; d+2 <= 32; ++d)
		for (int m = 0; m < M; ++m) {
			ll v = p10[d+1]+1;
			for (int k = 0; k < 10; ++k) {
				dp[d+2][(10*m + v*k)%M] += dp[d][m];
				if ((10*m + v*k)%M == 0 && k > 0)
					ans += dp[d][m];
			}
		}
	cout << ans << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout << fixed << setprecision(12);
	
	solve();
	
	return 0;
}
