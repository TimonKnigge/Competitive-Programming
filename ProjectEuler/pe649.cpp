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

void solve() {
	ll n, c;
	cin >> n >> c;

	vector<vector<int>> B(9, vector<int>(9));
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			unordered_set<int> seen;
			for (int d : {2,3,5,7}) {
				if (i-d >= 0) seen.insert(B[i-d][j]);
				if (j-d >= 0) seen.insert(B[i][j-d]);
			}
			while (seen.find(B[i][j]) != seen.end()) ++B[i][j];
			cerr << ' ' << B[i][j];
		}
		cerr << endl;
	}

	vi cnt(8, 0);
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			cnt[B[i][j]] += (max(n - i + 8, 0LL) / 9) * (max(n - j + 8, 0LL) / 9);
		}
	}
	for (int j = 0; j < 8; ++j)
		cerr << "cnt[" << j << "] = " << cnt[j] << endl;

	ll ans = 0LL;
	constexpr ll M = 1000000000;
	for (ll &v : cnt) v %= M;
	vvi dp(1<<8, vi(c+1, 0LL));
	dp[0][0] = 1LL;
	for (int k = 0; k < c; ++k) {
		for (int m = 0; m < (1<<8); ++m) {
			ll &cur = dp[m][k];
			if (!cur) continue;
			for (int n = 0; n < 8; ++n) {
				ll &nxt = dp[m^(1<<n)][k+1];
				nxt = (nxt + cur * cnt[n] % M) % M;
			}
		}
	}
	for (int m = 0; m < (1<<8); ++m) {
		int x = 0;
		for (int j = 0; j < 8; ++j)
			if ((m>>j)&1)
				x ^= j;
		if (!x)
			ans = (ans + dp[m][c]) % M;
	}

	ll total = 1LL, nn = std::accumulate(cnt.begin(), cnt.end(), 0LL);
	assert(n * n % M == nn % M);
	for (int k = 0; k < c; ++k) total = total * nn % M;
	cout << ans << " or " << (total+M-ans)%M << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	solve();
	
	return 0;
}
