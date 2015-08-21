#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

typedef long long ll;
typedef pair<int, ll> il;
typedef pair<ll, int> li;
typedef vector<ll> vl;
typedef vector<il> vil;
typedef vector<vil> vvil;

const ll LLINF = 2e18;

void dijkstra(vvil &e, int s, vl &d) {
	d.assign(e.size(), LLINF);
	priority_queue<li, vector<li>, greater<li> > pq;
	pq.push({0, s});
	d[s] = 0;
	while (!pq.empty()) {
		ll w = pq.top().first;
		int u = pq.top().second; 
		pq.pop();
		if (d[u] < w) continue;
		for (il vx : e[u]) {
			int v = vx.first;
			ll x = vx.second;
			if (d[u] + x < d[v]) {
				d[v] = d[u] + x;
				pq.push({d[v], v});
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	while (true) {
		int n, m, q, s;
		cin >> n >> m >> q >> s;
		if (n == 0) break;
		vvil e(n, vil());
		for (int i = 0; i < m; ++i) {
			int u, v; ll w;
			cin >> u >> v >> w;
			e[u].push_back({v, w});
		}
	
		vl dist;
		dijkstra(e, s, dist);
		for (int i = 0; i < q; ++i) {
			int a;
			cin >> a;
			if (dist[a] == LLINF)
				cout << "Impossible\n";
			else cout << dist[a] << '\n';
		}
		cout << endl;
	}

	return 0;
}
