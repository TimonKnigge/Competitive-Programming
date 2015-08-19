#include <iostream>
#include <iomanip>
#include <vector>	       
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <bitset>
#include <algorithm>
#include <functional>
#include <string>
#include <string.h>  // Include for memset!
#include <complex>
#include <random>
#define _USE_MATH_DEFINES
#include <math.h>

const int INF = 2000000000;	                 // 9
const long long LLINF = 9000000000000000000LL;  // 18
const long double LDINF = 1e300;

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<bool> vb;
typedef long long ll;
typedef long double ld;

struct CentroidDecomposition {
	vvi cd, &e;
	vvii dist;
	vb tocheck, col;
	vi size, p;
	vector<set<ii>> distances;
	int root;
	CentroidDecomposition(vvi &tree) : e(tree) {
		int V = e.size();
		tocheck.assign(V, true);
		col.assign(V, false);
		cd.assign(V, vi());
		p.assign(V, -1);
		size.assign(V, 0);
		dist.assign(V, vii());
		distances.assign(V, set<ii>());
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

	void dfs2(int u, int d, int s, int p) {
		if (!tocheck[u]) return;
		dist[u].push_back({s, d});
		for (int v : e[u]) {
			if (!tocheck[v] || v == p) continue;
			dfs2(v, d + 1, s, u);
		}
	}

	int closest(int u) {
		int best = INF;
		for (ii vd : dist[u]) {
			int v = vd.first, d = vd.second;
			if (distances[v].size() > 0) {
				auto it = distances[v].begin();
				int nd = d + it->first;
				best = best < nd ? best : nd;
			}
		}
		if (best == INF) best = -1;
		return best;
	}

	void toggle(int u) {
		col[u] = !col[u];
//		cerr << "Toggled " << u << " to " << col[u] << endl;
		for (ii vd : dist[u]) {
			int v = vd.first, d = vd.second;
			if (col[u])
				distances[v].insert({d, u});
			else
				distances[v].erase({d, u});
//			cerr << v << ' ' << d << endl;
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
			if (V - 1 - size[u] > V / 2 && p[u] != -1
				&&tocheck[p[u]]) nu = p[u];
			if (nu != -1) u = nu; else break;
		}
		for (int v = p[u]; v != -1 && tocheck[v]; v = p[v])
			size[v] -= 1 + size[u];
		
		// Fix dist for each vertex in our subtree:
		dfs2(u, 0, u, -1);
		
		
		tocheck[u] = false;
		for (int v : e[u]) {
			if (!tocheck[v]) continue;
			int V2 = 1 + size[v];
			if (v == p[u]) V2 = V - 1 - size[u];
			cd[u].push_back(decompose(v, V2));
		}
		return u;
	}
};

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N;
	cin >> N;
	vvi tree(N, vi());
	for (int i = 0; i < N - 1; ++i) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		tree[a].push_back(b);
		tree[b].push_back(a);
	}

	CentroidDecomposition cd(tree);
	int Q;
	cin >> Q;
	for (int q = 1; q <= Q; ++q) {
		int t, u;
		cin >> t >> u;
		u--;
		if (t == 0) {
			// Recolor u
			cd.toggle(u);
		} else {
			cout << cd.closest(u) << '\n';
//			cout << flush;
		}
	}
	cout << flush;
	
	return 0;
}
