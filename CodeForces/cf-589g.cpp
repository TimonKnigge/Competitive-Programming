#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;

using ll = long long;

template <class T, T(*op)(T, T)>
struct SegmentTree {
	struct Node {
		T val;
		int l, r;
		Node(T _val, int _l, int _r) : val(_val), l(_l), r(_r) { };
	};
	int n;
	vector<Node> tree;
	SegmentTree(int p, vector<T> &init) : n(1 << p) { // Needs 2^p leafs
		tree.assign(2 * n, Node({0LL, 0}, 0, n - 1));
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
		for (tree[i+n].val = val, i = (i+n)/2; i > 0; i /= 2)
			tree[i].val = op(tree[2*i].val, tree[2*i+1].val);
	}
	T query(int l, int r) {
		T lhs = T({0LL, 0}), rhs = T({0LL, 0});
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if   (l&1)  lhs = op(lhs, tree[l++].val);
			if (!(r&1)) rhs = op(tree[r--].val, rhs);
		}
		return op(l == r ? op(lhs, tree[l].val) : lhs, rhs);
	}
};

using lli = pair<ll, int>;
lli sm(lli a, lli b) { return {a.first + b.first, a.second + b.second}; }

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	
	vector<pair<ll, int> > t(m, {0LL, 0});
	for (int i = 0; i < m; ++i) {
		int x;
		scanf("%d", &x);
		t[i] = {x, i};
	}
	
	vector<pair<pair<int, int>, int> > dr(n, {{0, 0}, 0});
	for (int i = 0; i < n; ++i) {
		int di, ri;
		scanf("%d %d", &di, &ri);
		dr[i] = {{di, ri}, i};
	}
	
	sort(t.begin(), t.end());
	sort(dr.begin(), dr.end());
	
	int p = 1;
	while ((1LL << p) < m) p++;
	vector<lli> init(1LL << p, {0LL, 0LL});
	SegmentTree<lli, sm> st(p, init);
	
	int dayind = m - 1;
	vector<ll> ans(n, 0LL);
	for (int i = n - 1; i >= 0; --i) {
		ll di = dr[i].first.first, ri = dr[i].first.second;
		int ind = dr[i].second;
		// Insert all relevant days
		while (dayind >= 0 && t[dayind].first > di) {
			st.update(t[dayind].second, {t[dayind].first, 1});
			dayind--;
//			cerr << "Inserting " << (t[dayind + 1].second) << endl;
//	cerr << "INTERNAL STATE" <<endl;
//	for (int j = 1; j < st.tree.size(); ++j)
//		cerr << " (" << st.tree[j].val.first << ' ' << st.tree[j].val.second<<")";
//	cerr<<endl;
		}
		
//		cerr << "Checking " << ind << endl;
		
		// Binary search the answer for ind
		lli whole = st.query(0, (1LL << p) - 1);
//		cerr << " (" << whole.first << ", " << whole.second <<")" <<endl;
		if (whole.first < ll(whole.second) * di + ri) {
			ans[ind] = 0LL;
			continue;
		} else {
			int l = 0, r = (1LL << p) - 1;
			while (l < r) {
				int mid = (l + r) / 2;
				whole = st.query(0, mid);
//	cerr << "[" << 0 << ", " << mid <<"] -> " << whole.first << ", " << whole.second<<endl;
				if (whole.first < ll(whole.second) * di + ri)
					l = mid + 1;
				else r = mid;
			}
			ans[ind] = l + 1;
		}
	}
	
	for (int i = 0; i < n; ++i)
		cout << ans[i] << " \n"[i == n - 1];
	cout << flush;
	
	return 0;
}

