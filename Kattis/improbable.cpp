#include <bits/stdc++.h>

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
	const int v;			// neighbour
	const int r;	// index of the reverse edge
	F f;			// current flow
	const F cap;	// capacity
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


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int R, C;
	cin >> R  >> C;
	vvi B(R, vi(C, 0LL));
	vi RM(R, 0LL), CM(C, 0LL);
	ll minimal = 0LL;
	for (int r = 0; r < R; ++r)
		for (int c = 0; c < C; ++c)
			cin >> B[r][c],
			RM[r] = max(RM[r], B[r][c]),
			CM[c] = max(CM[c], B[r][c]),
			minimal += B[r][c] - ll(B[r][c] > 0LL);
	
	FlowGraph fg(R+C+2);
	int SOURCE = R+C, SINK = R+C+1;
	for (int r = 0; r < R; ++r) {
		minimal -= max(0LL, RM[r] - 1LL);
		fg.add_edge(SOURCE, r, 1);
		for (int c = 0; c < C; ++c)
			if (B[r][c] > 0LL && RM[r] == CM[c])
				fg.add_edge(r, R+c, 1);
	}
	for (int c = 0; c < C; ++c) {
		minimal -= max(0LL, CM[c] - 1LL);
		fg.add_edge(R+c, SINK, 1);
	}
	
	Dinic(fg, SOURCE, SINK).run();
	for (size_t i = 0; i < fg[SOURCE].size(); ++i) {
		if (fg[SOURCE][i].f > 0LL)
			minimal += max(0LL, RM[fg[SOURCE][i].v] - 1LL);
	}
	cout << minimal << endl;
	
	return 0;
}
