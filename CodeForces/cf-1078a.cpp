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

ld mhd(ld x1, ld y1, ld x2, ld y2) {
	return abs(x1-x2) + abs(y1-y2);
}
ld ecd(ld x1, ld y1, ld x2, ld y2) {
	return sqrt(max(ld(0.0), (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2)));
}

void solve() {
	ll a, b, c;
	cin >> a >> b >> c;

	ll x1, y1, x2, y2;
	cin >> x1 >> y1 >> x2 >> y2;

	ld ans = mhd(x1, y1, x2, y2);

	if (b != 0) {
		ans = min(ans,
			mhd(x1, y1, x1, ld(-c-a*x1)/ld(b))
			+ ecd(x1, ld(-c-a*x1)/ld(b), x2, ld(-c-a*x2)/ld(b))
			+ mhd(x2, ld(-c-a*x2)/ld(b), x2, y2));
	}
	if (a != 0) {
		ans = min(ans,
			mhd(x1, y1, ld(-c-b*y1)/ld(a), y1)
			+ ecd(ld(-c-b*y1)/ld(a), y1, ld(-c-b*y2)/ld(a), y2)
			+ mhd(ld(-c-b*y2)/ld(a), y2, x2, y2));
	}
	if (a != 0 && b != 0) {
		ans = min(ans,
			mhd(x1, y1, x1, ld(-c-a*x1)/ld(b))
			+ ecd(x1, ld(-c-a*x1)/ld(b), ld(-c-b*y2)/ld(a), y2)
			+ mhd(ld(-c-b*y2)/ld(a), y2, x2, y2));
		ans = min(ans,
			mhd(x1, y1, ld(-c-b*y1)/ld(a), y1)
			+ ecd(ld(-c-b*y1)/ld(a), y1, x2, ld(-c-a*x2)/ld(b))
			+ mhd(x2, ld(-c-a*x2)/ld(b), x2, y2));
	}
	printf("%.15lf\n", double(ans));
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout << fixed << setprecision(12);
	
	solve();
	
	return 0;
}
