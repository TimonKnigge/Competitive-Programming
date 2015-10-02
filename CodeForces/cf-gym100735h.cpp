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

// MAXFLOW
struct S{
	int v;		// neighbour
	const int r;	// index of the reverse edge
	ll f;		// current flow
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
			for (int u = 0; u < V; ++u) its[u] = edges[u].begin();
			while ((f = augment(s, INF)) > 0) flow += f;
		}	}
};

// -MAXFLOW

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	string S;
	int N;
	cin >> S >> N;
	
	// Count how often we need each lowercase english letter to make S
	char count[26];
	for (size_t i = 0; i < 26; ++i) count[i] = 0;
	for (size_t i = 0; i < S.length(); ++i) {
		count[S[i] - 'a']++;
	}
	
	// Make a FlowGraph with a cubes on the left side and letters on
	// the right side. Connect the cubes with the source using capacity
	// 1 edges (each cube can be used once), and connect the letters
	// with the sink using capacity count[i] edges (the letter i is 
	// needed count[i] times).
	FlowGraph fg(N + 26 + 2);
	
	// [0..N) are the cubes, [N..N+26) the letters, the other two
	// vertices are the source and sink.
	int SOURCE = N + 26, SINK = N + 26 + 1;
	
	// Make the above-mentioned connections
	for (int i = 0; i < N; ++i) fg.add_edge(SOURCE, i, 1);
	for (int i = 0; i < 26; ++i)
		if (count[i] > 0)
			fg.add_edge(N + i, SINK, count[i]);
	
	// Now read all the cubes
	for (int i = 0; i < N; ++i) {
		
		// For each letter, connect this cube (its vertex on the
		// left side) with the letter (its vertex on the right side)
		// using a capacity 1 edge (each cube can only provide one
		// letter).
		// Note: we can discard numbers, they aren't used anyway.
		for (int k = 0; k < 6; ++k) {
			char c;
			cin >> c;
			if (c >= '0' && c <= '9') continue;
			fg.add_edge(i, N + (c - 'a'), 1);
		}
	}
	
	// Find the flow
	Dinic dc(fg, SOURCE, SINK);
	ll flow = dc.run();
	
	// Did we find each letter?
	cout << (flow == ll(S.length()) ? "YES" : "NO") << endl;
	
	return 0;
}
