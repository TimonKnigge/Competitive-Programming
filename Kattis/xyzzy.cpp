#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<int> vi;
typedef vector<long long> vll;
typedef vector<vector<pair<int, long long> > > vvii;

const long long INF = 2000000000000;

void bellmann_ford(vvii &edges, int source,  vll &dist, vector<bool> &n_cycle) {
	dist.assign(edges.size(), INF);
	n_cycle.assign(edges.size(), false);
	dist[source] = 0;
	for (int iter = 0; iter < edges.size() - 1; ++iter) {
		for (int u = 0; u < edges.size(); ++u)
			if (dist[u] < INF)
				for (auto &e : edges[u])
					if (dist[u] + e.second < 0)
						dist[e.first] = min(dist[e.first], dist[u] + e.second);
	}
	bool ch = true;
	while (ch) {
		ch = false;
		for (int u = 0; u < edges.size(); ++u) {
			if (dist[u] == INF) continue;
			for (auto &e : edges[u]) {
				if (dist[e.first] > dist[u] + e.second && !n_cycle[e.first] && (dist[u] + e.second < 0)) {
					dist[e.first] = -INF;
					ch = true;
					n_cycle[e.first] = true;
				}
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	while (true) {

	int n; 
	cin >> n;
	if (n == -1) break;
	vvii e(n + 1, vector<pair<int, long long> >());
	vector<long long> w(n + 1, 0);
	for (int i = 1; i <= n; ++i) {
		cin >> w[i];

		int m;
		cin >> m;
		for (int j = 0; j < m; ++j) {
			int k; cin >> k;
			e[i].push_back({k, 0});
		}
	}
	e[0].push_back({1, -w[1] - 100});
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < e[i].size(); ++j)
			e[i][j].second = -w[e[i][j].first];
	}
	
	vll dist;
	vector<bool> n_cycle;
	bellmann_ford(e, 0, dist, n_cycle);
	
	if (n_cycle[n] || dist[n] < 0)
		cout << "winnable\n";
	else cout << "hopeless\n";
	
	}
	cout << flush;
	return 0;
}
