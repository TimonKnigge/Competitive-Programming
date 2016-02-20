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

ll mx(ll l, ll r) { return max(l, r); }
constexpr ll ident = 0LL;


#define MY_PI 3.14159265358979323846


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	vi r(n, 0LL), h(n, 0LL);
	vi volbypi(n, 0LL);
	vi volbypi2(n, 0LL);
	for (int i = 0; i < n; ++i) {
		cin >> r[i] >> h[i];
		volbypi[i] = volbypi2[i]
			= r[i] * r[i] * h[i];
	}
	sort(volbypi2.begin(), volbypi2.end());
	map<ll, int> indexof;
	for (int i = 0; i < n; ++i) {
		if (i == 0 || volbypi2[i-1] != volbypi2[i])
			indexof.insert({volbypi2[i], i});
	}
	
	int p = 1;
	while ((1<<p) < n) ++p;
	vi init(1 << p, 0LL);
	
	SegmentTree<ll, mx, ident> st(init);
	for (int i = 0; i < n; ++i) {
		int j = indexof[volbypi[i]];
		ll add = (j > 0 ? st.query(0, j - 1) : 0LL);
		add += volbypi[i];
		st.update(j, mx(add, st.query(j, j)));
	}
	
	ld ans = ld(st.query(0, n - 1)) * MY_PI;
	printf("%.7lf\n", double(ans));
	
	return 0;
}
