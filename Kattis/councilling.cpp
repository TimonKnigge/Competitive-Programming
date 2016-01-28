#include <iostream> 
#include <cstdio>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <unordered_map>
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
using ii = pair<int,int>;
using vi = vector<int>;
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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int T;
	cin >> T;
	while (T--) {
		int N;
		cin >> N;
		
		int parC = 0, clubC = 0;
		unordered_map<string, int> parmap, clubmap;
		vector<string> resname, parname, clubname;
		
		vi res_to_party;
		vvi res_to_clubs;
		
		for (int i = 0; i < N; ++i) {
			string resident, party;
			cin >> resident >> party;
			
			resname.push_back(resident);
			int pid = 0;
			auto it = parmap.find(party);
			if (it != parmap.end()) pid = it->second;
			else {
				pid = parC;
				parname.push_back(party);
				parmap.insert({party, pid});
				parC++;
			}
			
			res_to_party.push_back(pid);
			int cs;
			cin >> cs;
			res_to_clubs.push_back(vi());
			while (cs--) {
				string c;
				cin >> c;
				auto it2 = clubmap.find(c);
				int cid = 0;
				if (it2 != clubmap.end()) cid = it2->second;
				else {
					cid = clubC;
					clubname.push_back(c);
					clubmap.insert({c, cid});
					clubC++;
				}
				res_to_clubs.back().push_back(cid);
			}
		}
		
		int UB = (clubC - 1) / 2;
		if (UB == 0) cout << "Impossible." << endl;
		else {
			FlowGraph fg(2 + clubC + N + parC);
			int SOURCE = clubC + N + parC;
			int SINK = SOURCE + 1;
			
			for (int i = 0; i < parC; ++i) {
				fg.add_edge(clubC + N + i, SINK, UB);
			}
			for (int i = 0; i < N; ++i)
				fg.add_edge(clubC + i, clubC + N + res_to_party[i], 1);
			for (int i = 0; i < N; ++i) {
				for (int j : res_to_clubs[i]) {
					fg.add_edge(j, clubC + i, 1);
				}
			}
			for (int i = 0; i < clubC; ++i)
				fg.add_edge(SOURCE, i, 1);
			
			Dinic dn(fg, SOURCE, SINK);
			ll flo = dn.run();
			if (flo < clubC) cout << "Impossible." << endl;
			else {
				vi match(clubC, -1);
				for (int i = 0; i < clubC; ++i) {
					for (int j = 0; j < fg[i].size(); ++j) {
						if (fg[i][j].f==0) continue;
						if (fg[i][j].v >= clubC && fg[i][j].v < clubC + N)
							match[i] = fg[i][j].v - clubC;
					}
				}
				for (int i = 0; i < clubC; ++i)
					cout << resname[match[i]] << " " << clubname[i] << endl;
			}
		}
		if (T > 0) cout << endl;
	}
	
	return 0;
}
