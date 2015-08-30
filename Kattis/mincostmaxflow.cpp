#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cassert>
#include <set>

using namespace std;

typedef long long ll;

const ll LLINF = 9e18;

struct FlowNetwork {
	struct edge {
		int v, rev; ll cap, cost, flo;
		edge (int _v, ll _cap, ll _cost) : v(_v),
			cap(_cap), cost(_cost), flo(0) { }
	};
	int V;
	vector< vector<edge> > e;
	FlowNetwork(int V) : V(V) {
		e.assign(V, vector<edge>());
	}
	void add_edge(int u, int v, ll uv_cap, ll uv_cost) {
		e[u].push_back(edge(v, uv_cap,  uv_cost));
		e[v].push_back(edge(u,      0, -uv_cost));
		e[u].back().rev = e[v].size() - 1;
		e[v].back().rev = e[u].size() - 1;
	}
	pair<ll, ll> mcmf(int s, int t);
};

vector<ll> d;

typedef pair<ll, int> li;
pair<ll, ll> FlowNetwork::mcmf(int s, int t) {
	ll flow = 0, cost = 0;
	vector<pair<int, int> > p(V, {-1, -1});
	vector<ll> pot(V, 0);
	d.assign(V, -1);
	
//	// Set potentials
//	for (int it = 0; it < V - 1; ++it) {
//		for (int u = 0; u < V; ++u) {
//			if (d[u] == -1) continue;
//			for (int i = 0; i < int(e[u].size()); ++i) {
//				edge &uv = e[u][i];
//				int v = uv.v;
//				if (d[v] == -1 || d[v] > d[u] + uv.cost)
//					d[v] = d[u] + uv.cost;
//			}
//		}
//	}
//	for (int i = 0; i < V; ++i)
//		if (d[i] != -1) pot[i] = d[i];

	while (true) {
		d.assign(V, -1);
		d[s] = 0;
		priority_queue<li, vector<li>, greater<li> > pq;
		pq.push({0, s});
		while (!pq.empty()) {
			int u = pq.top().second; ll ww = pq.top().first; pq.pop();
			if (ww > d[u]) continue;
			for (int i = 0; i < int(e[u].size()); ++i) {
				edge &uv = e[u][i];
				if (uv.cap == uv.flo) continue;
				int v = uv.v;
				ll w = d[u] + uv.cost + pot[u] - pot[v];
				if (d[v] == -1 || w < d[v]) {
					p[v] = {u, i};
					d[v] = w;
					pq.push({d[v], v});
				}
			}
		}
		if (d[t] == -1) break;
		int u = t;
		ll cap = LLINF;
		while (u != s) {
			edge &uv = e[p[u].first][p[u].second];
			cap = min(cap, uv.cap - uv.flo);
			u = p[u].first;
		}
		if (cap == 0) break;
		u = t;
		flow += cap;
		while (u != s) {
			edge &uv = e[p[u].first][p[u].second];
			edge &vu = e[uv.v][uv.rev];
			uv.flo += cap;
			vu.flo -= cap;
			cost += cap * uv.cost;
			u = p[u].first;
		}
		for (int i = 0; i < V; ++i)
			if (d[i] != -1) pot[i] += d[i];
	}
	
	return {flow, cost};
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, m, s, t;
	cin >> n >> m >> s >> t;
	FlowNetwork fn(n);
	
	for (int i = 0; i < m; ++i) {
		int u, v, w, c;
		cin >> u >> v >> c >> w;
		fn.add_edge(u, v, c, w);
	}

	auto ans = fn.mcmf(s, t);
	cout << ans.first << ' ' << ans.second << endl;
	
	return 0;
}
