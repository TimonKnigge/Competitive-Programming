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

int dx[4] = { 0, 1, 0,-1};
int dy[4] = {-1, 0, 1, 0};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, m, k;
	cin >> n >> m >> k;
	
	vii pts(k, {0, 0});
	map<ii, int> mp;
	for (int i = 0; i < k; ++i)
		cin >> pts[i].first >> pts[i].second,
		--pts[i].first, --pts[i].second,
		mp[pts[i]] = i;
	
	vvii G(n + m + k, vii());
	for (int i = 0; i < k; ++i) {
		ll x = pts[i].first, y = pts[i].second;
		
		// Rows
		if (x > 0) {
			G[n+m+i].push_back({x-1, 1});
			G[x-1].push_back({n+m+i, 0});
		}
		G[n+m+i].push_back({x, 1});
		G[x].push_back({n+m+i, 0});
		if (x+1<n) {
			G[n+m+i].push_back({x+1, 1});
			G[x+1].push_back({n+m+i, 0});
		}
		
		// Columns
		if (y > 0) {
			G[n+m+i].push_back({n+y-1, 1});
			G[n+y-1].push_back({n+m+i, 0});
		}
		G[n+m+i].push_back({n+y, 1});
		G[n+y].push_back({n+m+i, 0});
		if (y+1<m) {
			G[n+m+i].push_back({n+y+1, 1});
			G[n+y+1].push_back({n+m+i, 0});
		}
		
		// Move
		for (int j = 0; j < 4; ++j) {
			ll nx = x+dx[j], ny = y+dy[j];
			auto it = mp.find({nx, ny});
			if (it != mp.end())
				G[n+m+i].push_back({n+m+it->second, 0});
		}
	}
	
	priority_queue<ii, vector<ii>, greater<ii>> pq;
	vi d(n+m+k, INF);
	d[n+m] = 0LL; pq.push({d[n+m], n+m});
	while (!pq.empty()) {
		ii pr = pq.top(); pq.pop();
		if (pr.first != d[pr.second]) continue;
		for (ii ed : G[pr.second]) {
			ll nd = pr.first + ed.second;
			if (nd < d[ed.first]) {
				d[ed.first] = nd;
				pq.push({d[ed.first], ed.first});
			}
		}
	}
	
	ll ans = min(d[n - 1], d[n + m - 1]);
	if (mp.find({n - 1, m - 1}) != mp.end())
		ans = min(ans, d[n+m+mp[{n - 1, m - 1}]]);
	if (ans == INF)
		cout << -1 << endl;
	else	cout << ans << endl;
	
	return 0;
}
