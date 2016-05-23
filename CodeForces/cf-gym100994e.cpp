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

struct T {
	ll pref = -LLINF;
	ll suff = -LLINF;
	ll best = -LLINF;
	ll full = -LLINF;
	T(ll p, ll s, ll b, ll f) {
		pref = p;
		suff = s;
		best = b;
		full = f;
	}
};

T op(T l, T r) {
	ll p = -LLINF;
	ll s = -LLINF;
	ll b = -LLINF;
	ll f = -LLINF;
	p = l.pref;
	if (l.full != -LLINF && r.pref != -LLINF && l.full + r.pref > l.pref)
		p = l.full + r.pref;
	s = r.suff;
	if (r.full != -LLINF && l.suff != -LLINF && l.suff + r.full > r.suff)
		s = l.suff + r.full;
	b = l.best;
	if (r.best != -LLINF && r.best > b)
		b = r.best;
	if (l.suff != -LLINF && r.pref != -LLINF && l.suff + r.pref > b) {
		b = l.suff + r.pref;
	}
	f = -LLINF;
	if (l.full != -LLINF && r.full != -LLINF)
		f = l.full + r.full;
	
	return T(p, s, b, f);
}

T ident(-LLINF, -LLINF, -LLINF, -LLINF);

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

int main() {
	
	int n, m;
	scanf("%d %d", &n, &m);
	
	vi a(n, 0LL);
	vi b(m, 0LL);
	for (int i = 0, v; i < n; ++i)
		scanf("%d", &v),
		a[i] = ll(v);
	for (int i = 0, v; i < m; ++i)
		scanf("%d", &v),
		b[i] = ll(v);
	
	
	priority_queue<ii> pqa, pqb;
	for (int i = 0; i < n; ++i)
		pqa.push({a[i], i});
	for (int i = 0; i < m; ++i)
		pqb.push({b[i], i});
	
	vi ans(m, 0LL);
	SegmentTree st(n);
	
	while (pqb.size() > 0) {
		
		while (pqa.size() > 0 && pqa.top().first >= pqb.top().first) {
			ll v = pqa.top().first;
			int i = int(pqa.top().second);
			st.update(i, T(v, v, v, v));
			pqa.pop();
		}
		
		int i = int(pqb.top().second);
		ll v = st.query(0, n - 1).best;
		ans[i] = (v == -LLINF ? 0LL : v);
		pqb.pop();
	}
	
	for (int i = 0; i < m; ++i)
		cout << ans[i] << " \n"[i + 1 == m];
	
	return 0;
}
