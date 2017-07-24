#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ii = pair<ll, ll>;
using vi = vector<ll>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

constexpr int INF = 2000000000;
constexpr ll LLINF = 9000000000000000000;

template <class T, const T&(*op)(const T&, const T&)>
struct SegmentTree {
	int n; T ident; vector<T> tree;
	SegmentTree(int _n, T _id) : n(_n), ident(_id), tree(2 * n, ident) { }
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

void addself(int u, int d, vi &last, SegmentTree<ii, min> &st, int &time) {
	int t = time++;
	st.update(t, ii(d, u));
	last[u] = t;
}
void dfs(int u, int p, int d, vvi &E, vi &last, SegmentTree<ii, min> &st,
		int &time, vi &depth) {
	addself(u, d, last, st, time);
	depth[u] = d;
	for (int v : E[u]) {
		if (v == p) continue;
		dfs(v, u, d+1, E, last, st, time, depth);
		addself(u, d, last, st, time);
	}
}

int getlc(int a, int b, SegmentTree<ii, min> &st, vi &last) {
	return (int)st.query(min(last[a], last[b]), max(last[a], last[b])).second;
}
int attempt(int a, int b, int c, vi &last, SegmentTree<ii, min> &st,
		vi &depth) {
	int lca_ab = getlc(a, b, st, last);
	{
		int lca_c_ab = getlc(c, lca_ab, st, last);
		if (lca_c_ab != lca_ab)
			return depth[b] - depth[lca_ab];
	}
	{
		int lca_ac = getlc(a, c, st, last);
		if (lca_ac != lca_ab)
			return depth[lca_ac] + depth[b] - 2 * depth[lca_ab];
	}
	{
		int lca_bc = getlc(b, c, st, last);
		return depth[b] - depth[lca_bc];
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, q;
	cin >> n >> q;
	vvi E(n, vi());
	for (int i = 1, a; i < n; ++i)
		cin >> a, --a,
		E[a].push_back(i),
		E[i].push_back(a);

	vi last(n, -1LL), depth(n, 0LL);
	SegmentTree<ii, min> st(3 * n, {LLINF, -1LL});
	int time = 0;
	dfs(0, -1, 0, E, last, st, time, depth);

	while (q--) {
		int a, b, c;
		cin >> a >> b >> c;
		--a; --b; --c;
		cout << 1+max(
			attempt(a, b, c, last, st, depth),
			max(
				attempt(c, a, b, last, st, depth),
				attempt(b, c, a, last, st, depth))) << '\n';
	}
	
	return 0;
}
