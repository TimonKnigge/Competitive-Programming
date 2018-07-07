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
	
	int n, U;
	cin >> n >> U;
	vi E(n);
	for (ll &e : E) cin >> e;

	ld opt = -1e300;
	for (int l = 0, r = 0; l < n; ++l) {
		while (r + 1 < n && E[r+1] - E[l] <= U) ++r;
		if (l + 2 <= r)
			opt = max(opt, ld(E[r] - E[l+1]) / ld(E[r] - E[l]));
	}

	if (opt < -10)
		cout << -1 << endl;
	else
		printf("%.10lf\n", double(opt));
	
	return 0;
}
