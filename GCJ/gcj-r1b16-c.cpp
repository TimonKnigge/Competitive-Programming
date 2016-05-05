#include <iostream> 
#include <unordered_map>
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


void solve(int t) {
	int N;
	cin >> N;
	
	unordered_map<string, int> lmap, rmap;
	int lid = 0, rid = 0;
	vvi lout;
	vvi rout;
	while (N--) {
		string L, R;
		cin >> L >> R;
		int mlid = -1, mrid = -1;
		
		auto itl = lmap.find(L);
		if (itl == lmap.end()) {
			lout.push_back(vi());
			mlid = lid;
			lmap.insert({L, lid++});
		} else mlid = itl->second;
		auto itr = rmap.find(R);
		if (itr == rmap.end()) {
			rout.push_back(vi());
			mrid = rid;
			rmap.insert({R, rid++});
		} else mrid = itr->second;
		lout[mlid].push_back(mrid);
		rout[mrid].push_back(mlid);
	}
	
	FlowGraph fg(2 + lid + rid);
	int SOURCE = lid + rid, SINK = lid + rid + 1;
	for (int i = 0; i < lid; ++i)
		if (lout[i].size() > 1)
			fg.add_edge(SOURCE, i, lout[i].size() - 1);
	for (int i = 0; i < rid; ++i)
		if (rout[i].size() > 1)
			fg.add_edge(lid+i, SINK, rout[i].size() - 1);
	for (int i = 0; i < lid; ++i)
		for (int j : lout[i])
			fg.add_edge(i, lid+j, 1);
	
	Dinic dn(fg, SOURCE, SINK);
	cout << "Case #" << t << ": " << dn.run() << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int T;
	cin >> T;
	for (int t = 1; t <= T; ++t) solve(t);
	
	return 0;
}
