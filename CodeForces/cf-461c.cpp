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
	int n; vector<T> tree;	// for binary search on ST: need 2^p length
	SegmentTree(vector<T> &init) : n(init.size()), tree(2 * n, ident) {
		copy(init.begin(), init.end(), tree.begin()+n);
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

ll add(ll l, ll r) { return l + r; }

int main() {
	
	int N, Q;
	scanf("%d %d", &N, &Q);
	
	int l = 0, r = N - 1;
	vi S(N, 1);
	bool flipped = false;
	
//	int p = 1;
//	while ((1 << p) < N) ++p;
//	cerr << "Building tree on vector of length " << S.size() << endl;
	SegmentTree<ll, add, 0LL> st( S);
//	cerr << "Made tree" << endl;
	while (Q--) {
		int x;
		scanf("%d", &x);
		if (x == 1) {
			int p;
			scanf("%d", &p);
			
			if (flipped)
				p = (r - l + 1) - p;
			
			if (p <= (r - l + 1) / 2) { // fold right
				if (flipped) flipped = false;
				for (int i = 0; i < p; ++i)
					st.update(l + p + i,
						st.query(l + p + i, l + p + i)
					      + st.query(l+p-1-i,   l+p-1-i ));
				l += p;
			} else {// fold left
				if (!flipped) flipped = true;
				for (int i = 0; i < (r - l + 1) - p; ++i)
					st.update(l + p - i - 1,
						st.query(l + p - i - 1, l + p - i - 1)
					      + st.query(l+p+i,   l+p+i ));
				r -= (r - l + 1) - p;
			}
		} else {
			int lv, rv;
			scanf("%d %d", &lv, &rv);
			if (flipped) {
				lv = (r - l + 1) - lv;
				rv = (r - l + 1) - rv;
				swap(lv, rv);
			}
			--rv;
			cout << st.query(l + lv, l + rv) << '\n';
		}

//		cerr << "  l = " << l << ", r = " << r << ", flipped = " << flipped << endl;
//		for (int i = 0; i < N; ++i) {
//			cerr  << "  ";
//			if (l == i) cerr << "[";
//			cerr << st.query(i, i);
//			if (r == i) cerr << "]";
//		}
//		cerr << endl;
	}
	cout << flush;
	
	return 0;
}
