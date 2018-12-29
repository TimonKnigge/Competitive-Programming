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

__int128 f(ll n) {
	return __int128(n) * (n + 1) * 2 - __int128(n) * n;
}
__int128 g(ll n) {
	return __int128(n) * (n + 1) / 2LL;
}

// http://oeis.org/A006451/b006451.txt
ll sol[40] = {
 2,		5,		15,		32,		90,
 189,	527,	1104,	3074,	6437,
 17919,	37520,
 104442,218685,	608735,	1274592,3547970,
 7428869,		20679087,		43298624,
 120526554,		252362877,		702480239,
 1470878640,	4094354882,		8572908965,
 23863649055,	49966575152,	139087539450,
 291226541949,	810661587647,	1697392676544,
 4724881986434,	9893129517317,	27538630330959,
 57661384427360,160506899999322,336075177046845,
 935502769664975,				1958789677853712,
};

void solve() {
	ll ans = 0LL;
	for (size_t i = 0; i < 40; ++i) {
		ll l = 1LL, r = sol[i];
		__int128 t = g(sol[i]);
		while (l < r) {
			ll m = (l + r) / 2;
			if (f(m) < t)
				l = m + 1;
			else
				r = m;
		}
		ans += l;
		cerr << i+1 << "\t" << l << "\t" << ans << endl;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout << fixed << setprecision(12);
	
	solve();
	
	return 0;
}
