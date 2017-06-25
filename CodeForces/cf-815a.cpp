#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ii = pair<ll, ll>;
using vi = vector<ll>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

constexpr int INF = 2000000000;
constexpr ll LLINF = 9000000000000000000;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, m;
	cin >> n >> m;
	vvi a(n, vi(m, 0LL));
	for (vi &r : a) for (ll &v : r) cin >> v;
	
	vii ans;

	if (n < m) {
		for (int r = 0; r < n; ++r) {
			ll m = LLINF;
			for (ll v : a[r]) m = min(m, v);
			if (m > 0LL) {
				for (ll &v : a[r]) v -= m;
				while (m--) ans.push_back({0, r+1});
			}
		}
	}
	for (int c = 0; c < m; ++c) {
		ll m = LLINF;
		for (vi &r : a) m = min(m, r[c]);
		if (m > 0LL) {
			for (vi &r : a) r[c] -= m;
			while (m--) ans.push_back({1, c+1});
		}
	}
	for (int r = 0; r < n; ++r) {
		ll m = LLINF;
		for (ll v : a[r]) m = min(m, v);
		if (m > 0LL) {
			for (ll &v : a[r]) v -= m;
			while (m--) ans.push_back({0, r+1});
		}
	}
	
	bool s = true;
	for (vi &r : a) for (ll v : r) s = s && v == 0LL;
	if (!s) cout << -1 << endl;
	else {
		cout << ans.size() << endl;
		for (ii pr : ans)
			cout << (pr.first ? "col " : "row ") << pr.second << '\n';
	}
	
	return 0;
}
