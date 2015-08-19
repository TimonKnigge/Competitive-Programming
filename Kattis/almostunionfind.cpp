#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class UnionFind {
private:
	vector<int>par, rank, size;
	int c;
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
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, m;
	while (cin >> n) {
		cin >> m;
		UnionFind uf(n);
		vector<int> size(n, 1), val(n, 1), set(n, 0);
		for (int i = 0; i < n; ++i) {
			val[i] = i + 1;
			set[i] = i;
		}

		for (int i = 0; i < m; ++i) {
			int c;
			cin >> c;
			if (c == 1) { // Union p and q
				int p, q;
				cin >> p >> q;
				p--; q--;
				if (uf.same(set[p], set[q])) continue;
				int setp = uf.find(set[p]), setq = uf.find(set[q]);
				uf.union_set(set[p], set[q]);
				int new_set = uf.find(set[p]);
//				cout << val[setp] << ' ' <<val[setq]<<endl;
				size[new_set] = size[setp] + size[setq];
				val[new_set] = val[setp] + val[setq];
				set[p] = set[q] = new_set;

//cerr << "Unioned set " <<setp << " containing " << p <<" of and " <<setq << " containing " << q << ", now in " << new_set << " of size " << size[new_set] << " with sum " << val[new_set] << endl;
				
			} else if (c == 2) {
				int p, q;
				cin >> p >> q;
				p--; q--;
				if (uf.same(set[p], set[q])) continue;
				int setp = uf.find(set[p]), setq = uf.find(set[q]);
				size[setp] -= 1;
				val[setp] -= p + 1;
				set[p] = setq;
				size[setq]++;
				val[setq] += p + 1;
			} else {
				int p;
				cin >> p;
				p--;
				cout << size[uf.find(set[p])] << ' ' << val[uf.find(set[p])] << '\n';
			}
		}
		cout << flush;
	}
	
	return 0;
}

