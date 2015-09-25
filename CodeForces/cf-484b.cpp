#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

template <class T, T(*op)(T, T), T ident>
struct SegmentTree {
	struct Node {
		T val;
		int l, r;
		Node(T _val, int _l, int _r) : val(_val), l(_l), r(_r) { };
	};
	int n;
	vector<Node> tree;
	SegmentTree(int p, vector<T> &init) : n(1 << p) { // Needs 2^p leafs
		tree.assign(2 * n, Node(ident, 0, n - 1));
		for (int j = 1; j < n; ++j) {
			int m = (tree[j].l + tree[j].r) / 2;
			tree[2*j].l = tree[j].l;
			tree[2*j].r = m;
			tree[2*j+1].l = m + 1;
			tree[2*j+1].r = tree[j].r;
		}
		for (int j = 2 * n - 1; j > 0; --j) {
			if (j >= n) tree[j].val = init[j - n];
			else tree[j].val = op(tree[2*j].val, tree[2*j+1].val);
		}
	}
	void update(int i, T val) {
		for (tree[i+n].val = val, i = (i+n)/2; i > 1; i /= 2)
			tree[i].val = op(tree[2*i].val, tree[2*i+1].val);
	}
	T query(int l, int r) {
		T lhs = T(ident), rhs = T(ident);
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if   (l&1)  lhs = op(lhs, tree[l++].val);
			if (!(r&1)) rhs = op(tree[r--].val, rhs);
		}
		return op(l == r ? op(lhs, tree[l].val) : lhs, rhs);
	}
};

const int INF = 1e8;
const int NINF = -1e8;
int mymax(int l, int r) { return l < r ? r : l; }

int main() {
	int n;
	scanf("%d", &n);
	
	vector<int> init(1 << 20, NINF);
	int M = 0;
	for (int i = 0; i < n; ++i) {
		int x;
		scanf("%d", &x);
		if (x > M) M = x;
		init[x] = x;
	}
	
	SegmentTree<int, mymax, NINF> st(20, init);
	int best = 0;
	for (int d = 2; d <= M; ++d) {
		if (init[d] == NINF) continue;
		for (int r = d; r <= M; r += d) {
			int mx = st.query(r, min(r + d - 1, M));
			if (mx == NINF) continue;
			if (mx % d > best) {
				best = mx % d;
			}
		}
	}
	
	printf("%d\n", best);
	
	return 0;
}
