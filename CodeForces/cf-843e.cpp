#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
using ll = long long;
using ld = long double;
using ii = pair<ll, ll>;
using vi = vector<ll>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;
using vb = vector<bool>;

template<class T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<class TIn, class TOut = null_type>
using order_tree = tree<TIn, TOut, less<TIn>, rb_tree_tag,
	tree_order_statistics_node_update>;

constexpr ll INF = 1000000010;
constexpr ll LLINF = 1000000000000000010LL;

using F = ll; using W = ll; // types for flow and weight/cost
struct S{
	const int v;			// neighbour
	const int r;	// index of the reverse edge
	F f;			// current flow
	const F cap;	// capacity
	const W cost;	// unit cost
	int assoc = -1;
	S(int v, int ri, F c, W cost = 0, int _assoc = -1) :
		v(v), r(ri), f(0), cap(c), cost(cost), assoc(_assoc) {}
};
struct FlowGraph : vector<vector<S>> {
	FlowGraph(size_t n) : vector<vector<S>>(n) {}
	void add_edge(int u, int v, F c, W cost = 0, int assoc = -1){ auto &t = *this;
		t[u].emplace_back(v, t[v].size(), c, cost, assoc);
		t[v].emplace_back(u, t[u].size()-1, 0, -cost, assoc);
	}
};


void dfs_fill(int i, vii &pr, vvii &E) {
	for (ii ch : E[i]) {
		int j = ch.first, ix = ch.second;
		if (pr[j].first != -1) continue;
		pr[j] = {i, ix};
		dfs_fill(j, pr, E);
	}
}

pair<vi, vi> coverall(int n, int m, int s, int t, vector<pair<ii, ii>> &edges) {
	map<ii, int> eid;
	for (auto &e : edges) eid[e.first] = e.second.second;

	vii par(n, {-1, -1}), rpar(n, {-1, -1});
	vvii E(n, vii()), RE(n, vii());
	for (auto &e : edges) {
		int u = e.first.first, v = e.first.second;
		int g = e.second.first, i = e.second.second;
		if (g == 0) continue;
		E[u].push_back({v, i});
		RE[v].push_back({u, i});
	}

	par[s] = rpar[t] = {-2, -2};
	dfs_fill(s, par, E);
	dfs_fill(t, rpar, RE);

	vi f(m, 0LL), c(m, 0LL);
	for (auto &e : edges) {
		int u = e.first.first, v = e.first.second;
		int g = e.second.first, i = e.second.second;
		if (g == 0) continue;

		if (f[i] > 0) continue;
		f[i]++; c[i]++;
		int w = u;
		while (par[w].first >= 0) {
			++f[par[w].second];
			++c[par[w].second];
			w = par[w].first;
		}
		w = v;
		while (rpar[w].first >= 0) {
			++f[rpar[w].second];
			++c[rpar[w].second];
			w = rpar[w].first;
		}
	}
//	cerr << "Cover all" << endl;
//	for (int i = 0; i < m; ++i)
//		cerr << ' ' << i << ' ' << f[i] << ' ' << c[i] << endl;
	return {f, c};
}

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

pair<vi, vi> block(int n, int m, int s, int t, vector<pair<ii, ii>> &edges) {
	FlowGraph fg(n);
	map<ii, int> eid;
	for (auto &e : edges) eid[e.first] = e.second.second;

	for (auto &e : edges) {
		int u = e.first.first, v = e.first.second;
		int g = e.second.first, i = e.second.second;
		if (g == 0) {
			fg.add_edge(u, v, INF, 0, i);
		} else {
			fg.add_edge(u, v, 1, 0, i);
			fg.add_edge(v, u, INF, 0, -1);
		}
	}
	
	Dinic(fg, s, t).run();
	vb mc;
	infer_minimum_cut(fg, s, mc);
//	cerr << "MC" << endl;
//	for (int i = 0; i < n; ++i)
//		cerr << i << ' '<< mc[i] << endl;

	vi f(m, 0LL), c(m, 0LL);
	for (int u = 0; u < n; ++u) {
		for (size_t j = 0; j < fg[u].size(); ++j) {
			int v = fg[u][j].v;
			if (fg[u][j].cap == 0LL) continue;
			if (!(mc[u] && !mc[v])) {
				if (fg[u][j].assoc != -1) ++c[fg[u][j].assoc];
			}
		}
	}
//	cerr << "Block" << endl;
//	for (int i = 0; i < m; ++i)
//		cerr << ' ' << i << ' ' << f[i] << ' ' << c[i] << endl;
	return {f, c};
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	ll n, m, s, t;
	cin >> n >> m >> s >> t;
	--s; --t;

	vector<pair<ii, ii>> edges;
	for (int i = 0; i < m; ++i) {
		int u, v, g;
		cin >> u >> v >> g;
		--u; --v;
		edges.push_back({{u, v}, {g, i}});
	}

	vi f(m, 0LL), c(m, 0LL);
	vi f2, c2;
	tie(f2, c2) = coverall(n, m, s, t, edges);
	for (int i = 0; i < m; ++i) f[i] += f2[i], c[i] += c2[i];
	tie(f2, c2) = block(n, m, s, t, edges);
	for (int i = 0; i < m; ++i) f[i] += f2[i], c[i] += c2[i];

	for (int i = 0; i < m; ++i) if (c[i] == 0) { f[i] = 0; c[i] = 2; }
	
	int ans = 0;
	for (int i = 0; i < m; ++i) ans += int(c[i] == f[i]);
	cout << ans << endl;
	for (int i = 0; i < m; ++i)
		cout << f[i] << ' ' << c[i] << '\n';

	return 0;
}
