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
	vector<vector<int>> D(N+1);
	for (int d = 1; d <= N; ++d)
		for (int m = d; m <= N; m += d)
			D[m].push_back(d);

	ll ans = (N-1)/2;
	unordered_set<ll> st;
	for (ll a = 2LL; a < N; ++a) {
		st.clear();
		for (ll d1 : D[a-1]) {
			for (ll d2 : D[a+1]) {
				ll bmc = d1*d2;
				ll bpc = ((a-1)/d1)*((a+1)/d2);
				if ((bmc+bpc)&1) continue;
				ll b = (bmc + bpc) / 2;
				ll c = bpc - b;
				if (b > 0 && c > 0 && a > 0) {
					ll abc = a+b+c;
					ll m = max(a, max(b, c));
					if (abc-m > m)
						if (abc <= N)
							if (a <= c && c <= b)
								st.insert(b + 1000000000LL * c);
				}
			}
		}
		ans += (ll)st.size();
		if (a % 50000 == 0)
			cout << ans << endl;
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
