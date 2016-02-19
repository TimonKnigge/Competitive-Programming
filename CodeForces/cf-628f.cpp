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

int find2(int v, int d) {
	if (v <= 0) return 0;
	return (v - d + 5) / 5;
}
int ffind(int l, int r, int d) {
	return (find2(r, d) - find2(l-1, d));
}

int main() {
	
	int n, b, q;
	scanf("%d %d %d", &n, &b, &q);
	
	vii given;
	while (q--) {
		int upto, quantity;
		scanf("%d %d", &upto, &quantity);
		given.push_back({upto, quantity});
	}
	given.push_back({0, 0});
	given.push_back({b, n});
	
	sort(given.begin(), given.end());
	for (size_t i = 1; i < given.size(); ++i) {
		if (given[i-1].second > given[i].second || 
			(given[i-1].first == given[i].first &&
			 given[i-1].second != given[i].second)) {
			cout << "unfair" << endl;
			return 0;
		}
	}
	
	vector<pair<ii, int> > ivs;
	for (size_t i = 1; i < given.size(); ++i) {
		if (given[i-1].first == given[i].first) continue;
		ivs.push_back({{given[i-1].first+1, given[i].first},
			given[i].second - given[i-1].second});
	}
	
	int L = ivs.size();
	int R = 5;
	int SOURCE = L + R, SINK = L + R + 1;
	
	FlowGraph fg(L + R + 2);
	for (int i = 0; i < int(ivs.size()); ++i) {
		fg.add_edge(SOURCE, i, ivs[i].second);
		for (int d = 1; d <= 5; ++d) {
			fg.add_edge(i, L + (d%5), 
				ffind(ivs[i].first.first, ivs[i].first.second, d));
		}
	}
	for (int d = 0; d < 5; ++d)
		fg.add_edge(L + d, SINK, n / 5);
	
	Dinic dn(fg, SOURCE, SINK);
	ll flo = dn.run();
	if (flo == n) cout << "fair" << endl;
	else cout << "unfair" << endl;
	
	return 0;
}
