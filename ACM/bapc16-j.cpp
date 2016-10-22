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

//
using F = ll; using W = ll; // types for flow and weight/cost
struct S{
	const int v;			// neighbour
	const int r;	// index of the reverse edge
	F f;			// current flow
	F cap;	// capacity
	const W cost;	// unit cost
	S(int v, int ri, F c, W cost = 0) :
		v(v), r(ri), f(0), cap(c), cost(cost) {}
};
struct FlowGraph : vector<vector<S>> {
	FlowGraph(size_t n) : vector<vector<S>>(n) {}
	void add_edge(int u, int v, F c, W cost = 0){ auto &t = *this;
		t[u].emplace_back(v, t[v].size(), c, cost);
		t[v].emplace_back(u, t[u].size()-1, 0, -cost);
	}
};
struct Dinic{
	FlowGraph &edges; int V,s,t;
	vi l; vector<vector<S>::iterator> its; // levels and iterators
	Dinic(FlowGraph &edges, int s, int t) :
		edges(edges), V(edges.size()), s(s), t(t), l(V,-1), its(V) {}
	ll augment(int u, F c) { // we reuse the same iterators
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
//

ll dis(ii l, ii r) {
	return abs(l.first-r.first)+abs(l.second-r.second);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N;
	cin >> N;
	vii L(N, {-1, -1}), R(N, {-1, -1});
	for (int i = 0; i < N; ++i) cin >> L[i].first >> L[i].second;
	for (int i = 0; i < N; ++i) cin >> R[i].first >> R[i].second;
	
	
	vvi D(N, vi(N, 0LL));
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			D[i][j] = dis(L[i], R[j]);
	
	ll l = 0LL, r = 0LL;
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			r = max(r, D[i][j]);
	
	FlowGraph fg(N+N+2);
	ll SOURCE = N+N, SINK = N+N+1;
	for (int i = 0; i < N; ++i) {
		fg.add_edge(SOURCE, i, 1);
		fg.add_edge(i+N, SINK, 1);
		for (int j = 0; j < N; ++j)
			fg.add_edge(i, j+N, 1);
	}
	
	while (l < r) {
		ll k = (l+r)/2LL;
		// k is the maximum distance
		for (int i = 0; i < N+N+2; ++i) {
			for (size_t j = 0; j < fg[i].size(); ++j) {
				fg[i][j].f = 0LL;
				if (i >= N || fg[i][j].v >= N+N) continue;
				fg[i][j].cap = (D[i][fg[i][j].v - N] <= k ? 1 : 0);
			}
		}
		if (Dinic(fg, SOURCE, SINK).run() < N)
			l = k + 1;
		else	r = k;
	}
	
	cout << l << endl;	
	
	return 0;
}
