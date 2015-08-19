#include <iostream>
#include <vector>

using namespace std;

class UnionFind {
private:
	vector<int> par, rank, size;
	int c;
public:
	UnionFind(int n) {
		size.assign(n, 1);
		c = n;
		rank.assign(n, 0);
		par.assign(n, 0);
		for (int i = 0; i < n; ++i) par[i] = i;
	}

	int find(int i) { return (par[i] == i ? i : (par[i] = find(par[i]))); }
	bool same(int i, int j) { return (find(i) == find(j)); }
	int count() { return c; }
	int size_of(int i) { return size[find(i)]; }
	
	void union_set(int i, int j) {
		if ((i = find(i)) == (j = find(j))) return;
		c--;
		if (rank[i] > rank[j]) swap(i, j);
		par[i] = j;
		size[j] += size[i];
		if (rank[i] == rank[j]) rank[j]++;
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n, q;
	cin >> n >> q;
	UnionFind uf(n);
	vector<int> box(n, -1), resides(n, -1);
	for (int i = 0; i < n; ++i) {
		box[i] = i;
		resides[i] = i;
	}
	for (int i = 0; i < q; ++i) {
		int s, t;
		cin >> s >> t;
		s--; t--;
		int set_s = box[s];
		int set_t = box[t];
		resides[uf.find(set_s)] = t;
		if (set_t == -1) {
			box[t] = set_s;
		} else {
			uf.union_set(set_s, set_t);
			box[t] = uf.find(set_s);
		}
		box[s] = -1;
	}

	for (int i = 0; i < n; ++i) {
		cout << (resides[uf.find(i)] + 1) << " \n"[i == n - 1];
	}
	cout << flush;

	return 0;
}
