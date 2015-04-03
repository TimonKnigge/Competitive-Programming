#include <iostream>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <vector>
#include <queue>

using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef long long ll;
typedef vector<bool> vb;

#ifndef _MSC_VER
#define scanf_s scanf
#endif

typedef pair<int, ii> iii;
// Adjacency list given as (endpoint, weight)
ll prim(vvii& adj, vii& tree) {
	ll tc = 0; vb intree(adj.size(), false);
	priority_queue<iii, vector<iii>, greater<iii> > pq;

	intree[0] = true;
	for (ii e : adj[0]) pq.push(iii(e.second, ii(0, e.first)));

	while (!pq.empty()) {
		int c = pq.top().first; ii e = pq.top().second; pq.pop();
		if (intree[e.second]) continue;
		intree[e.second] = true;
		tc += c; tree.push_back(ii(min(e.first, e.second), max(e.first, e.second)));
		for (ii e2 : adj[e.second]) {
			if (!intree[e2.first])
				pq.push(iii(e2.second, ii(e.second, e2.first)));
		}
	}

	return tc;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n, m;
	while (true) {
		cin >> n >> m;
		if (n == 0 && m == 0) break;

		if (m == 0) {
			cout << "Impossible" << endl;
			continue;
		}

		// Read the graph
		vvii edges(n);
		for (int i = 0; i < m; ++i) {
			int u, v, w;
			cin >> u >> v >> w;
			edges[u].push_back(ii(v, w));
			edges[v].push_back(ii(u, w));			
		}

		// Run Prim's
		vii tree;
		ll cost = prim(edges, tree);

		// Do output
		if (tree.size() < n - 1) cout << "Impossible" << endl;
		else {
			sort(tree.begin(), tree.end());
			cout << cost << endl;
			for (int i = 0; i < n - 1; ++i) cout << tree[i].first << ' ' << tree[i].second << '\n';
		}
	}

	return 0;
}