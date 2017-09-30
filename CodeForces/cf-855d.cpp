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

template<class T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<class TIn, class TOut = null_type>
using order_tree = tree<TIn, TOut, less<TIn>, rb_tree_tag,
	tree_order_statistics_node_update>;

constexpr int INF = 1000000010;
constexpr ll LLINF = 1000000000000000010LL;

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

constexpr int PARTOF = 1, SPECIAL = 0, NONE = 2;

void dfs1(int u, vvi &E, vvi &T, vi &hp, vi &hs, vi &depth) {
	int C = (int)E[u].size();
	for (int i = 0; i < C; ++i) {
		int v = E[u][i], t = T[u][i];
		if (t == PARTOF) {
			hp[v] = hp[u];
			hs[v] = v;
		} else if (t == SPECIAL) {
			hp[v] = v;
			hs[v] = hs[u];
		} else {
			hp[v] = hs[v] = v;
		}
		depth[v] = depth[u] + 1;
		dfs1(v, E, T, hp, hs, depth);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;

	vvi E(n+1, vi());
	vvi T(n+1, vi());
	for (int i = 1; i <= n; ++i) {
		int p, t;
		cin >> p >> t;
		if (p == -1) { p = 0; t = NONE; }
		E[p].push_back(i);
		T[p].push_back(t);
	}

	vi hp(n+1, -1), hs(n+1, -1), depth(n+1, 0);
	dfs1(0, E, T, hp, hs, depth);
	HLD hld(E);

	int q;
	cin >> q;
	while (q--) {
		int type, u, v;
		cin >> type >> u >> v;
		if (type == 1) {
			// is v a special case of u?
			int l = hld.lca(u, v);
			bool yes = (l == u && v != u && depth[hs[v]] <= depth[u]);
			cout << (yes ? "YES" : "NO") << '\n';
		} else {
			// is v a part of u?
			int l = hld.lca(u, v);
			bool yes = (l != v && depth[hp[v]] <= depth[l]
				&& depth[hs[u]] <= depth[l]);
			cout << (yes ? "YES" : "NO") << '\n';
		}
	}

	return 0;
}
