#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
typedef long long ll;
using namespace std;

struct AdjEdge { int v, weight; };	// adjacency list edge
struct Edge { int u, v; };			// edge u->v for output
struct PQ { int weight; Edge e; };	// PQ element
bool operator>(const PQ &lhs, const PQ &rhs) {
    return lhs.weight > rhs.weight;
}
ll prim(vector<vector<AdjEdge>>& adj, vector<Edge>& tree) {
	ll tc = 0; vector<bool> intree(adj.size(), false);
	priority_queue<PQ, vector<PQ>, greater<PQ> > pq;
	intree[0] = true;
	int tcount = 1;
	for (auto& e : adj[0]) pq.push({e.weight, {0, e.v}});
	while (!pq.empty()) {
		auto& top = pq.top();
		int c = top.weight; auto e = top.e; pq.pop();
		if (intree[e.v]) {tc += c; continue; };
		intree[e.v] = true; tree.push_back(e);
		tcount++;
		for (auto& e2 : adj[e.v])
			if (!intree[e2.v]) pq.push({e2.weight, {e.v, e2.v}});
	}
	return (tcount == adj.size() ? tc : -1);
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int n, m;
	cin >> n >> m;
	vector<vector<AdjEdge> > adj(n, vector<AdjEdge>());
	for (int i = 0; i < m; ++i) {
		int a, b, w;
		cin >> a >> b >> w;
		a--; b--;
		adj[a].push_back({b, w});
		adj[b].push_back({a, w});
	}
	vector<Edge> tree;
	cout << prim(adj,tree)<<endl;
}
