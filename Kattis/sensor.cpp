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

// FG
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
void imc_dfs(FlowGraph &fg, int u, vb &cut) {
	cut[u] = true;
	for (auto &&e : fg[u]) {
		if (e.cap > e.f && !cut[e.v])
			imc_dfs(fg, e.v, cut);
	}
}
ll infer_minimum_cut(FlowGraph &fg, int s, vb &cut) {
	cut.assign(fg.size(), false);
	imc_dfs(fg, s, cut);
	ll cut_value = 0LL;
	for (size_t u = 0; u < fg.size(); ++u) {
		if (!cut[u]) continue;
		for (auto &&e : fg[u]) {
			if (cut[e.v]) continue;
			cut_value += e.cap;
			// The edge e from u to e.v is
			// in the minimum cut.
		}
	}
	return cut_value;
}
//-FG

ll dist(ii l, ii r) {
	return (l.first-r.first)*(l.first-r.first)
		+ (l.second-r.second)*(l.second-r.second);
}
ll side(ii p1, ii p2, ii c) {
	return (p2.first-p1.first)*(c.second-p1.second)
		- (p2.second-p1.second)*(c.first-p1.first);
}

bool internal(ii p1, ii p2, ii c) {
	ll pr1 = (c.first-p1.first)*(p2.first-p1.first)
		+ (c.second-p1.second)*(p2.second-p1.second);
	ll pr2 = (c.first-p2.first)*(p1.first-p2.first)
		+ (c.second-p2.second)*(p1.second-p2.second);
	return (pr1 >= 0 && pr2 >= 0);
}

void attempt(ii p1, ii p2, vii &pts, ll d, vi &best) {
	ll d12 = dist(p1, p2);
	if (d12 > d*d) return;

	vi l, r;
	for (int i = 0; i < (int)pts.size(); ++i) {
		if (dist(pts[i], p1) > d*d) continue;
		if (dist(pts[i], p2) > d*d) continue;
		if (!internal(p1, p2, pts[i])) continue;
		if (side(p1, p2, pts[i]) > 0LL)
			l.push_back(i);
		else	r.push_back(i);
	}
	FlowGraph fg(l.size() + r.size() + 2);
	int SOURCE = l.size()+r.size(), SINK = l.size()+r.size()+1;
	for (size_t i = 0; i < l.size(); ++i) fg.add_edge(SOURCE, i, 1);
	for (size_t i = 0; i < r.size(); ++i) {
		fg.add_edge(l.size()+i, SINK, 1);
		for (size_t j = 0; j < l.size(); ++j)
			if (dist(pts[r[i]], pts[l[j]]) > d*d)
				fg.add_edge(j, l.size()+i, 1);
	}
	Dinic(fg, SOURCE, SINK).run();
	vb cut(fg.size(), false);
	infer_minimum_cut(fg, SOURCE, cut);
	
	vi sol;
	for (size_t i = 0; i < l.size(); ++i)
		if (cut[i]) sol.push_back(l[i]);
	for (size_t j = 0; j < r.size(); ++j)
		if (!cut[l.size()+j]) sol.push_back(r[j]);
	if (sol.size() > best.size()) swap(best, sol);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N;
	ll d;
	cin >> N >> d;
	
	vii pts(N, {0, 0});
	for (ii &pt : pts) cin >> pt.first >> pt.second;
	
	vi best(1, 0);
	for (int i = 0; i < N; ++i)
		for (int j = i + 1; j < N; ++j)
			attempt(pts[i], pts[j], pts, d, best);
	cout << best.size() << endl;
	for (int i = 0; i < (int)best.size(); ++i)
		cout << best[i]+1 << " \n"[i+1==(int)best.size()];
	
	return 0;
}
