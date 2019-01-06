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

	vi spf(N+1);
	iota(spf.begin(), spf.end(), 0LL);
	for (ll n = 2; n <= N; ++n) {
		if (spf[n] != n) continue;
		for (ll v = n*n; v <= N; v += n)
			if (spf[v] == v)
				spf[v] = n;
	}

	map<ii, ll> best;
	for (ll n = 2; n <= N; ++n) {
		set<ll> P;
		ll nn = n;
		while (nn > 1) P.insert(spf[nn]), nn /= spf[nn];
		if (P.size() == 2)
			best[{*P.begin(), *P.rbegin()}] = n;
	}

	ll ans = 0LL;
	for (auto it : best) ans += it.second;
	cout << ans << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout << fixed << setprecision(12);
	
	solve();
	
	return 0;
}
