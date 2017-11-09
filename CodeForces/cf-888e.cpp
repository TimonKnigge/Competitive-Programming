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
	
	int n; ll m;
	cin >> n >> m;
	vi a(n, 0LL);
	for (ll &v : a) cin >> v;

	if (n == 1) {
		cout << (a[0] % m) << endl;
		return 0;
	}

	int mid = (n/2);
	vi l, r;
	for (int i = 0; i < (1<<mid); ++i) {
		ll v = 0LL;
		for (int j = 0; j < mid; ++j) if ((i>>j)&1) v += a[j];
		l.push_back(v%m);
	}
	for (int i = 0; i < (1<<(n-mid)); ++i) {
		ll v = 0LL;
		for (int j = 0; j < (n-mid); ++j) if ((i>>j)&1) v += a[mid+j];
		r.push_back(v%m);
	}

	sort(l.begin(), l.end());
	ll ans = 0LL;
	for (ll v : r) {
		for (int k = 1; k <= 2; ++k) {
			auto it = lower_bound(l.begin(), l.end(), k*m-v);
			if (it != l.begin()) {
				--it;
				ans = max(ans, (v + *it) % m);
			}
		}
	}
	cout << ans << endl;
	
	return 0;
}
