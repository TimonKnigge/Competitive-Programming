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

char board[1000 * 1000];
int weight[1000 * 1000];
int rep(int x, int y) { return x + 1000 * y; }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, m, k;
	cin >> n >> m >> k;
	
	for (int x = 0; x < n; ++x) {
		for (int y = 0; y < m; ++y) {
			cin >> board[rep(x, y)];
		}
	}
	
	int dir[8] = {0, 1, 0, -1, 1, 0, -1, 0};
	
	for (int x = 1; x < n - 1; ++x) {
		for (int y = 1; y < m - 1; ++y) {
			weight[rep(x, y)] = 0;
			if (board[rep(x, y)] == '*') continue;
			for (int i = 0; i < 4; ++i)
				if (board[rep(x + dir[2 * i], y + dir[2 * i + 1])]
					== '*') weight[rep(x, y)]++;
		}
	}
	
	UnionFind uf(1000 * 1000);
	for (int x = 1; x < n - 1; ++x) {
		for (int y = 1; y < m - 1; ++y) {
			if (board[rep(x, y)] == '*') continue;
			for (int i = 0; i < 4; ++i) {
				int ox = x + dir[2 * i];
				int oy = y + dir[2 * i + 1];
				if (board[rep(ox, oy)] == '*') continue;
				if (uf.same(rep(x, y), rep(ox, oy))) continue;
				int pict = weight[uf.find(rep(x, y))] 
					 + weight[uf.find(rep(ox, oy))];
				uf.merge(rep(x, y), rep(ox, oy));
				weight[uf.find(rep(x, y))] = pict;
			}
		}
	}

	while (k--) {
		int x, y;
		cin >> x >> y;
		x--; y--;
		cout << weight[uf.find(rep(x, y))] << '\n';
	}
	cout << flush;
	
	return 0;
}
