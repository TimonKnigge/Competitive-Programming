#include <iostream> 
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
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

struct S{
	int v;			// neighbour
	const int r;	// index of the reverse edge
	ll f;			// current flow
	const ll cap;	// capacity
	const ll cost;	// unit cost
	S(int v, int reverse_index, ll capacity, ll cost = 0) :
		v(v), r(reverse_index), f(0), cap(capacity), cost(cost) {}
};
struct FlowGraph : vector<vector<S>> {
	FlowGraph(size_t n) : vector<vector<S>>(n) {}
	void add_edge(int u, int v, ll capacity, ll cost = 0){
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
			for(int u=0;u<V;++u) its[u] = edges[u].begin();
			while ((f = augment(s, INF)) > 0) flow += f;
		}	}
};


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int R;
	cin >> R;
	while (R--) {
		int N, M, K;
		cin >> N >> M >> K;
		
		vector<vb> adj(N, vb(M, false));
		for (int i = 0; i < K; ++i) {
			double x, y;
			cin >> x >> y;
			adj[int(x)][int(y)] = true;
		}
		
		FlowGraph fg(N + M + 2);
		int SOURCE = N + M, SINK = N + M + 1;
		
		for (int i = 0; i < N; ++i) {
			fg.add_edge(SOURCE, i, 1);
			for (int j = 0; j < M; ++j) {
				if (adj[i][j])
					fg.add_edge(i, N + j, 1);
			}
		}
		for (int i = 0; i < M; ++i)
			fg.add_edge(N + i, SINK, 1);
		
		Dinic dn(fg, SOURCE, SINK);
		cout << dn.run() << endl;
	}
	
	return 0;
}
