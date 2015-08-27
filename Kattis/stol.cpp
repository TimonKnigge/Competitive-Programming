#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

class UnionFind {
private:
	vector<int> par, rank, size;
	int c;
public:
	UnionFind(int n) : par(n, 0), rank(n, 0), size(n, 1), c(n) {
		for (int i = 0; i < n; ++i) par[i] = i;
	}

	int find(int i) { return (par[i] == i ? i : (par[i] = find(par[i]))); }
	bool same(int i, int j) { return find(i) == find(j); }
	int get_size(int i) { return size[find(i)]; }
	void union_set(int i, int j) {
		if ((i = find(i)) == (j = find(j))) return;
		c--;
		if (rank[i] > rank[j]) swap(i, j);
		par[i] = j; size[j] += size[i];
		if (rank[i] == rank[j]) rank[j]++;
	}
	void reset() {
		c = par.size();
		for (int i = 0; i < c; ++i) {
			par[i] = i;
			size[i] = 1;
			rank[i] = 0;
		}
	}
};

int histogram(vector<int> &h, UnionFind &uf) {
	uf.reset();
	int ret = 0;
	vector<int> sh(h.size(), 0);
	priority_queue<pair<int, int> > pq; //, vector<pair<int, int> >, greater<pair<int, int> > > pq;
	for (int i = 0; i < h.size(); ++i) {
		sh[i] = h[i];
		ret = max(ret, (h[i] > 0 ? 2 * h[i] + 2 : 0));
		if (i > 0)
			pq.push({min(h[i - 1], h[i]), i - 1});
	}
	
	while (!pq.empty()) {
		int h = pq.top().first, i = pq.top().second;
		pq.pop();
		
		uf.union_set(i, i + 1);
		int w = uf.get_size(i);
		ret = max(ret, h > 0 ? 2 * (w + h) : 0);
	}
	
	return ret;
}

int main() {
	int R, C;
	scanf("%d", &R);
	scanf("%d", &C);
	
	vector<vector<bool> > b(C, vector<bool>(R, false));
	for (int i = 0; i < R; ++i) {
		for (int j = 0; j < C; ++j) {
			char c;
			scanf(" %c", &c);
			b[j][i] = (c == '.');
		}
	}

	vector<int> h(R, 0);
	UnionFind uf(R);
	int best = 0;
	for (int i = 0; i < C; ++i) {
		for (int j = 0; j < R; ++j)
			h[j] = (b[i][j] ? h[j] + 1 : 0);
		best = max(best, histogram(h, uf));
	}

	 cout << (best - 1) << endl;
	
	return 0;
}

