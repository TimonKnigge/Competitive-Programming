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

void dfs(int u, vvi &C, vi &dfs_in, vi &dfs_out, vi &depth, ll &_time) {
	dfs_in[u] = _time++;
	for (ll v : C[u])
		depth[v] = depth[u] + 1,
		dfs(v, C, dfs_in, dfs_out, depth, _time);
	dfs_out[u] = _time++;
}

using T = ii;
ii op(ii l, ii r) { return {l.first+r.first, l.second+r.second}; }
ii ident = {0LL, 0LL};

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
	void reset() { tree.assign(tree.size(), ident); }
};

void fix_update(ll F, ll X, ll D, SegmentTree &st, vi &dfs_in, vi &dfs_out, vi &depth) {
	ii cur = st.query(dfs_in[F], dfs_in[F]);
	cur.first += X - depth[F] * D;
	cur.second += D;
	st.update(dfs_in[F], cur);
	
	cur = st.query(dfs_out[F], dfs_out[F]);
	cur.first -= X - depth[F] * D;
	cur.second -= D;
	st.update(dfs_out[F], cur);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N, M;
	cin >> N >> M;
	
	vi P(N, -1LL);
	vvi C(N, vi());
	for (int i = 1; i < N; ++i) {
		int v;
		cin >> v;
		P[i] = v - 1;
		C[v - 1].push_back(i);
	}
	
	vvi fac(M, vi());
	for (int i = 0, v; i < N; ++i)
		cin >> v,
		fac[v - 1].push_back(i);
	
	vi threshold(M, 0LL);
	for (int i = 0; i < M; ++i) {
		ll v;
		cin >> v;
		threshold[i] = v;
	}
	
	vi dfs_in(N, 0LL), dfs_out(N, 0LL), depth(N, 0LL);
	ll time = 0LL;
	dfs(0, C, dfs_in, dfs_out, depth, time);
	
	ll Q;
	cin >> Q;
	SegmentTree st(2*N);
	
	vector<pair<ll, ii>> updates;
	for (int i = 0; i < Q; ++i) {
		ll F, X, D;
		cin >> F >> X >> D;
		--F;
		updates.push_back({F, {X, D}});
	
		fix_update(F, X, D, st, dfs_in, dfs_out, depth);
	}
	
	vi ans(M, 0LL);
	vector<pair<ii, ll>> owners[2];
	int cur = 0;
	for (int i = 0; i < M; ++i) {
		ll accum = 0LL;
		for (int j : fac[i]) {
			ii ab = st.query(0, dfs_in[j]);
			ll v = ab.first + depth[j] * ab.second;
			accum += v;
		}
		if (accum < threshold[i]) ans[i] = -1LL;
		else owners[cur].push_back({{0, Q - 1}, i});
	}
	
	cur = 1 - cur;
	while (owners[1-cur].size() > 0) {
		owners[cur].clear();
		st.reset();
		int last = 0;
		for (size_t l = 0, r = 0; l < owners[1-cur].size(); l = r) {
			while (r < owners[1-cur].size() && owners[1-cur][l].first == owners[1-cur][r].first) ++r;
			
			int L = owners[1-cur][l].first.first, R = owners[1-cur][l].first.second;
			if (L == R) {
				for (size_t i = l; i < r; ++i)
					ans[owners[1-cur][i].second] = L;
			} else {
				int M = (L+R)/2;
				while (last < L) {
					fix_update(updates[last].first, updates[last].second.first, updates[last].second.second,
						st, dfs_in, dfs_out, depth);
					++last;
				}
				for (int i = max(last, L); i <= M; ++i)
					fix_update(updates[i].first, updates[i].second.first, updates[i].second.second,
						st, dfs_in, dfs_out, depth);
				last = M+1;
				for (int i = l; i < r; ++i) {
					int o = owners[1-cur][i].second;
					ll accum = 0LL;
					for (int f : fac[o]) {
						ii ab = st.query(0, dfs_in[f]);
						accum += ab.first + depth[f] * ab.second;
					}
					if (accum >= threshold[o])
						owners[cur].push_back({{L, M}, o});
					else	owners[cur].push_back({{M+1,R},o});
				}
			}
		}
		sort(owners[cur].begin(), owners[cur].end());
		cur = 1 - cur;
	}
	
	for (int i = 0; i < M; ++i)
		if (ans[i] == -1LL)
			cout << "rekt\n";
		else	cout << ans[i]+1 << '\n';
	
	return 0;
}
