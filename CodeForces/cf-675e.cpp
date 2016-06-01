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

template <class T, const T&(*op)(const T&, const T&), T ident>
struct SegmentTree {
	int n; vector<T> tree;
	SegmentTree(int _n) : n(_n), tree(2 * n, ident) { }
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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	vi a(n, n-1);
	for (int i = 0; i < n - 1; ++i)
		cin >> a[i], --a[i];
	
	SegmentTree<ll, min<ll>, LLINF> dp(n);
	dp.update(n - 1, n - 1);
	for (int i = n - 2; i >= 0; --i)
		dp.update(i, n-1 - a[i] + dp.query(i + 1, a[i]));
	
	ll ans = 0LL;
	for (int i = 0; i < n; ++i)
		ans += dp.query(i, i) - i;
	
	cout << ans << endl;
	
	return 0;
}
