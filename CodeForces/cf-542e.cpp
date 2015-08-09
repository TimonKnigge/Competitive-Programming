#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <functional>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef long long ll;
const int INF = 2000000000;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int n, m;
	cin >> n >> m;
	vvi e(n, vi());
	for (int i = 0; i < m; ++i) {
		int a, b; cin >> a >> b; a--; b--;
		e[a].push_back(b);
		e[b].push_back(a);
	}

	int com = 0;
	vi co(n, -1), ceid(n, -1);
	vvi ce;
	for (int i = 0; i < n; ++i) {
		if (co[i] != -1) continue;
		ce.push_back(vi());
		queue<int> q;
		q.push(i);
		while (!q.empty()) {
			int u = q.front(); q.pop();
			if (co[u] != -1) continue;
			co[u] = com;
			ce[com].push_back(u);
			ceid[u] = ce[com].size() - 1;
			for (int v : e[u]) {
				q.push(v);
			}
		}
		com++;
	}


	vb check(com, false);
	vi sz(com, 0);
	bool bpt = false;
	for (int i = 0; i < n && !bpt; ++i) {
		if (check[co[i]]) continue;
		int M = 0;
		check[co[i]] = true;
		vi dist(ce[co[i]].size(), INF);
		for (int u = 0; u < ce[co[i]].size(); ++u) {
			queue<int> q;
			q.push(u);
			dist.assign(ce[co[i]].size(), -1);
			dist[u] = 0;
			while (!q.empty() && !bpt) {
				int v = q.front(); q.pop();
				M = max(M, dist[v]);
				for (int vv : e[ce[co[i]][v]]) {
					int vvv = ceid[vv];
					if (dist[vvv] == -1) {
						dist[vvv] = dist[v] + 1;
						q.push(vvv);
					} else {
						if (abs(dist[vvv] - dist[v]) % 2 == 0) {
							bpt = true;
							break;
						}
					}
				}
			}
//			cerr << co[i] << ": " << endl;
//			for (int x = 0; x < ce[co[i]].size(); ++x) {
//				cerr << ce[co[i]][x] << " -> " << dist[x] <<endl;
//			}
		}
		sz[co[i]] = M;
	}

	if (bpt) cout << "-1" << endl;
	else {
		ll sum = 0;
		for (int i = 0; i < com; ++i) sum += sz[i];
		cout << sum << endl;
	}

	return 0;
}
