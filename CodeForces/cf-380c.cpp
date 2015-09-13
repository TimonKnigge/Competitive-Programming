#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <list>
#include <bitset>
#include <algorithm>
#include <functional>
#include <string>
#include <cstring>
#define _USE_MATH_DEFINES
#include <math.h>
#include <complex>
#include <random>

using namespace std;

typedef pair<int, int> ii;
typedef pair<ii, int> iii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<bool> vb;
typedef long long ll;
typedef long double ld;

#define INF 2000000000
#define LLINF 9000000000000000000LL

template <class T, T(*op)(T, T), int ident>
struct SegmentTree {
	struct Node {
		T val;
		int l, r;
		Node(T _val, int _l, int _r) : val(_val), l(_l), r(_r) { };
	};
	int n;
	vector<Node> tree;
	SegmentTree(int p, vector<T>& init) : n(1 << p) { // The segment tree will support 2^p leafs
		tree.assign(2 * n, Node(T(ident), 0, n - 1));
		for (int j = 1; j < n; ++j) {
			int m = (tree[j].l + tree[j].r) / 2;
			tree[2*j].l = tree[j].l;
			tree[2*j].r = m;
			tree[2*j+1].l = m + 1;
			tree[2*j+1].r = tree[j].r;
		}
		for (int j = 2 * n - 1; j > 0; --j) {
			if (j >= n) tree[j].val = init[j - n];
			else        tree[j].val = op(tree[2*j].val, tree[2*j+1].val);
		}
	}
	void update(int i, T val) {
		for(tree[i+n].val = val, i = (i+n)/2; i > 1; i /= 2)
			tree[i].val = op(tree[2*i].val, tree[2*i+1].val);
	}
	T query(int l, int r) {
		T lhs = T(ident), rhs = T(ident);
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if   (l & 1)  lhs = op(lhs, tree[l++].val);
			if (!(r & 1)) rhs = op(tree[r--].val, rhs);
		}
		return op(l == r ? op(lhs, tree[l].val) : lhs, rhs);
	}
};

struct pinfo {
	int open, closed, full;
	pinfo() : open(0), closed(0), full(0) { };
	pinfo(int ident) : open(0), closed(0), full(0) { };
	pinfo(int _o, int _c, int _f) : open(_o), closed(_c), full(_f) { };
};

pinfo combine(pinfo lhs, pinfo rhs) {
	int add = min(lhs.open, rhs.closed);
	return pinfo(lhs.open + rhs.open - add, 
		lhs.closed + rhs.closed - add, 
		lhs.full + rhs.full + 2 * add);
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	string s;
	cin >> s;
	int p = int(ceil(log2(s.length())));
	vector<pinfo> init(1 << p);
	for (size_t i = 0; i < size_t(1 << p); ++i) {
		if (i < s.length())
			init[i] = pinfo((s[i] == '(' ? 1 : 0), (s[i] == ')' ? 1 : 0), 0);
		else init[i] = pinfo(0, 0, 0);
	}
	SegmentTree<pinfo, combine, 0> st(p, init);

	int q;
	cin >> q;
	for (int i = 0; i < q; ++i) {
		int l, r;
		cin >> l >> r;
		l--; r--;
		cout << st.query(l, r).full << endl;
	}

	return 0;
}
