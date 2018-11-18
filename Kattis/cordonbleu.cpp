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
using vd = vector<ld>;

template<class T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<class TIn, class TOut = null_type>
using order_tree = tree<TIn, TOut, less<TIn>, rb_tree_tag,
	tree_order_statistics_node_update>;
// .find_by_order(int r) and .order_of_key(TIn v)

constexpr int INF = 2000000010;
constexpr ll LLINF = 9000000000000000010LL;
constexpr ld PI = acos(-1);

// From ETH codebook
// Fastest flow and min cost flow/circulation code
// Push-Relabel cost-scaling algorithm
// Runs in O( V^3 * log(V * max_edge_cost))
// In practice runs in O(V * E) with constant < 1
// Operates on integers, costs are multiplied by 2N!!
// Works with negative costs
// To get min_cost_max_flow, don't change anything
// To get max flow, just call max_flow
// To get min cost circulation, remove the call to max_flow
// To get min cost (not max) flow, use circulation
// and add a t->s edge with capacity inf and cost 0
template<typename flow_t = int, typename cost_t = int>
struct mcSFlow{
  struct Edge{
    cost_t c;
    flow_t f;
    int to, rev;
    Edge(int _to, cost_t _c, flow_t _f, int _rev):c(_c), f(_f), to(_to), rev(_rev){}
  };
  static constexpr cost_t INFCOST = numeric_limits<cost_t>::max()/2;
  cost_t eps;
  int N, S, T;
  vector<vector<Edge> > G;
  vector<unsigned int> isq, cur;
  vector<flow_t> ex;
  vector<cost_t> h;
  mcSFlow(int _N, int _S, int _T):eps(0), N(_N), S(_S), T(_T), G(_N){}
  void add_edge(int a, int b, cost_t cost, flow_t cap){
    assert(cap>=0);
    assert(a>=0&&a<N&&b>=0&&b<N);
    if(a==b){assert(cost>=0); return;}
    cost*=N;
    eps = max(eps, abs(cost));
    G[a].emplace_back(b, cost, cap, G[b].size());
    G[b].emplace_back(a, -cost, 0, G[a].size()-1);
  }
  void add_flow(Edge& e, flow_t f) {
    Edge &back = G[e.to][e.rev];
    if (!ex[e.to] && f)
      hs[h[e.to]].push_back(e.to);
    e.f -= f; ex[e.to] += f;
    back.f += f; ex[back.to] -= f;
  }
  vector<vector<int> > hs;
  vector<int> co;
  // fast max flow
  flow_t max_flow() {
    ex.assign(N, 0);
    h.assign(N, 0); hs.resize(2*N);
    co.assign(2*N, 0); cur.assign(N, 0);
    h[S] = N;
    ex[T] = 1;
    co[0] = N-1;
    for(auto &e:G[S]) add_flow(e, e.f);
    if(hs[0].size())
    for (int hi = 0;hi>=0;) {
      int u = hs[hi].back();
      hs[hi].pop_back();
      while (ex[u] > 0) { // discharge u
        if (cur[u] == G[u].size()) {
          h[u] = 1e9;
          for(unsigned int i=0;i<G[u].size();++i){
            auto &e = G[u][i];
            if (e.f && h[u] > h[e.to]+1){
              h[u] = h[e.to]+1, cur[u] = i;
            }
          }
          if (++co[h[u]], !--co[hi] && hi < N)
            for(int i=0;i<N;++i)
              if (hi < h[i] && h[i] < N){
                --co[h[i]];
                h[i] = N + 1;
              }
          hi = h[u];
        } else if (G[u][cur[u]].f && h[u] == h[G[u][cur[u]].to]+1)
          add_flow(G[u][cur[u]], min(ex[u], G[u][cur[u]].f));
        else ++cur[u];
      }
      while (hi>=0 && hs[hi].empty()) --hi;
    }
    return -ex[S];
  }
  // begin min cost flow
  void push(Edge &e, flow_t amt){
    if(e.f < amt) amt=e.f;
    e.f-=amt; ex[e.to]+=amt;
    G[e.to][e.rev].f+=amt; ex[G[e.to][e.rev].to]-=amt;
  }
  void relabel(int vertex){
    cost_t newHeight = -INFCOST;
    for(unsigned int i=0;i<G[vertex].size();++i){
      Edge const&e = G[vertex][i];
      if(e.f && newHeight < h[e.to]-e.c){
        newHeight = h[e.to] - e.c;
        cur[vertex] = i;
      }
    }
    h[vertex] = newHeight - eps;
  }
  static constexpr int scale=2;
  pair<flow_t, cost_t> minCostMaxFlow(){
    cost_t retCost = 0;
    for(int i=0;i<N;++i)
      for(Edge &e:G[i])
        retCost += e.c*(e.f);
    // remove this for circulation
    flow_t retFlow = max_flow();
    h.assign(N, 0); ex.assign(N, 0);
    isq.assign(N, 0); cur.assign(N,0);
    stack<int> q; //queue is usually slower
    for(;eps;eps>>=scale){
      fill(cur.begin(), cur.end(), 0);
      for(int i=0;i<N;++i)
        for(auto &e:G[i])
          if(h[i] + e.c - h[e.to] < 0 && e.f) push(e, e.f);
      for(int i=0;i<N;++i){
        if(ex[i]>0){
          q.push(i);
          isq[i]=1;
        }
      }
      while(!q.empty()){
        int u=q.top();q.pop();
        isq[u]=0;
        while(ex[u]>0){
          if(cur[u] == G[u].size())
            relabel(u);
          for(unsigned int &i=cur[u], max_i = G[u].size();i<max_i;++i){
            Edge &e=G[u][i];
            if(h[u] + e.c - h[e.to] < 0){
              push(e, ex[u]);
              if(ex[e.to]>0 && isq[e.to]==0){
                q.push(e.to);
                isq[e.to]=1;
              }
              if(ex[u]==0) break;
      }  }  }  }
      if(eps>1 && eps>>scale==0){
        eps = 1<<scale;
      }
    }
    for(int i=0;i<N;++i){
      for(Edge &e:G[i]){
        retCost -= e.c*(e.f);
      }
    }
    return make_pair(retFlow, retCost/2/N);
  }
  flow_t getFlow(Edge const &e){
    return G[e.to][e.rev].f;
  }
};

ll mhd(ll x1, ll y1, ll x2, ll y2) {
	return abs(x1-x2) + abs(y1-y2);
}

void solve() {
	int N, M;
	cin >> N >> M;

	vi xb(N), yb(N), xc(M), yc(M);
	for (int i = 0; i < N; ++i) cin >> xb[i] >> yb[i];
	for (int i = 0; i < M; ++i) cin >> xc[i] >> yc[i];

	ll xr, yr;
	cin >> xr >> yr;

	ll base = 0LL;
	for (int i = 0; i < N; ++i)
		base += 2 * mhd(xr, yr, xb[i], yb[i]);

	int SOURCE = N+M+1, SINK = N+M+2;
	mcSFlow<ll, ll> mf(N+M+3, SOURCE, SINK);
	for (int i = 0; i < M; ++i) {
		mf.add_edge(SOURCE, i, 0LL, 1LL);
	}
	for (int i = 0; i < N; ++i) {
		mf.add_edge(M+i, SINK, 0LL, 1LL);
	}
	mf.add_edge(N+M, SINK, 0LL, M-1LL);
	for (int i = 0; i < M; ++i) {
		mf.add_edge(i, N+M, 0LL, 1LL);
		for (int j = 0; j < N; ++j) {
			ll change = mhd(xc[i], yc[i], xb[j], yb[j])
				- mhd(xr, yr, xb[j], yb[j]);
			mf.add_edge(i, M+j, change, 1LL);
		}
	}

	cout << base + mf.minCostMaxFlow().second << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout << fixed << setprecision(12);
	
	solve();
	
	return 0;
}
