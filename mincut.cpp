#include <iostream> // strings/streams
#include <string>
#include <sstream>
#include <vector> // datastructures
#include <list>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <bitset>
#include <tuple> // quick compare
#include <cstdio> // utils
#include <numeric>
#include <iterator>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <cassert>

#define REP(i,n)	for(auto i = decltype(n)(0); i<(n); i++)
#define F(v)		begin(v), end(v)
constexpr bool LOG =
#ifdef _LOG
true;
#define _GLIBCXX_DEBUG
#else
false;
#endif

using namespace std;
using ll = long long;
using ii = pair<int,int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;

constexpr int  INF = 1e9+1; // < 1e9 - -1e9
constexpr ll LLINF = 1e18+1;
void Log() { if(LOG) cerr << "\n"; }
template<class T, class... S> void Log(T t, S... s){
	if(LOG) cerr << t << "\t", Log(s...);
}

struct S {
	int v;
	const int r;
	ll f;
	const ll cap;
	const ll cost;
	S(int v, int reverse_index, ll capacity, ll cost = 0 ) :
		v(v), r(reverse_index), f(0), cap(capacity), cost(cost) { }
};
struct FlowGraph : vector<vector<S> > {
	FlowGraph(size_t n) : vector<vector<S> >(n) {}
	void add_edge(int u, int v, ll capacity, ll cost = 0) {
		operator[](u).emplace_back(v, operator[](v).size(), capacity, cost);
		operator[](v).emplace_back(v, operator[](u).size() - 1, 0, -cost);
	}
};

struct Dinic {
	FlowGraph &edges; int V, s, t;
	vi l; vector<vector<S>::iterator> its;
	Dinic(FlowGraph &edges, int s, int t) :
		edges(edges), V(edges.size()), s(s), t(t), l(V, -1), its(V) {}
	ll augment(int u, ll c) {
		if (u == t) return c;
		for (auto &i = its[u]; i != edges[u].end(); ++i) {
			auto &e = *i;
			if (e.cap > e.f && l[u] < l[e.v]) {
				ll d = augment(e.v, min(c, e.cap-e.f));
				if (d > 0) {
					e.f += d; edges[e.v][e.r].f -= d;
					return d;
				}
			}
		}
		return 0;
	}
	ll run() {
		ll flow = 0, f;
		while (true) {
			fill(l.begin(), l.end(), -1); l[s] = 0;
			queue<int> q; q.push(s);
			while (!q.empty()) {
				auto u = q.front(); q.pop();
				for (auto &&e : edges[u]) if (e.cap > e.f
					&& l[e.v] < 0) {
						l[e.v] = l[u] + 1;
						q.push(e.v);
					}
			}
			if (l[t] < 0) return flow;
			for (int u = 0; u < V; ++u) its[u] = edges[u].begin();
			while ((f = augment(s, LLINF)) > 0) flow += f;
		}
	}
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
	}	}
	return cut_value;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, m, s, t;
	cin >> n >> m >> s >> t;
	FlowGraph fg(n);
	for (int i = 0; i < m; ++i) {
		int u, v; ll c;
		cin >> u >> v >> c;
		fg.add_edge(u, v, c);
	}
	
	Dinic dc(fg, s, t);
	dc.run();
	
	vb cut;
	infer_minimum_cut(fg, s, cut);
	vector<int> res;
	for (int i = 0; i < n; ++i) if (cut[i]) res.push_back(i);
	
	cout << res.size() << endl;
	for (size_t i = 0; i < res.size(); ++i) cout << res[i] << '\n';
	cout << flush;
	
	return 0;
}

