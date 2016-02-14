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

template <class T, T(*op)(T, T), T ident>
struct SegmentTree {
	int n; vector<T> tree;
	SegmentTree(vector<T> &init) : n(init.size()), tree(2 * n, ident) {
		copy(init.begin(), init.end(), tree.begin() + n);
		for (int j = n - 1; j > 0; --j)
			tree[j] = op(tree[2*j], tree[2*j+1]);
	}
	void update(int i, T val) {
		for (tree[i+n] = val, i = (i+n)/2; i > 0; i /= 2)
			tree[i] = op(tree[2*i], tree[2*i+1]);
	}
	T query(int l, int r) {
		T lhs = T(ident), rhs = T(ident);
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (  l&1 ) lhs = op(lhs, tree[l++]);
			if (!(r&1)) rhs = op(tree[r--], rhs);
		}
		return op(l == r ? op(lhs, tree[l]) : lhs, rhs);
	}
};

int mgcd(int l, int r) {
	if (l == -1) return r;
	if (r == -1) return l;
	while (l) {
		r %= l;
		swap(l, r);
	}
	return r;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int Q;
	scanf("%d", &Q);
	
	vector<int> tmp(Q, -1);
	SegmentTree<int, mgcd, -1> st(tmp);
	
	set<pair<int, int> > el;
	for (int q = 0; q < Q; ++q) {
		char c;
		int v;
		scanf(" %c %d", &c, &v);
		if (c == '+') {
			st.update(q, v);
			el.insert({v, q});
		} else {
			auto it = el.lower_bound({v, -1});
			st.update(it->second, -1);
			el.erase(it);
		}
		int qr = st.query(0, Q - 1);
		cout << (qr == -1 ? 1 : qr) << '\n';
	}
	cout << flush;
	
	return 0;
}
