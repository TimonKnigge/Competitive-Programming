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
	ll n;
	cin >> n;

	vi ans(n+1, 1);
	vvi divs(n+2);
	for (ll d = 1; d <= n+1; ++d)
		for (ll p = d; p <= n+1; p += d)
			divs[p].push_back(d);

	for (ll x = 2; x < n; ++x)
		for (ll d1 : divs[x-1])
			for (ll d2 : divs[x])
				if (d1*d2 <= n && x < d1*d2 && x > ans[d1*d2])
					ans[d1*d2] = x;

	cout << std::accumulate(ans.begin()+1, ans.begin()+n+1, 0LL) << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout << fixed << setprecision(12);
	
	solve();
	
	return 0;
}
