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

int M[2500][2500];

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
	
	int N;
	scanf("%d", &N);
	
	bool magic = true;
	vector<pair<int, pair<int, int> > > v;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			scanf("%d", &M[i][j]);
			if (i == j) magic = magic && M[i][j] == 0;
			if (i > j)  magic = magic && M[i][j] == M[j][i];
			if (j < i)  v.push_back({M[i][j], {i, j}});
		}
	}
	
	sort(v.begin(), v.end());
	
	if (magic) {
		UnionFind uf(N);
		size_t l = 0, r = 0;
		while (l < v.size()) {
			r = l;
			while (r < v.size() && v[l].first == v[r].first)
				++r;
			
			for (size_t i = l; i < r; ++i)
				magic = magic && !uf.same(v[i].second.first, v[i].second.second);
			
			for (size_t i = l; i < r; ++i)
				uf.merge(v[i].second.first, v[i].second.second);
			
			l = r;
		}
	}
	
	cout << (magic ? "MAGIC" : "NOT MAGIC") << endl;
	
	return 0;
}
