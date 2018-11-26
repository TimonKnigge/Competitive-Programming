#define _GLIBCXX_DEBUG
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<ll>;

constexpr int INF = 2000000010;
constexpr ll LLINF = 9000000000000000010LL;

struct UnionFind {
	vi par, rank, size; int c;
	UnionFind(int n) : par(n), rank(n,0), size(n,1), c(n) {
		for (int i = 0; i < n; ++i) par[i] = i;
	}
	int find(int i) { return (par[i] == i ? i : (par[i] = find(par[i]))); }
	bool same(int i, int j) { return find(i) == find(j); }
	int get_size(int i) { return size[find(i)]; }
	int count() { return c; }
	void merge(int i, int j) {
		if ((i = find(i)) == (j = find(j))) return; else --c;
		if (rank[i] > rank[j]) swap(i, j);
		par[i] = j; size[j] += size[i];
		if (rank[i] == rank[j]) rank[j]++;
	}
};

template <class T>
struct SkewHeap {
	struct node {
		ll key, lazy = 0LL; T val;
		node *lc = nullptr, *rc = nullptr;
		node(ll k, T v) : key(k), val(v) {}
		node *prop() {
			if (lc) lc->lazy += lazy;
			if (rc) rc->lazy += lazy;
			key += lazy, lazy = 0LL;
			return this;
		}
	};
	node *r = nullptr;
	node* merge(node* x, node* y){
		if (!x) return y; else if (!y) return x;
		if (x->prop()->key > y->prop()->key) swap(x, y);
		x->rc = merge(x->rc, y);
		swap(x->lc, x->rc);
		return x;
	}

	bool empty() { return r != nullptr; }
	void insert(ll x, T val) { r = merge(r, new node(x, val)); }
	void adjust(ll c) { if (r) r->lazy += c; }
	pair<ll, T> pop_min() {
		ll w = r->prop()->key;
		T ret = r->val;
		node *nr = merge(r->lc, r->rc);
		swap(r, nr), delete nr;
		return {w, ret};
	}
	void absorb(SkewHeap<T> &o) { r = merge(r, o.r); o.r = nullptr; }
};

struct edge { int v; ll w; };

ll solve(int n, vector<vector<edge>> &E) {
	UnionFind uf(n+1);
	vector<SkewHeap<int>> sk(n+1);
	for (int i = 1; i <= n; ++i)
		for (const edge &e : E[i])
			sk[i].insert(e.w, e.v);
	ll ans = 0LL;
	vi best(n+1, -LLINF);
	for (int i = 1, root = 0; i <= n; ++i) {
		if (uf.find(i) == root) continue;
		vector<int> st; st.push_back(i);
		while (true) {	
			int u = st.back(), v; ll w;
			tie(w, v) = sk[u].pop_min();
			v = uf.find(v);
			if (v == u) continue;
			ans += (best[u] = w);
			if (v == root) break;
			if (best[v] == -LLINF) {
				st.push_back(v);
			} else {
				while (true) {
					sk[st.back()].adjust(-best[st.back()]);
					if (st.back() != u) sk[u].absorb(sk[st.back()]);
					if (uf.find(st.back()) == v) break;
					else uf.merge(st.back(), v), v = uf.find(v), st.pop_back();
				}
				swap(sk[u], sk[v]);
				st.pop_back(), st.push_back(v);
			}
		}
		while (!st.empty()) uf.merge(root, st.back()), st.pop_back();
		root = uf.find(root);
	}
	return ans;
}

void solve() {
	int n;
	cin >> n;
	vector<vector<edge>> E(n+1);
	for (int i = 1, x, s; i <= n; ++i) {
		cin >> x >> s;
		E[i].push_back({x, ll(s)});
		for (int j = 0, v; j <= n; ++j) {
			cin >> v;
			if (j != x)
				E[i].push_back({j, ll(v)});
		}
	}
	cout << solve(n, E) << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout << fixed << setprecision(12);
	
	solve();
	
	return 0;
}
