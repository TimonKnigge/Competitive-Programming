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

void mkmx(ll &l, ll r) { if (l < r) l = r; }

template <class T, T(*op)(T, T), T ident>
struct SegmentTree {
	int n; vector<T> tree;
	SegmentTree(int _n) : n(_n), tree(2 * n, ident) {
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
ll mx(ll l, ll r) { return max(l, r); }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N, M;
	cin >> N >> M;
	
	vvi blocks(N, vi());
	vi fst(N, 0LL);
	int lensum = 0;
	for (int i = 0; i < N; ++i) {
		int len;
		cin >> len;
		fst[i] = lensum;
		for (int j = 0; j < len; ++j) {
			int v;
			cin >> v;
			blocks[i].push_back(v);
		}
		lensum += len;
	}
	
	vvi dp(2, vi(lensum, 0LL));
	vector<SegmentTree<ll, mx, 0LL>> st(2, 
		SegmentTree<ll, mx, 0LL>(N));
	int c = 0;
	
	ll ans = 0LL;
	for (int b = 0; b < N; ++b) {
		ll best = 0LL;
		for (int i = 0; i < int(blocks[b].size()); ++i) {
			dp[c][fst[b] + i] = blocks[b][i];
			mkmx(best, blocks[b][i]);
			mkmx(ans, blocks[b][i]);
		}
		st[c].update(b, best);
	}
	
	c = 1-c;
	for (int m = 1; m < M; ++m) {
		
		for (int i = 0; i < lensum; ++i)
			dp[c][i] = 0LL;
		for (int i = 0; i < N; ++i)
			st[c].update(i, 0);
		
		for (int b = 0; b < N; ++b) {
			
			ll best = 0LL;
			for (int i = 0; i < int(blocks[b].size()); ++i) {
				if (i > 0)
					mkmx(dp[c][fst[b]+i], dp[1-c][fst[b]+i-1] + blocks[b][i]);
				ll dbmax = 0LL;
				if (b > 0) mkmx(dbmax, st[1-c].query(0, b-1));
				mkmx(dp[c][fst[b]+i], dbmax + blocks[b][i]);
				
				mkmx(best, dp[c][fst[b] + i]);
				mkmx(ans, dp[c][fst[b] + i]);
			}
			
			st[c].update(b, best);
		}
		
		c = 1-c;
	}
	
	cout << ans << endl;
	
	return 0;
}
