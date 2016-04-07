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

struct HLD {
	int V; vvi &graph; // graph can be graph or childs only
	vi p, r, d, h; // parents, path-root; heavy child, depth
	HLD(vvi &graph, int root = 0) : V(graph.size()), graph(graph),
	p(V,-1), r(V,-1), d(V,0), h(V,-1) { dfs(root);
		for(int i=0; i<V; ++i) if (p[i]==-1 || h[p[i]]!=i)
			for (int j=i; j!=-1; j=h[j]) r[j] = i;
	}
	int dfs(int u){
		ii best={-1,-1}; int s=1, ss;	// best, size (of subtree)
		for(auto &v : graph[u]) if(v!=p[u])
			d[v]=d[u]+1, p[v]=u, s += ss=dfs(v), best = max(best,{ss,v});
		h[u] = best.second; return s;
	}
	int lca(int u, int v){
		for(; r[u]!=r[v]; v=p[r[v]]) if(d[r[u]] > d[r[v]]) swap(u,v);
		return d[u] < d[v] ? u : v;
	}
};

int main() {
	
	int N;
	scanf("%d", &N);
	
	vvii E(N, vii());
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			int v;
			scanf("%d", &v);
			if (v <= 0) continue;
			E[i].push_back({j, v});
		}
	}
	
	vi ans(N, -1LL);
	
	for (int u = 0; u < N; ++u) {
		
		vi d(N, LLINF);
		priority_queue<ii, vector<ii>, greater<ii>> pq;
		pq.push({0LL, u});
		d[u] = 0LL;
		
		vi p(N, -1LL);
		while (!pq.empty()) {
			int v = pq.top().second;
			ll dist = pq.top().first;
			pq.pop();
			
			if (dist > d[v]) continue;
			for (ii wd : E[v]) {
				int w = wd.first;
				int dist2 = wd.second;
				if (dist + dist2 < d[w]) {
					d[w] = dist + dist2;
					p[w] = v;
					pq.push({d[w], w});
				}
			} 
		}

		vvi ch(N, vi());
		for (int i = 0; i < N; ++i)
			if (p[i] != -1)
				ch[p[i]].push_back(i);
		
		HLD hld(ch, u);

		// Edges adjacent to u
		for (size_t j = 0; j < E[u].size(); ++j) {
			if (p[E[u][j].first] == u)
				continue;
			if (ans[u] == -1LL || ans[u] > E[u][j].second + d[E[u][j].first])
				ans[u] = E[u][j].second + d[E[u][j].first];
		}
		
		
		for (int i = 0; i < N; ++i) {
			if (i == u) continue;
			if (d[i] == LLINF) continue;
			for (size_t j = 0; j < E[i].size(); ++j) {
				if (E[i][j].first == u) continue;
				if (hld.lca(i, E[i][j].first) != u) continue;
				if (ans[u] == -1LL || ans[u] > E[i][j].second + d[i] + d[E[i][j].first])
					ans[u] = E[i][j].second + d[i] + d[E[i][j].first];
			}
		}
	}
	
	for (int i = 0; i < N; ++i)
		cout << ans[i] << '\n';
	
	return 0;
}
