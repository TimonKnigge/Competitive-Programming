#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>

using namespace std;

typedef long long ll;

#define LC(n) (2 * (n))
#define RC(n) (2 * (n) + 1)
#define PA(n) ((n) >> 1)

class SegmentTree {
	struct Node {
		vector<int> st;
		int l, r;
		Node(int _l, int _r) : l(_l), r(_r) { };
	};
	int n;
	vector<Node> tree;
public:
	SegmentTree(int p, vector<int> &init) {
		this->n = (1 << p);
		tree.assign(2 * n, Node(0, 0));
		tree[1].l = 0; tree[1].r = n - 1;
		for (int j = 1; j < n; ++j) {
			int m = (tree[j].l + tree[j].r) / 2;
			tree[LC(j)].l = tree[j].l;
			tree[LC(j)].r = m;
			tree[RC(j)].l = m + 1;
			tree[RC(j)].r = tree[j].r;
		}
		for (int j = tree.size() - 1; j > 0; --j) {
			if (j >= n) {
				tree[j].st.push_back(init[j - n]);
			} else {
				std::merge(
					tree[LC(j)].st.begin(),
					tree[LC(j)].st.end(),
					tree[RC(j)].st.begin(),
					tree[RC(j)].st.end(),
					std::back_inserter(tree[j].st));
			}
		}
	}

	int query(int l, int r, int k) {
		int ret = 0;
		l += n; r += n;
		while (l < r) {
			if (l & 1) {
				ret += tree[l].st.end() - upper_bound(tree[l].st.begin(), tree[l].st.end(), k);
				l++;
			}
			if (!(r & 1)) {
				ret += tree[r].st.end() - upper_bound(tree[r].st.begin(), tree[r].st.end(), k);
				r--;
			}
			l >>= 1; r >>= 1;
		}
		if (l == r) {
			ret += tree[l].st.end() - upper_bound(tree[r].st.begin(), tree[r].st.end(), k);
		}
		return ret;
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, p = 2;
	cin >> n;
	while ((1 << p) < n) ++p;
	vector<int> a((1 << p), 0);
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	
//	cerr << "Building segtree.." << endl;
	SegmentTree st(p, a);

	int q, la = 0;
	cin >> q;
	for (int z = 0; z < q; ++z) {
		int i, j, k;
		cin >> i >> j >> k;
		i ^= la; j ^= la; k ^= la;
		i--; j--;
		la = st.query(i, j, k);
		cout << la << endl;
	}
	cout << flush;
	
	return 0;
}
