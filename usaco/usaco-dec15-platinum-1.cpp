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
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;


struct HLD {
	int V,T; vi &p; vvi &childs;	// Size; dfs-time; input parent/childs
	vi pr, size, heavy;		// path-root; size of subtrees; heavy child
	vi t_in, t_out;			// dfs in and out times
	HLD(vvi &childs, vi &p, int root = 0) :
		V(p.size()), T(0), p(p), childs(childs), pr(V,-1),
		size(V,-1), heavy(V,-1), t_in(V,-1), t_out(V,-1) {
			dfs(root); set_pr(root,0);
		}
	int dfs(int u){
		size[u] = 1; t_in[u] = T++;
		int m = -1, mi = -1, s;		// max, max index, size of subtree
		for(auto &v : childs[u]){
			size[u] += s = dfs(v);
			if(s > m) m=s, mi = v;
		}
		heavy[u] = mi; t_out[u] = T++; return size[u];
	}
	void set_pr(int u, int r){		// node, path root
		pr[u] = r;
		for(auto &v : childs[u]) set_pr(v, heavy[u] == v ? r : v);
	}
	bool is_parent(int p, int u){	// test whether p is a parent of u
		return t_in[p] <= t_in[u] && t_out[p] >= t_out[u];
	}
	int lca(int u, int v){
		while(!is_parent(pr[v],u)) v = p[pr[v]];
		while(!is_parent(pr[u],v)) u = p[pr[u]];
		return is_parent(u,v) ? u : v;
	}
};

void direct(int u, vi &p, vvi &ch, vvi &e) {
	for (int v : e[u]) {
		if (v == p[u]) continue;
		p[v] = u;
		ch[u].push_back(v);
		direct(v, p, ch, e);
	}
}

void dfs(int u, vi &par, vvi &ch, vi &upinc, vi &upexc, vi &flo) {
	flo[u] = upinc[u];
	for (int v : ch[u]) {
		dfs(v, par, ch, upinc, upexc, flo);
		flo[u] += upexc[v] + flo[v];
	}
}

int main() {
	
	freopen("maxflow.in", "r", stdin);
	freopen("maxflow.out", "w", stdout);
	
	int N, K;
	scanf("%d %d", &N, &K);
	vvi e(N, vi());
	for (int i = 0; i < N - 1; ++i) {
		int x, y;
		scanf("%d %d", &x, &y);
		--x; --y;
		e[x].push_back(y);
		e[y].push_back(x);
	}
	
	vi par(N, -1);
	vvi ch(N, vi());
	direct(0, par, ch, e);
	
	HLD hld(ch, par);
	
	vi upinc(N, 0), upexc(N, 0);
	while (K--) {
		int a, b;
		scanf("%d %d", &a, &b);
		--a; --b;
		int l = hld.lca(a, b);
		if (l != a && l != b) {
			upinc[a]++;
			upinc[b]++;
			upinc[l]--;
			upexc[l]--;
		}
		if (l == a) {
			upinc[b]++;
			upexc[a]--;
		}
		if (l == b) {
			upinc[a]++;
			upexc[b]--;
		}
	}
	
	vi flo(N, 0);
	dfs(0, par, ch, upinc, upexc, flo);
	
	int best = 0;
	for (int i = 0; i < N; ++i)
		best = max(best, flo[i]);
	
	cout << best << endl;
	
	return 0;
}
