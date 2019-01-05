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
	int n;
	cin >> n;

	vi p(n, -1);
	for (int i = 1; i < n; ++i) cin >> p[i], --p[i];
	vi a(n);
	for (ll &v : a) cin >> v;

	vvi ch(n);
	ll ans = 0LL;
	for (int i = n-1; i >= 0; --i) {
		if (a[i] < 0 && !ch[i].empty()) {
			ll mxc = LLINF;
			for (int c : ch[i]) mxc = min(mxc, a[c]);
			a[i] = mxc;
			for (int c : ch[i]) ans += a[c] - mxc;
		} else if (a[i] >= 0) {
			for (int c : ch[i]) {
				if (a[c] < a[i]) {
					cout << -1 << endl;
					return;
				} else {
					ans += a[c] - a[i];
				}
			}
		}
		
		if (i > 0 && (a[i] >= 0 || !ch[i].empty()))
			ch[p[i]].push_back(i);
		else if (i == 0)
			ans += a[i];
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
