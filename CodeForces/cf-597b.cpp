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

struct Order {
	int l, r;
	Order() : l(0), r(0) { }
	Order(int _l, int _r) : l(_l), r(_r) { }
	bool operator<(const Order &rhs) const {
		return l < rhs.l;
	}
};


template <class T, T(*op)(T, T), T ident>
struct SegmentTree {
	struct Node {
		T val;
		int l, r;
		Node(T _val, int _l, int _r) : val(_val), l(_l), r(_r) { };
	};
	int n;
	vector<Node> tree;
	SegmentTree(int p/*, vector<T> &init*/) : n(1 << p) { // Needs 2^p leafs
		tree.assign(2 * n, Node(ident, 0, n - 1));
		for (int j = 1; j < n; ++j) {
			int m = (tree[j].l + tree[j].r) / 2;
			tree[2*j].l = tree[j].l;
			tree[2*j].r = m;
			tree[2*j+1].l = m + 1;
			tree[2*j+1].r = tree[j].r;
		}
//		for (int j = 2 * n - 1; j > 0; --j) {
//			if (j >= n) tree[j].val = init[j - n];
//			else tree[j].val = op(tree[2*j].val, tree[2*j+1].val);
//		}
	}
	void update(int i, T val) {
		for (tree[i+n].val = val, i = (i+n)/2; i > 0; i /= 2)
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

int mymax(int l, int r) { return l > r ? l : r; }

int main() {
	
	int n;
	scanf("%d", &n);
	
	vector<Order> ods;
	map<int, int> time;
	for (int i = 0; i < n; ++i) {
		int l, r;
		scanf("%d %d", &l, &r);
		ods.push_back(Order(l, r));
		if (time.find(l) == time.end())
			time.insert({l, 0});
		if (time.find(r) == time.end())
			time.insert({r, 0});
	}
	
	sort(ods.begin(), ods.end());
	int id = 1;
	for (auto it = time.begin(); it != time.end(); ++it) {
		it->second = id;
		id++;
//		cerr << it->first << it->second << endl;
	}
	
	int p = 1;
	while ((1<<p) < 2 * n) p++;
	
	SegmentTree<int, mymax, 0> st(p);
	int rm = 0;
	for (int i = 0; i < n; ++i) {
		int tm = time[ods[i].l];
		int mx = st.query(0, tm - 1) + 1;
//		cerr << mx << endl;
		if (mx > rm) rm = mx;
		
		int tm2 = time[ods[i].r];
		int mx2 = st.query(tm2, tm2);
		st.update(tm2, mx > mx2 ? mx : mx2);
	}
	
	cout << rm << endl;
	
	return 0;
}
