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

// Order Statistics Tree
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class TIn, class TOut>
using order_tree = tree<
	TIn, TOut, less<TIn>, // key, value types. TOut can be null_type
	rb_tree_tag, tree_order_statistics_node_update>;
// find_by_order(int r) (0-based)
// order_of_key(TIn v)
// use key pair<Tin,int> {value, counter} for multiset/multimap

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

ll mx(ll l, ll r) { return l > r ? l : r; }

int main() {
	
	int N;
	scanf("%d", &N);
	
	vi A(N, 0LL);
	for (int i = 0, v; i < N; ++i) {
		scanf("%d", &v);
		A[i] = v;
	}
	
	vvi opt(N, vi(N, LLINF)), uniques(N, vi(N, 0LL));
	vi min_index(N, 0LL), earlier(N, 0LL), later(N, 0LL);
	order_tree<ll, null_type> elems;
	
	for (int l = N - 1; l >= 0; --l) {
		
		elems.clear();
		elems.insert(A[l]);

		opt[l][l] = 0LL;
		uniques[l][l] = 1LL;
		earlier[l] = 0LL;
		later[l] = 0LL;

		for (int r = l + 1; r < N; ++r) {
			
			earlier[r] = elems.order_of_key(A[r]);
			later[r] = 0LL;
			elems.insert(A[r]);
			uniques[l][r] = elems.size();
			
			// Are there duplicates?
			if (uniques[l][r] < r - l + 1) {
				opt[l][r] = LLINF;
				continue;
			}
			
			min_index[r] = r;
			for (int i = r - 1; i >= l; --i) {
				if (A[r] < A[i]) ++later[i];
				if (A[min_index[i+1]] < A[i])
					min_index[i] = min_index[i + 1];
				else	min_index[i] = i;
			}
			
			// l<=k<r, split into [l, k] and [k+1, r]

			int l_min_index = l, r_min_index;
			for (int k = l; k < r; ++k) {
				ll cost = opt[l][k] + opt[k + 1][r]
					+ r - l + 1;
				
				if (A[k] < A[l_min_index])
					l_min_index = k;
				r_min_index = min_index[k + 1];
				
				if (A[l_min_index] < A[r_min_index])
					cost -= earlier[r_min_index];
				else	cost -= later[l_min_index];
				
//				ll lm = *lseg.begin(),
//				   rm = *rseg.begin();
//				if (lm < rm)
//					cost -= lseg.order_of_key(rm);
//				else	cost -= rseg.order_of_key(lm);
				
				opt[l][r] = min(opt[l][r], cost);
			}
		}
	}
	
	SegmentTree<ll, mx, 0LL> max_tree(A);

	vi dp(N, LLINF);
	for (int r = 0; r < N; ++r)
		if (uniques[0][r] == r + 1
			&& max_tree.query(0, r) == r + 1)
			dp[r] = opt[0][r];
	
	for (int r = 1; r < N; ++r)
		for (int l = 1; l <= r; ++l)
			if (opt[l][r] < LLINF && dp[l - 1] < LLINF
				&& uniques[l][r] == r - l + 1
				&& max_tree.query(l, r) == r - l + 1)
				dp[r] = min(dp[r], dp[l - 1] + opt[l][r]);
	
	if (dp[N - 1] < LLINF)
		cout << dp[N - 1] << endl;
	else	cout << "impossible\n";
	
	return 0;
}
