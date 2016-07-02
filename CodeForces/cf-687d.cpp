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

constexpr size_t NMAX = 1000;
constexpr size_t MMAX = 1000000;
constexpr size_t TMAX = 2000000;

template<class T>
struct res_vector {
	vector<T> v, d;
	int time = 0;
	vi t;
	res_vector(int n, T _d) {
		v.assign(n, _d);
		d.assign(n, _d);
		t.assign(n, 0);
	}
	T get(int i) { return t[i] == time ? v[i] : d[i]; }
	void set(int i, T _v) { t[i] = time; v[i] = _v; }
	void setdef(int i, T _v) { d[i] = _v; }
	void reset() { ++time; }
};

struct UnionFind {
	bool consistent = true;
	int n, c;
	res_vector<int> par, rank, size;
	res_vector<bool> sign;
	UnionFind(int _n) : n(_n), c(n), par(n, 0), rank(n, 0), size(n, 1), sign(n, false){
		for (int i = 0; i < n; ++i) par.set(i, i), par.setdef(i, i);
	}

	int find(int i) {
		if (par.get(i) == i) return i;
		int p = find(par.get(i));
		if (par.get(i) != p && sign.get(par.get(i))) {
			sign.set(i, !sign.get(i));
		}
		par.set(i, p);
		return p;
//		return (par[i] == i ? i : (par[i] = find(par[i])));	
	}
	bool same(int i, int j) { return find(i) == find(j); }
	bool sign_of(int u, int pu) {
		bool su = sign.get(u);
		if (u != pu && sign.get(pu)) su = !su;
		return su;
	}
	
	void reset() {
		par.reset();
		rank.reset();
		size.reset();
		sign.reset();
		c = n;
	}

	void merge(int i, int j, bool diff = true) {
		int pi = find(i), pj = find(j);
		
		if (pi == pj) {
			bool si = sign_of(i, pi), sj = sign_of(j, pj);
			if (si == sj && diff) consistent = false;
			if (si != sj && !diff) consistent = false;
		}
		
		c--;
		if (rank.get(pi) > rank.get(pj)) swap(i, j), swap(pi, pj);
		
		bool si = sign_of(i, pi), sj = sign_of(j, pj);
		
		if ((si == sj && diff) || (si != sj && !diff)) {
			sign.set(pi, !sign.get(pi));
		}
		
		par.set(pi, pj); size.set(pj, size.get(pj) + size.get(pi));
		if (rank.get(pi) == rank.get(pj)) rank.set(pj, rank.get(pj)+1);
	}
};

// ipt
int n, m, q;
vector<pair<ii, ll>> E;
// -ipt

//template <class T, const T&(*op)(const T&, const T&), T ident>
constexpr int SZ = 1e6;
vb sign;
UnionFind uf(NMAX);
vector<pair<ll, vi>> ans(SZ, {-2LL, vi()});
map<ii, int> cache;

void combine_into(pair<ll, vi> &lv, pair<ll, vi> &rv, pair<ll, vi> &o) {
	uf.reset();
	size_t lx = 0, rx = 0; //lv.second.size(), rx = rv.second.size();
	
	while (lx < lv.second.size() || rx < rv.second.size()) {
		int i = (lx < lv.second.size() ? lv.second[lx] : rv.second[rx]);
		if (rx < rv.second.size() && E[i].second <= E[rv.second[rx]].second) {
			i = rv.second[rx];
			++rx;
		} else	++lx;
		
		int u = E[i].first.first, v = E[i].first.second;
		int pu = uf.find(u), pv = uf.find(v);
		if (pu == pv && uf.sign_of(u, pu) != uf.sign_of(v, pv))
			continue;
		o.second.push_back(i);
		if (pu != pv)
			uf.merge(u, v);
		else {
			o.first = E[i].second;
			break;
		}
	}
}

void ptup(pair<ll, vi> &v) {
	cerr << "{" << v.first << ",";
	for (ll w : v.second) cerr << " ((" << E[w].first.first << "," << E[w].first.second << ")," << E[w].second << ")";
	cerr << "}";
}

int solve(int l, int r) {
	auto it = cache.find({l, r});
	if (it != cache.end()) return it->second;
	cache.insert({{l, r}, cache.size()});
	int id = cache.size() - 1;
	ans[id].first = -1LL;
	
	// solve l,r
	int lid = solve(l, (l+r)/2), rid = solve((l+r)/2+1, r);
	combine_into(ans[lid], ans[rid], ans[id]);
	
//	cerr << "[" << l << ", " << r << "] goes to ";
//	ptup(ans[id]);
//	cerr << endl;
	return id;
}

// [l, r]: query, [L, R]: representee
void accumulate(int l, int r, int L, int R, vi &res) {
//	cerr << "enc " << L << " " << R << " in accum." << endl;
	if (r < L || R < l) return;
	if (l <= L && R <= r)
		res.push_back(solve(L, R));
	else {
		accumulate(l, r, L, (L+R)/2, res);
		accumulate(l, r, (L+R)/2+1, R, res); 
	}
}

ll query(int l, int r) {
//	cerr << "Processing [" << l << ", " << r << "]\n";
	vi res;
	accumulate(l, r, 0, m - 1, res);
	
//	cerr << "Collected: " << endl;
//	for (int i : res) ptup(ans[i]), cerr << endl;
	
//	cerr << "Computing: " << endl;
	vector<pair<ll, vi>> resa(2, {-1LL, vi()});
	for (size_t i = 0; i < res.size(); ++i) {
		resa[i&1].second.clear();
		combine_into(resa[(i&1)^1], ans[res[i]], resa[i&1]);
//		ptup(resa[(i&1)^1]); cerr << " and ";
//		ptup(ans[res[i]]); cerr << " mapsto ";
//		ptup(resa[i&1]); cerr << endl;
	}
	return resa[(1&res.size())^1].first;
}

int main() {
	
	scanf("%d %d %d", &n, &m, &q);
	
	E.assign(m, {{-1, -1}, 0LL});
	for (int i = 0; i < m; ++i) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		E[i] = {{u - 1, v - 1}, ll(w)};
		ans[cache.size()] = {-1LL, vi {i}};
		cache.insert({{i, i}, cache.size()});
	}
	
//	cerr << "Setup cache" << endl;
	
	while (q--) {
		int l, r;
		scanf("%d %d", &l, &r);
		cout << query(l - 1, r - 1) << '\n';
	}
	
	return 0;
}
