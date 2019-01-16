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
	int N;
	cin >> N;
	vector<vector<vector<bool>>> W[8];
	for (int d = 0; d < 8; ++d) {
		W[d].assign(N+1, vector<vector<bool>>(N+1, vector<bool>(N+1, false)));
		W[d][0][0][0] = true;
	}

	ll ans = 0LL;
	for (int i = 0; i <= N; ++i) {
		cout << i << "/" << N << endl;
		for (int j = 0; j <= N; ++j)
			for (int k = 0; k <= N; ++k) {
				if (!i && !j && !k) continue;
				bool cr0 = false;
				for (int d = 1; d < 8; ++d) {
					int ni = i-(d&1);
					int nj = j-((d>>1)&1);
					int nk = k-((d>>2)&1);
					if (ni < 0 || nj < 0 || nk < 0) continue;
					if (W[d][ni][nj][nk]) cr0 = true, W[d][i][j][k] = true;
				}
				if (!cr0) {
					if (i <= j && j <= k)
						ans += i+j+k;
					for (int d = 0; d < 8; ++d)
						W[d][i][j][k] = true;
				}
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
