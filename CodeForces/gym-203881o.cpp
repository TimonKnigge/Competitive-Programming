#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, m, t, k;
	cin >> n >> m >> t >> k;
	vector< vector< pair<int, int> > > e(n, vector< pair<int, int> >());
	for (int i = 0; i < m; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		u--; v--;
		e[u].push_back({v, w});
		e[v].push_back({u, w});
	}

	vector<int> dist(n, 5e7);
	vector<int> disc(n, 0);
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int> > > pq;
	for (int i = 0; i < t; ++i) {
		int a;
		cin >> a;
		a--;
		if (dist[a] == 5e7) disc[i]++;
		dist[a] = 0;
		pq.push({0, a});
		while (!pq.empty()) {
			auto _uw = pq.top(); pq.pop();
			pair<int, int> uw = {_uw.second, _uw.first};
			if (dist[uw.first] == uw.second) {
				for (auto vw : e[uw.first]) {
					if (dist[uw.first] + vw.second < dist[vw.first] && dist[uw.first] + vw.second < k) {
						if (dist[vw.first] == 5e7)
							disc[i]++;
						dist[vw.first] = dist[uw.first] + vw.second;
						pq.push({dist[vw.first], vw.first});
					}
				}
			}
		}
	}
	
	int s = n;
	for (int i = 0; i < t; ++i) {
		s -= disc[i];
		cout << s << '\n';
	}
	cout  << flush;
	
	return 0;
}
