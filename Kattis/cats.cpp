#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef long long ll;
struct AdjEdge { int v; ll weight; };
struct Edge { int u, v; };
struct PQ { ll weight; Edge e; };
bool operator>(const PQ &l, const PQ &r) { return l.weight > r.weight; }
ll prim(vector<vector<AdjEdge> > &adj) {
	ll tc = 0; vector<bool> intree(adj.size(), false);
	priority_queue<PQ, vector<PQ>, greater<PQ> > pq;
	intree[0] = true;
	for (auto &e : adj[0]) pq.push({e.weight, {0, e.v}});
	while (!pq.empty()) {
		auto &top = pq.top();
		ll c = top.weight; auto e = top.e; pq.pop();
		if (intree[e.v]) continue;
		intree[e.v] = true; tc += c;
		for (auto &e2 : adj[e.v]) if (!intree[e2.v])
			pq.push({e2.weight, {e.v, e2.v}});
	}
	return tc;
}

void solve() {
	int M, C;
	scanf("%d", &M);
	scanf("%d", &C);
	vector<vector<AdjEdge> > e(C, vector<AdjEdge>());
	for (int s = 0; s < C * (C - 1) / 2; ++s) {
		int i, j; ll Dij;
		scanf("%d", &i);
		scanf("%d", &j);
		scanf("%lld", &Dij);
		e[i].push_back({j, Dij});
		e[j].push_back({i, Dij});
	}
	printf(prim(e) <= (M - C) ? "yes\n" : "no\n");
}

int main() {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; ++t) solve();
	
	return 0;
}
