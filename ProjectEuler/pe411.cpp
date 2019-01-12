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

ll solve(const vii &pts) {
	int n = (int)pts.size();
	vector<pair<int, int>> E;
	for (int i = 0; i < n; ++i) {
		int x = pts[i].first, y = pts[i].second;
		E.push_back({x, y});
	}
	sort(E.begin(), E.end());
	E.erase(unique(E.begin(), E.end()), E.end());
	cerr << "E.size() is " << E.size() << endl;

	int c = 0;
	set<pair<int, int>> level;
	for (auto xy : E) {
		auto it = level.lower_bound({xy.second, int(1e9)});
		if (it != level.end())
			level.erase(it);
		level.insert({xy.second, c++});
	}

	return (ll)level.size();
}

ll S(ll n) {
	vii pts;
	set<ii> seen;
	ll nx = 1%n, ny = 1%n;
	for (ll i = 0; i <= 2*n; ++i) {
		if (seen.find({nx, ny}) == seen.end()) {
			pts.push_back({nx, ny});
			seen.insert({nx, ny});
			nx = 2*nx%n;
			ny = 3*ny%n;
		} else break;
	}
	return solve(pts);
}

void solve() {
	cout << "S(22) = " << S(22) << endl;
	cout << "S(123) = " << S(123) << endl;
	cout << "S(10000) = " << S(10000) << endl;
	ll ans = 0LL;
	for (ll k = 1; k <= 30; ++k) {
		cerr << "at k = " << k << '\t' << ans << endl;
		ans += S(k*k*k*k*k);
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
