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

constexpr int INF = 1000000010;
constexpr ll LLINF = 9000000000000000010LL;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	ll p, q, r;
	cin >> n >> p >> q >> r;

	ll best[3] = {-LLINF, -LLINF, -LLINF};
	while (n--) {
		ll a;
		cin >> a;
		best[0] = max(best[0], p * a);
		best[1] = max(best[1], best[0] + q * a);
		best[2] = max(best[2], best[1] + r * a);
	}
	cout << best[2] << endl;
	
	return 0;
}
