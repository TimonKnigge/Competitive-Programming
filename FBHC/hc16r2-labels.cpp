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
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 100000000000000000; // factor 1/30 smaller than normal!!

using F = ll; using W = ll; // types for flow and weight/cost
struct S{
	int v;			// neighbour
	int r;	// index of the reverse edge
	F f;			// current flow
	F cap;	// capacity
	W cost;	// unit cost
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

using F = ll; using W = ll; W WINF = LLINF; F FINF = LLINF;
struct Q{ int u; F c; W w;}; // target, maxflow and total cost/weight
bool operator>(const Q &l, const Q &r){return l.w > r.w;}


#define REP(i,n)	for(auto i = decltype(n)(0); i<(n); i++)
#define F(v)		begin(v), end(v)
struct Edmonds_Karp_Dijkstra{
	FlowGraph &g; int V,s,t; vector<W> pot;
	Edmonds_Karp_Dijkstra(FlowGraph &g, int s, int t) :
		g(g), V(g.size()), s(s), t(t), pot(V) {}
	pair<F,W> run() { // return pair<f, cost>
		F maxflow = 0; W cost = 0;			// Bellmann-Ford for potentials
		fill(pot.begin(),pot.end(),WINF); pot[s]=0;
//		REP(i,V-1) {
//			bool relax = false;
//			REP(u,V) if(pot[u] != WINF) for(auto &e : g[u])
//				if(e.cap>e.f)
//					if(pot[u] + e.cost < pot[e.v])
//						pot[e.v] = pot[u] + e.cost, relax=true;
//			if(!relax) break;
//		}
		REP(u,V) if(pot[u] == WINF) pot[u] = 0;
		while(true){
			priority_queue<Q,vector<Q>,greater<Q>> q;
			vector<vector<S>::iterator> p(V,g.front().end());
			vector<W> dist(V, WINF); F f, tf = -1;
			q.push({s, FINF, 0}); dist[s]=0;
			while(!q.empty()){
				int u = q.top().u; W w = q.top().w;
				f = q.top().c; q.pop();
				if(w!=dist[u]) continue; if(u==t && tf < 0) tf = f;
				for(auto it = g[u].begin(); it!=g[u].end(); it++){
					auto &e = *it;
					W d =  w + e.cost + pot[u] - pot[e.v];
					if(e.cap>e.f && d < dist[e.v]){
						q.push({e.v, min(f, e.cap-e.f),dist[e.v] = d});
						p[e.v]=it;
					}	}	}
			auto it = p[t];
			if(it == g.front().end()) return {maxflow,cost};
			maxflow += f = tf;
			while(it != g.front().end()){

				auto &r = g[it->v][it->r];
				cost += f * it->cost; it->f+=f;
				r.f -= f; it = p[r.v];
			}
			for(int u =0;u<V; ++u) if(dist[u]!=WINF) pot[u] += dist[u];
		}
	}
};

int main() {
	
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; ++t) {
		int N, K;
		scanf("%d %d", &N, &K);
		ll P; int __P;
		scanf("%d", &__P); P = __P;
		
		vector<vector<ll> > C(K, vector<ll>(N, 0LL));
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < K; ++j) {
				int v;
				scanf("%d", &v);
				C[j][i] = v;
			}
		}
		
		vvi e(N, vi());
		for (int i = 0; i < N - 1; ++i) {
			int A, B;
			scanf("%d %d", &A, &B);
			e[A - 1].push_back(B - 1);
			e[B - 1].push_back(A - 1);	
		}
		
		// toposort from 0
		vi par(N, -1);
		vb vis(N, false);
		vi topo;
		stack<int> st;
		st.push(0);
		while (!st.empty()) {
			int u = st.top();
			if (vis[u]) {
				st.pop();
				topo.push_back(u);
			} else {
				for (int v : e[u]) {
					if (v == par[u]) continue;
					par[v] = u;
					st.push(v);
				}
				vis[u] = true;
			}
		}
		
		vector<vector<vector<ll> > > 
			dpdiff(K,vector<vector<ll> >(K, vector<ll>(N, LLINF)));
		vector<vector<ll> > dpbreak(K, vector<ll>(N, LLINF));
		for (int _j = 0; _j < N; ++_j) {
			int i = topo[_j];
//			cerr << "Visiting "<<i << endl;
			if ((e[i].size() <= 1 && _j != N-1) || (e[i].size() < 1 && _j==N-1)) {
				for (int c1 = 0; c1 < K; ++c1) {
					dpbreak[c1][i] = C[c1][i];
					for (int c2 = 0; c2 < K; ++c2)
						dpdiff[c1][c2][i] = C[c1][i];
				}
			} else {
				int kids = int(e[i].size()) - (_j==N-1?0:1);
				// First calculate dpbreak
				// That is, we break i and 
				// just pick the minimal cost
				// over all children
				for (int c1 = 0; c1 < K; ++c1) {
					// color i c1
					ll cost = P + C[c1][i];
					for (int j : e[i]) {
						if (j == par[i]) continue;
						// We need to color j,
						// any color suffices
						// decide whether or not
						// to break j
						ll best = LLINF;
						for (int c2 = 0; c2 < K; ++c2) {
							best=min(best, min(
								dpbreak[c2][j], dpdiff[c2][c1][j]));
						}
						cost += best;
					}
					dpbreak[c1][i] = cost;
				}
				// Dont break i, color it c1, and dont color children with c2 
				// if we have more than K children, this is impossible
				
				if (kids <= K && kids > 0)
				for (int c1 = 0; c1  < K; ++c1) {
					// color i c1, children
					// not c2
					for (int c2 = 0; c2 < K; ++c2) {
						FlowGraph fg(2*K+2);
						int SINK = 2*K+1, SOURCE=2*K;
						for (int u = 0; u < K; ++u) fg.add_edge(SOURCE, u, 1, 0);
						for (int u = 0; u < kids; ++u) fg.add_edge(K + u, SINK, 1, 0);
						int chn = 0;
						for (int j : e[i]) {
							if (j == par[i]) continue;
							for (int c3 = 0; c3 < K; ++c3) {
								if (c3 == c2) continue;
								// we'll color child j with color c3.
								ll optj = min(dpdiff[c3][c1][j], dpbreak[c3][j]);
								fg.add_edge(c3, K + chn, 1, optj);
							}
							chn ++;
						}
						Edmonds_Karp_Dijkstra ekd(fg, SOURCE, SINK);
						pair<ll, ll> res = ekd.run();
						if (res.first < kids) continue;
						else {
							dpdiff[c1][c2][i] = res.second + C[c1][i];
						}
					}
				}
			}
		}
//		for (int i = 0; i < N; ++i) {
//			cout << i << " " << dpbreak[0][i] << endl;
//		}
		
		int root = topo[N - 1]; // == 0  ?
		ll outp = LLINF;
		
		// Break the root
		for (int c1 = 0; c1 < K; ++c1) outp = min(outp, dpbreak[c1][root]);
		int kids = int(e[root].size());
		// Dont break it!
		if (kids > 0 && kids <= K) {
			for (int c1 = 0; c1 < K; ++c1) {
				FlowGraph fg(2*K + 2);
				int SOURCE = 2 * K, SINK = 2 * K + 1;
				for (int u = 0; u < K; ++u) fg.add_edge(SOURCE, u, 1, 0);
				for (int u = 0; u < K; ++u) fg.add_edge(K+u, SINK, 1, 0);
				int chn = 0;
				for (int j : e[root]) {
					for (int c2 = 0; c2 < K; ++c2) {
						ll optj = min(dpdiff[c2][c1][j], dpbreak[c2][j]);
						fg.add_edge(c2, K + chn, 1, optj);
					}
					chn++;
				}
				Edmonds_Karp_Dijkstra ekd(fg, SOURCE, SINK);
				pair<ll, ll> res = ekd.run();
				if (res.first < kids) continue;
				else outp = min(outp, res.second + C[c1][root]);
			}
		}
		
		cout << "Case #" << t << ": " << outp << endl;
	}
	
	return 0;
}
