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

struct UnionFind {
	vi par, rank, size; int c;
	UnionFind(int n) : par(n), rank(n,0), size(n,1), c(n) {
		for (int i = 0; i < n; ++i) par[i] = i;
	}

	int find(int i) { return (par[i] == i ? i : (par[i] = find(par[i]))); }
	bool same(int i, int j) { return find(i) == find(j); }
	int get_size(int i) { return size[find(i)]; }
	int count() { return c; }

	void merge(int i, int j) {
		if ((i = find(i)) == (j = find(j))) return;
		c--;
		if (rank[i] > rank[j]) swap(i, j);
		par[i] = j; size[j] += size[i];
		if (rank[i] == rank[j]) rank[j]++;
	}
};

ll getcomplete(ll n) {
	return n * (n - 1LL) / 2LL;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, m, k;
	cin >> n >> m >> k;
	
	vi c(k, 0LL);
	for (ll &v : c) cin >> v, --v;
	
	UnionFind uf(n);
	vi internal(n, 0LL);
	while (m--) {
		int u, v;
		cin >> u >> v;
		--u; --v;
		u = uf.find(u);
		v = uf.find(v);
		if (!uf.same(u, v)) {
			uf.merge(u, v);
			internal[uf.find(u)] = internal[u] + internal[v];
		}
		++internal[uf.find(u)];
	}
	
	ll ans = 0LL;
	int largest = -1;
	vb seen(n, false);
	for (ll v : c) {
		v = uf.find(v);
		seen[v] = true;
		ans += getcomplete(uf.get_size(v)) - internal[v];
		if (largest < 0 || uf.get_size(v) > uf.get_size(largest))
			largest = v;
	}

	for (int i = 0; i < n; ++i) {
		int v = uf.find(i);
		if (seen[v]) continue;
		seen[v] = true;
		ans += uf.get_size(largest) * uf.get_size(v);
		uf.merge(largest, v);
	}
	
	cout << ans << endl;
	
	return 0;
}
