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
	int V; vector<vector<int> > &graph; // graph can be graph or childs only
	vi p, r, d, h; // parents, path-root; heavy child, depth
	HLD(vector<vector<int> > &graph, int root = 0) : V(graph.size()), graph(graph),
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

void root(int u, int p, vector<vector<int> > &e, vector<vector<int> > &ch, vi &sz, vi &dpth, vii &dpthcounts, ll &time, vi &in, vi &out) {
	in[u] = time++;
	dpthcounts[u] = {0LL, 1LL};
	for (int v : e[u]) {
		if (p == v) continue;
		dpth[v] = 1 + dpth[u];
		root(v, u, e, ch, sz, dpth, dpthcounts, time, in, out);
		ch[u].push_back(v);
		sz[u] += sz[v];
		dpthcounts[u].first  += dpthcounts[v].first;
		dpthcounts[u].second += dpthcounts[v].second;
	}
	dpthcounts[u].first += dpthcounts[u].second - 1LL;
	out[u] = time++;
}

void calcup(int u, vector<vector<int> > &ch, vii &pathsup, vii &dpthcounts) {
	ii val = pathsup[u];
	val.first += dpthcounts[u].first;
	val.second += dpthcounts[u].second;
//	cerr << "   " << u << ' ' << ch[u].size() << endl;
	for (int v : ch[u]) {
		pathsup[v] = val;
		pathsup[v].second -= dpthcounts[v].second;
		pathsup[v].first -= dpthcounts[v].first + dpthcounts[v].second;
		pathsup[v].first += pathsup[v].second;
//		cerr << v << ' ' << pathsup[v].first << ' '<<pathsup[v].second<<endl;
		calcup(v, ch, pathsup, dpthcounts);
	}
}

int main() {
	
	int N, M;
	scanf("%d %d", &N, &M);
	
	vector<vector<int> > e(N, vector<int>());
	for (int i = 0; i + 1 < N; ++i) {
		int a, b;
		scanf("%d %d", &a, &b);
		--a;
		--b;
		e[a].push_back(b);
		e[b].push_back(a);
	}
	
	vector<vector<int> > ch(N, vector<int>());
	vi sz(N, 1LL), dpth(N, 0LL);
	vi in(N, 0LL), out(N, 0LL);
	vii dpthcounts(N, {0LL, 0LL}), pathsup(N, {0LL, 0LL});
	ll time = 0LL;
	root(0, -1, e, ch, sz, dpth, dpthcounts, time, in, out);
	calcup(0, ch, pathsup, dpthcounts);
	
	HLD hld(ch, 0);
	while (M--) {
		int u, v;
		scanf("%d %d", &u, &v);
		--u;
		--v;
		assert(u != v);
		if (dpth[u] > dpth[v]) swap(u, v);
		
		int lca = hld.lca(u, v);
		ll dibt = dpth[u] + dpth[v] - 2LL * dpth[lca] + 1LL;
		
		ii underu = dpthcounts[u];
		ii underv = dpthcounts[v];
		
		if (u == lca) {
			// find the child that contains v
			int l = 0, r = int(ch[u].size()) - 1;
			while (l < r) {
				int mid = (l + r) / 2;
				if (out[ch[u][mid]] < in[v])
					l = mid + 1;
				else	r = mid;
			}
			while (in[ch[u][l]] > in[v]) --l;
			while (out[ch[u][l]] < out[v]) ++l;
			int c = ch[u][l];
			underu.second -= dpthcounts[c].second;
			underu.first  -= dpthcounts[c].first + dpthcounts[c].second;
			underu.second += pathsup[u].second;
			underu.first  += pathsup[u].first;
		}
//		cerr << underu.first << ' ' << underu.second << endl;
//		cerr << underv.first << ' ' << underv.second << endl;
		
		ld ans = ld(dibt) + ld(underu.first) / ld(underu.second)
				  + ld(underv.first) / ld(underv.second);
		printf("%.7lf\n", double(ans));
	}
	
	return 0;
}
