#include <iostream> 
#include <cstdio>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <bitset>
#include <numeric>
#include <iterator>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <cassert>

using namespace std;
using ll = long long;
using ld = long double;
using ii = pair<ll, ll>;
using vi = vector<ll>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

using F = ll; using W = ll; // types for flow and weight/cost
struct S{
	int v;			// neighbour
	const int r;	// index of the reverse edge
	F f;			// current flow
	const F cap;	// capacity
	const W cost;	// unit cost
	S(int v, int reverse_index, F capacity, W cost = 0) :
		v(v), r(reverse_index), f(0), cap(capacity), cost(cost) {}
};
struct FlowGraph : vector<vector<S>> {
	FlowGraph(size_t n) : vector<vector<S>>(n) {}
	void add_edge(int u, int v, F capacity, W cost = 0){
		operator[](u).emplace_back(v, operator[](v).size(), capacity, cost);
		operator[](v).emplace_back(u, operator[](u).size()-1, 0, -cost);
	}
};

struct Dinic{
	FlowGraph &edges; int V,s,t;
	vi l; vector<vector<S>::iterator> its; // levels and iterators
	Dinic(FlowGraph &edges, int s, int t) :
		edges(edges), V(edges.size()), s(s), t(t), l(V,-1), its(V) {}
	ll augment(int u, ll c) { // we reuse the same iterators
		if (u == t) return c;
		for(auto &i = its[u]; i != edges[u].end(); i++){
			auto &e = *i;
			if (e.cap > e.f && l[u] < l[e.v]) {
				auto d = augment(e.v, min(c, e.cap - e.f));
				if (d > 0) { e.f += d; edges[e.v][e.r].f -= d; return d; }
			}	}
		return 0;
	}
	ll run() {
		ll flow = 0, f;
		while(true) {
			fill(l.begin(), l.end(),-1); l[s]=0; // recalculate the layers
			queue<int> q; q.push(s);
			while(!q.empty()){
				auto u = q.front(); q.pop();
				for(auto &&e : edges[u]) if(e.cap > e.f && l[e.v]<0)
					l[e.v] = l[u]+1, q.push(e.v);
			}
			if (l[t] < 0) return flow;
			for (int u = 0; u < V; ++u) its[u] = edges[u].begin();
			while ((f = augment(s, INF)) > 0) flow += f;
		}	}
};

int main() {
	
	int N, M, C;
	scanf("%d %d %d", &N, &M, &C);
	
	vvii ET(N, vii());
	while (M--) {
		int x, y, w;
		scanf("%d %d %d", &x, &y, &w);
		--x;
		--y;
		ET[x].push_back({y, w});
		ET[y].push_back({x, w});
	}
	
	priority_queue<ii, vector<ii>, greater<ii> > pq;
	vi D(N, LLINF);
	D[0] = 0LL;
	pq.push({0LL, 0LL});
	while (!pq.empty()) {
		ll d = pq.top().first, u = pq.top().second;
		pq.pop();
		if (D[u] < d) continue;
		for (ii vw : ET[u]) {
			ll v = vw.first, w = vw.second;
			if (D[v] > d + w) {
				D[v] = d + w;
				pq.push({D[v], v});
			}
		}
	}
	
	vvii E(N, vii());
	for (int u = 0; u < N; ++u) {
		for (size_t i = 0; i < ET[u].size(); ++i) {
			if (D[u] == D[ET[u][i].first] + ET[u][i].second) {
				E[u].push_back({ET[u][i]});
			}
		}
	}
	
	vii positions(C, {0LL, 0LL});
	for (int i = 0; i < C; ++i) {
		int p;
		scanf("%d", &p);
		--p;
		positions[i] = {D[p], p};
	}
	
	sort(positions.begin(), positions.end());
	
	FlowGraph fg(N + 1);
	int SOURCE = N, SINK = 0;
	
	for (int i = 0; i < N; ++i) {
		for (size_t j = 0; j < E[i].size(); ++j) {
			fg.add_edge(i, E[i][j].first, 1);
		}
	}
	
	Dinic dn(fg, SOURCE, SINK);
	
	int ans = 0;
	for (int l = 0, r = 0; l < C; l = r) {
		
		if (positions[l].first == LLINF) break;
		
		while (r < C && positions[l].first == positions[r].first) ++r;
		
		if (l + 1 == r) {
			++ans;
			continue;
		}
		
		// Add sources
		for (int i = l; i < r; ++i) {
			fg.add_edge(SOURCE, positions[i].second, 1);
		}
		
		ans += dn.run();
		// Reset flow graph
		for (int u = 0; u <= N; ++u)
			for (size_t i = 0; i < fg[u].size(); ++i)
				fg[u][i].f = 0LL;
		
		fg[N].clear();
	}
	
	cout << ans << endl;
	
	return 0;
}
