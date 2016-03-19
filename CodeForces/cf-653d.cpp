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
	F cap;	// capacity

	F realcap;
	W cost;	// unit cost
	S(int v, int reverse_index, F capacity, W cost = 0) :
		v(v), r(reverse_index), f(0), cap(capacity), realcap(capacity), cost(cost) {}
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

bool possible(FlowGraph &fg, int N, int X, ld d) {
	
	// Reset the flowgraph
	for (size_t i = 0; i < fg.size(); ++i) {
		for (size_t j = 0; j < fg[i].size(); ++j) {
			fg[i][j].f = 0LL;
			fg[i][j].cap = ll(double(fg[i][j].realcap) / d);
		}
	}
	
	Dinic dn(fg, 0, N - 1);
	return dn.run() >= X;
}

int main() {
	
	int N, M, X;
	scanf("%d %d %d", &N, &M, &X);
	
	FlowGraph fg(N);
	while (M--) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		--a; --b;
		fg.add_edge(a, b, c);	
	}
	
	ld l = 0.0, r = 1.0;
	while (possible(fg, N, X, r)) r *= 2.0;
	while (X * (r - l) > 1e-7) {
		ld m = (l + r) / 2.0;
		if (possible(fg, N, X, m))
			l = m;
		else	r = m;
	}
	
	printf("%.7lf\n", double(X * (l+r)/2.0));
	
	return 0;
}
