#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

struct HLD {
	int V,T; vi &p; vvi &childs;	// Size; dfs-time; input parent/childs
	vi pr, size, heavy;		// path-root; size of subtrees; heavy child
	vi t_in, t_out;			// dfs in and out times
	HLD(vvi &childs, vi &p) : V(p.size()), T(0), p(p), childs(childs),
	pr(V,-1), size(V,-1), heavy(V,-1), t_in(V,-1), t_out(V,-1) {
		dfs(0); set_pr(0,0);
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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N;
	cin >> N;
	vi p(N, -1); vvi e(N, vi());
	
	for (int i = 0; i < N; ++i) {
		int M;
		cin >> M;
		for (int j = 0; j < M; ++j) {
			int x;
			cin >> x;
			e[i].push_back(x);
			p[x] = i;
		}
	}
	
	HLD hld(e, p);
	
	int Q;
	cin >> Q;
	for (int q = 0; q < Q; ++q) {
		int u, v;
		cin >> u >> v;
		cout << hld.lca(u, v) << '\n';
	}
	cout << flush;
	
	return 0;
}
