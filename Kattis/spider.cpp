#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

typedef vector<int> vi;

class UnionFind {
private:
	vi par, rank, size; int c;
public:
	UnionFind(int n) : par(n), rank(n,0), size(n,1), c(n) {
		for (int i = 0; i < n; ++i) par[i] = i;
	}

	int find(int i) { return (par[i] == i ? i : (par[i] = find(par[i]))); }
	bool same(int i, int j) { return find(i) == find(j); }
	int get_size(int i) { return size[find(i)]; }
	int count() { return c; }

	void union_set(int i, int j) {
		if ((i = find(i)) == (j = find(j))) return;
		c--;
		if (rank[i] > rank[j]) swap(i, j);
		par[i] = j; size[j] += size[i];
		if (rank[i] == rank[j]) rank[j]++;
	}
};

typedef long long ll;

struct AdjEdge {
	int v;
	ll weight;
	bool intree = false;
	AdjEdge(int _v, ll w, bool it = false) : v(_v), weight(w), intree(it) { }
};
struct SortEdge {
	int u, i;
	ll w;
	SortEdge(int u, int i, ll w) : u(u), i(i), w(w) { }
	bool operator<(const SortEdge &o) const {
		return w < o.w;
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	while (cin >> n) {
		int m;
		cin >> m;
		
		UnionFind uf(n);
		vector<SortEdge> e;
		vector<vector<AdjEdge> > el(n, vector<AdjEdge>());
		for (int i = 0; i < m; ++i) {
			int u, l, v;
			cin >> u >> v >> l;
			u--; v--;
			e.push_back({u, int(el[u].size()), l});
			el[u].push_back({v, l});
		}
		
		sort(e.begin(), e.end());
		ll ans = 0LL, hmst = 0LL;
		for (size_t i = 0; i < e.size(); ++i) {
			int u = e[i].u, v = el[e[i].u][e[i].i].v;
			if (uf.same(u, v)) continue;
			uf.union_set(u, v);
			ans += e[i].w;
			hmst = e[i].w;
			el[u][e[i].i].intree = true;
		}
		if (uf.count() > 1) cout << "disconnected\n";
		else {
			vector<vector<AdjEdge> > mst(n, vector<AdjEdge>());
			for (int u = 0; u < n; ++u) {
				for (size_t i = 0; i < el[u].size(); ++i) {
					if (!el[u][i].intree) continue;
					mst[u].push_back(el[u][i]);
					mst[el[u][i].v].push_back({u, el[u][i].weight, el[u][i].intree});
				}
			}
			vector<vector<ll> > maxpath(n, vector<ll>(n, -1));
			for (int u = 0; u < n; ++u) {
				queue<int> q; q.push(u);
				maxpath[u][u] = 0LL;
				while (!q.empty()) {
					int v = q.front(); q.pop();
					for (AdjEdge &ed : mst[v]) {
						ll w = max(maxpath[u][v], ed.weight);
						if (maxpath[u][ed.v] == -1) {
							maxpath[u][ed.v] = w;
							q.push(ed.v);
						}
					}
				}
			}
//			for (int u = 0; u < n; ++u){for(int v = 0; v < n;++v)
//			cout << maxpath[u][v]<<'\t';cout<<endl;}
			ll bestdiff = 2 * hmst;
			for (size_t i = 0; i < e.size(); ++i) {
				int u = e[i].u, v = el[e[i].u][e[i].i].v;
				if (el[u][e[i].i].intree) continue;
				bestdiff = max(bestdiff, e[i].w + maxpath[u][v]);
			}
			cout << (ans - bestdiff) << '\n';
		}
	}
	cout << flush;
	
	return 0;
}
