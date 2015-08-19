#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<bool> vb;

struct AdjEdge { int v; ll weight; };
struct Edge { int u; int v; };
struct PQ { ll weight; Edge e; };
bool operator>(const PQ &l, const PQ &r) { return l.weight > r.weight; }
ll prim(vector<vector<AdjEdge> > &adj) {
	ll tc = 0; vb intree(adj.size(), false);
	priority_queue<PQ, vector<PQ>, greater<PQ> > pq;
	intree[0] = true;
	for (auto &e : adj[0]) pq.push({e.weight, {0, e.v}});
	while (!pq.empty()) {
		auto &top = pq.top();
		ll c = top.weight; auto e = top.e; pq.pop();
		if (intree[e.v]) continue;
		intree[e.v] = true; tc += c;
		for (auto &e2 : adj[e.v])
			if (!intree[e2.v]) pq.push({e2.weight, {e.v, e2.v}});
	}
	return tc;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	vector<ll> x(n, 0), y(n, 0), z(n, 0);
	vector< pair<ll, pair<ll, pair<ll, int> > > > 
		byx(n, {0, {0, {0, 0}}}), 
		byy(n, {0, {0, {0, 0}}}), 
		byz(n, {0, {0, {0, 0} } });
	for (int i = 0; i < n; ++i) {
		cin >> x[i] >> y[i] >> z[i];
		byx[i] = {x[i], {y[i], {z[i], i}}};
		byy[i] = {y[i], {z[i], {x[i], i}}};
		byz[i] = {z[i], {x[i], {y[i], i}}};
	}
	sort(byx.begin(), byx.end());
	sort(byy.begin(), byy.end());
	sort(byz.begin(), byz.end());
	
	vector< vector<AdjEdge> > adj(n, vector<AdjEdge>());
	for (int i = 1; i < n; ++i) {
		ll d = byx[i].first - byx[i - 1].first;
		int u = byx[i].second.second.second,
		    v = byx[i - 1].second.second.second;
		adj[u].push_back({v, d});
		adj[v].push_back({u, d});
		d = byy[i].first - byy[i - 1].first;
		u = byy[i].second.second.second;
		v = byy[i - 1].second.second.second;
		adj[u].push_back({v, d});
		adj[v].push_back({u, d});
		d = byz[i].first - byz[i - 1].first;
		u = byz[i].second.second.second;
		v = byz[i - 1].second.second.second;
		adj[u].push_back({v, d});
		adj[v].push_back({u, d});
	}

	cout << prim(adj) << endl;
	
	return 0;
}
