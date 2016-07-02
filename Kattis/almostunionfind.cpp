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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, m;
	while (cin >> n) {
		cin >> m;
		UnionFind uf(n);
		
		vi val(n, 1), size(n, 1), set(n, 0);
		for (int i = 0; i < n; ++i) {
			val[i] = i + 1;
			set[i] = i;
		}
		
		while (m--) {
			int c;
			cin >> c;
			if (c == 1) { // Union p and q
				int p, q;
				cin >> p >> q;
				p--; q--;
				if (uf.same(set[p], set[q])) continue;
				int setp = uf.find(set[p]), setq = uf.find(set[q]);
				uf.merge(set[p], set[q]);
				int new_set = uf.find(set[p]);
				val[new_set] = val[setp] + val[setq];
				set[p] = set[q] = new_set;
				size[new_set] = size[setp] + size[setq];
			} else if (c == 2) {
				int p, q;
				cin >> p >> q;
				p--; q--;
				if (uf.same(set[p], set[q])) continue;
				int setp = uf.find(set[p]), setq = uf.find(set[q]);
				val[setp] -= p + 1;
				size[setp]--;
				set[p] = setq;
				val[setq] += p + 1;
				size[setq]++;
			} else {
				int p;
				cin >> p;
				p--;
				cout << size[uf.find(set[p])] << ' ' << val[uf.find(set[p])] << '\n';
			}
		}
	}
	
	return 0;
}

