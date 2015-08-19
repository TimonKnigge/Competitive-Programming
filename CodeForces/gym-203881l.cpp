#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <random>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

const ll LLINF = 9000000000000000000LL;

class UnionFind {
private:
	vi par, rank, size; int c;
public:
	UnionFind(int n) : par(n), rank(n, 0), size(n, 1), c(n) {
		for (int i = 0; i < n; ++i) par[i] = i;
	}
	int find(int i) { return (par[i] == i ? i : (par[i] = find(par[i]))); }
	bool same(int i, int j) { return find(i) == find(j); }
	void union_set(int i, int j) {
		if ((i = find(i)) == (j = find(j))) return;
		c--;
		if (rank[i] > rank[j]) swap(i, j);
		par[i] = j; size[j] += size[i];
		if (rank[i] == rank[j]) rank[j]++;
	}
	void reset() {
		for (int i = 0; i < par.size(); ++i) {
			par[i] = i;
			size[i] = i;
			rank[i] = 0;
			c = par.size();
		}
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, m, s, t;
	cin >> n >> m >> s >> t;
	s--; t--;
	
	vector<vector<pair<int, ll> > > e(n);
	ll bigor = 0;
	for (int i = 0; i < m; ++i) {
		int v, u; ll ww;
		cin >> v >> u >> ww;
		v--; u--;
		e[u].push_back({v, ww});
		e[v].push_back({u, ww});
		bigor = bigor | ww;
	}

	ll ans = 0LL, forb = 0LL;
	vector<int> check(n, 41);
	UnionFind uf(n);
	for (int k = 40; k >= 0; --k) {
		ll sh = 1LL << k;
		if ((sh & bigor) == 0) continue;
		queue<int> q;
		q.push(s);
		q.push(t);
		check[s] = k + 1;
		check[t] = -k - 1;
		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (int j = 0; j < e[u].size(); ++j) {
				ll w = e[u][j].second;
				int v = e[u][j].first;
				if (check[v] == check[u]) continue;
				if ((sh & w) == sh || (forb & w) != 0)
					continue;
				check[v] = check[u];
				uf.union_set(u, v);
				q.push(v);
			}
			if (uf.same(s, t)) break;
		}
		if (!uf.same(s, t)) {
			ans = ans | sh;
		} else {
			forb = forb | sh;
		}
		if (k > 0) uf.reset();
	}
	
	cout << ans << endl;
	
	return 0;
}

