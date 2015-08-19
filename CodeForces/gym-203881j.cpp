#include <iostream>
#include <vector>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;

struct CentroidDecomposition {
	vvi &e;
	vb tocheck;
	vi size, p;
	int root;
	vvi cd, dir;
	CentroidDecomposition(vvi &tree) : e(tree) {
		int V = e.size();
		tocheck.assign(V, true);
		cd.assign(V, vi());
		dir.assign(V, vi());
		p.assign(V, -1);
		size.assign(V, 0);
		
		dfs(0);
		root = decompose(0, V);
	}
	void dfs(int u) {
		for (int v : e[u]) {
			if (v == p[u]) continue;
			p[v] = u;
			dfs(v);
			size[u] += 1 + size[v];
		}
	}

	int decompose(int _u, int V) {
		int u = _u;
		while (true) {
			int nu = -1;	
			for (int v : e[u]) {
				if (!tocheck[v] || v == p[u]) continue;
				if (1 + size[v] > V / 2) nu = v;
			}
			if (V-1-size[u] > V / 2 && p[u] != -1
				&& tocheck[p[u]]) nu = p[u];
			if (nu != -1) u = nu; else break;
		}
		for (int v = p[u]; v != -1 && tocheck[v]; v = p[v])
			size[v] -= 1 + size[u];
		tocheck[u] = false;
		for (int v : e[u]) {
			if (!tocheck[v]) continue;
			int V2 = 1 + size[v];	
			if (v == p[u]) V2 = V - 1 - size[u];
			cd[u].push_back(decompose(v, V2));
			dir[u].push_back(v);
		}
		return u;
	}
};


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int n; cin >> n;

	vector<vector<int>> e(n, vi());
	for (int i = 0; i < n - 1; ++i) {
		int u, v;
		cin >> u >> v;
		u--; v--;
		e[u].push_back(v);
		e[v].push_back(u);
	}

	CentroidDecomposition cd(e);
//	cerr << "Finished decomposition" << endl;
	int cur = cd.root, inf;
	for (int q = 1; q <= 33; ++q) {
		cout << (cur + 1) << endl;
		cin >> inf;
		inf--;
		if (inf == -1) break;
		for (int j = 0; j < cd.dir[cur].size(); ++j) {
			if (cd.dir[cur][j] == inf) {
				cur = cd.cd[cur][j];
				break;
			}
		}
	}
	
	return 0;
}

