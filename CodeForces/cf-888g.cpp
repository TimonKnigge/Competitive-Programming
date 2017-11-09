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

ll minxor(const vi &a, int e, int l1, int r1, int l2, int r2) {
	if (l1 >= r1 || l2 >= r2) return LLINF;
	if (e < 0) return 0LL;
	int m1 = l1, m2 = l2;
	while (m1 < r1 && ((a[m1]>>e)&1) == 0) ++m1;
	while (m2 < r2 && ((a[m2]>>e)&1) == 0) ++m2;
	if ((l1 < m1 && l2 < m2) || (m1 < r1 && m2 < r2)) {
		return min(minxor(a, e-1, l1, m1, l2, m2),
					minxor(a, e-1, m1, r1, m2, r2));
	} else {
		return min(minxor(a, e-1, l1, m1, m2, r2),
					minxor(a, e-1, m1, r1, l2, m2)) + (1LL<<e);
	}
}

ll recurse(const vi &a, int e, int l, int r) {
	if (e < 0 || r - l <= 1) return 0LL;
	int m = l;
	while (m < r && ((a[m]>>e)&1) == 0) ++m;
	ll cost = recurse(a, e-1, l, m) + recurse(a, e-1, m, r);
	if (l < m && m < r) {
		cost += minxor(a, e-1, l, m, m, r) + (1LL<<e);
	}
	return cost;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	vi a(n, 0LL);
	for (ll &v : a) cin >> v;
	sort(a.begin(), a.end());

	cout << recurse(a, 30, 0, n) << endl;
	
	return 0;
}
