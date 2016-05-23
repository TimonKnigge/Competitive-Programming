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

void dfs(int u, vi &dfs_in, vi &dfs_out, vi &par, vvi &E, int &time, vi &subtree, vi &depth) {
	dfs_in[u] = time++;
	for (int v : E[u]) {
		if (v == par[u]) continue;
		par[v] = u;
		depth[v] = depth[u] + 1;
		dfs(v, dfs_in, dfs_out, par, E, time, subtree, depth);
		subtree[u] += subtree[v];
	}
	dfs_out[u] = time++;
}

template <class T, T(*op)(T, T), T ident>
struct SegmentTree {
	int n; vector<T> tree;
	SegmentTree(int _n) : n(_n), tree(2 * n, ident) {
	}
	void update(int i, T val) {
		for (tree[i+n] = val, i = (i+n)/2; i > 0; i /= 2)
			tree[i] = op(tree[2*i], tree[2*i+1]);
	}
	T query(int l, int r) {
		T lhs = T(ident), rhs = T(ident);
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (  l&1 ) lhs = op(lhs, tree[l++]);
			if (!(r&1)) rhs = op(tree[r--], rhs);
		}
		return op(l == r ? op(lhs, tree[l]) : lhs, rhs);
	}
};

ll comb(ll l, ll r) {
	if (l == -1) return r;
	if (r == -1) return l;
	return l;
}

void dfs_cumulative(int u, vvi &E, vi &cumulative, vi &par) {
	for (int v : E[u]) {
		if (v == par[u]) continue;
		cumulative[v] += cumulative[u];
		dfs_cumulative(v, E, cumulative, par);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N;
	cin >> N;
	vvi byc(1e5, vi());
	vi col(N, 0LL);
	for (int i = 0; i < N; ++i) {
		cin >> col[i];
		--col[i];
		byc[col[i]].push_back(i);
	}
	
	vvi E(N, vi());
	for (int i = 0; i < N - 1; ++i) {
		int a, b;
		cin >> a >> b;
		--a; --b;
		E[a].push_back(b);
		E[b].push_back(a);
	}
	
	vi dfs_in(N, -1LL), dfs_out(N, -1LL), par(N, -1LL), subtree(N, 1LL), depth(N, 0LL);
	int time = 0;
	dfs(0, dfs_in, dfs_out, par, E, time, subtree, depth);

	HLD hld(E, 0);
	
	
	SegmentTree<ll, comb, -1LL> st(2 * N);
	
	vvi col_ch(N, vi());
	vi cumulative(N, 0LL);
	ll cols = 0LL;
	for (int c = 0; c < 1e5; ++c) {
		if (byc[c].size() == 0) continue;
		++cols;
		
		vi &v = byc[c];
		sort(v.begin(), v.end(),
			[&dfs_in](int l, int r){ return dfs_in[l] < dfs_in[r];
		});
		
		ll left = N;
		vi nopar;
		for (size_t i = 0; i < v.size(); ++i) {
			ll res = st.query(dfs_out[v[i]], 2 * N - 1);
			if (res == -1LL)
				nopar.push_back(v[i]);
			else	col_ch[res].push_back(v[i]);
			st.update(dfs_out[v[i]], v[i]);
		}
		
		for (size_t i = 0; i < v.size(); ++i) {
			vi ch;
			for (int j : E[v[i]])
				if (j != par[v[i]])
					ch.push_back(j);
			sort(ch.begin(), ch.end(),
				[&dfs_in](int l, int r){ return dfs_in[l] < dfs_in[r];
			});
			
			size_t k = 0;
			for (size_t j = 0; j < ch.size(); ++j) {
				ll ar = subtree[ch[j]], old_k = k;
				while (k < col_ch[v[i]].size()
					&& dfs_in[col_ch[v[i]][k]]
						< dfs_out[ch[j]]) {
					ar -= subtree[col_ch[v[i]][k]];
					++k;
				}
				cumulative[ch[j]] += ar;
				while (old_k < k) {
					cumulative[col_ch[v[i]][old_k]] -= ar;
					old_k++;
				}
			}
		}
		for (int i : nopar) left -= subtree[i];
		cumulative[0] += left;
		for (int i : nopar)cumulative[i] -= left;
		
		for (int u : v)
			st.update(dfs_out[u], -1LL);
	}
	
	dfs_cumulative(0, E, cumulative, par);
	
	for (int i = 0; i < N; ++i)
		cout << N * cols - cumulative[i] << '\n';
	
	return 0;
}
