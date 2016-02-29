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

ll sum(ll l, ll r) { return l+r; }

int main() {
	
	int N, K, A, B, Q;
	scanf("%d %d %d %d %d", &N, &K, &A, &B, &Q);
	
	vi tmp(N, 0LL);
	SegmentTree<ll, sum, 0LL> at(tmp), bt(tmp);
	
	while (Q--) {
		int t;
		scanf("%d", &t);
		if (t == 1) {
			int d, a;
			scanf("%d %d", &d, &a);
			at.update(d - 1, min(ll(A), a + at.query(d-1, d-1)));
			bt.update(d - 1, min(ll(B), a + bt.query(d-1, d-1)));
		} else {
			int p;
			scanf("%d", &p);
			--p;
			ll ans = 0LL;
			if (p > 0)
				ans += bt.query(0, p - 1);
			p += K;
			if (p < N)
				ans += at.query(p, N - 1);
			cout << ans << '\n';
		}
	}
	
	return 0;
}
