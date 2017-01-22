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
	
	int N;
	cin >> N;
	vi T(N, 0LL);
	for (ll &v : T) cin >> v;
	
	SegmentTree<ll, min, LLINF> st(N);
	st.update(0, 20);
	cout << 20 << endl;

	int l9 = 0, l1 = 0;
	for (int i = 1; i < N; ++i) {
		ll a = 20 + st.query(i-1, i-1);
		
		while (T[l9] + 90 <= T[i]) ++l9;
		while (T[l1] +1440<= T[i]) ++l1;
		
		if (l9 > 0 && l9 < i)
			a = min(a, 50LL + st.query(l9 - 1, i - 1));
		else if (l9 == 0)
			a = min(a, 50LL);
		if (l1 > 0 && l1 < i)
			a = min(a,120LL + st.query(l1 - 1, i - 1));
		else if (l1 == 0)
			a = min(a, 120LL);
		
		st.update(i, a);
		cout << (a - st.query(i-1, i-1)) << '\n';
	}
	
	return 0;
}
