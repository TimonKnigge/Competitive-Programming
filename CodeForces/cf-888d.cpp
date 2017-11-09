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

vi comp(ll n) {
	vi ret;

	// 0
	ret.push_back(1);

	// 1
	ret.push_back(0);

	// 2
	ret.push_back(n * (n - 1) / 2LL);

	// 3
	ret.push_back(2LL * n * (n - 1) * (n - 2) / 6LL);

	// 4
	ret.push_back(n * (n - 1) * (n - 2) * (n - 3) / 24LL * (6LL + 3LL));

	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, k;
	cin >> n >> k;

	vi v = comp(n);

	ll ans = 0LL;
	for (int i = 0; i <= k; ++i) ans += v[i];
	cout << ans << endl;
	
	return 0;
}
