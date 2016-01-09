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
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

constexpr ll MOD = 1e9 + 7;
constexpr ll SMOD = 1e9 + 6;

ll gcd(ll a, ll b) { while (b) { a %= b; swap(a, b); } return a; }
ll lcm(ll a, ll b) { return (a / gcd(a, b)) * b;				 }
ll mod(ll a, ll b) { return ((a % b) + b) % b;				   }

// Finds x, y s.t. ax + by = d = gcd(a, b).
void extended_euclid(ll a, ll b, ll &x, ll &y, ll &d) {
	ll xx = y = 0;
	ll yy = x = 1;
	while (b) {
		ll q = a / b;
		ll t = b; b = a % b; a = t;
		t = xx; xx = x - q * xx; x = t;
		t = yy; yy = y - q * yy; y = t;
	}
	d = a;
}

// solves ab = 1 (mod n), -1 on failure
ll mod_inverse(ll a, ll n) {
	ll x, y, d;
	extended_euclid(a, n, x, y, d);
	return (d > 1 ? -1 : mod(x, n));
}

ll modpow(ll a, ll b, ll m) {
	if (b == 0LL) return 1LL;
	if (b == 1LL) return a % m;
	ll r = modpow((a * a) % m, b / 2, m);
	if (b&1LL) r = (r * a) % m;
	return r;
}

template <class T, T(*op)(T, T), T ident>
struct SegmentTree {
	struct Node {
		T val;
		int l, r;
		Node(T _val, int _l, int _r) : val(_val), l(_l), r(_r) { };
	};
	int n;
	vector<Node> tree;
	SegmentTree(int p, vector<T> &init) : n(1 << p) { // Needs 2^p leafs
		tree.assign(2 * n, Node(ident, 0, n - 1));
		for (int j = 1; j < n; ++j) {
			int m = (tree[j].l + tree[j].r) / 2;
			tree[2*j].l = tree[j].l;
			tree[2*j].r = m;
			tree[2*j+1].l = m + 1;
			tree[2*j+1].r = tree[j].r;
		}
		for (int j = 2 * n - 1; j > 0; --j) {
			if (j >= n) tree[j].val = init[j - n];
			else tree[j].val = op(tree[2*j].val, tree[2*j+1].val);
		}
	}
	void update(int i, T val) {
		for (tree[i+n].val = val, i = (i+n)/2; i > 0; i /= 2)
			tree[i].val = op(tree[2*i].val, tree[2*i+1].val);
	}
	T query(int l, int r) {
		T lhs = T(ident), rhs = T(ident);
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if   (l&1)  lhs = op(lhs, tree[l++].val);
			if (!(r&1)) rhs = op(tree[r--].val, rhs);
		}
		return op(l == r ? op(lhs, tree[l].val) : lhs, rhs);
	}
};

ll mul(ll l, ll r) { return (l * r) % SMOD; }

int main() {
	
	int m;
	scanf("%d", &m);
	vi _p(m, 0);
	for (int i = 0; i < m; ++i) {
		scanf("%d", &_p[i]);
	}
	
	sort(_p.begin(), _p.end());
	vector<pair<ll, int> > p;
	for (int i = 0; i < m; ++i) {
		if (int(p.size()) == 0 || p.back().first != _p[i])
			p.push_back({_p[i], 1});
		else	p.back().second++;
	}
	
	// total number of divisors mod (MOD-1)
	int pp = 1;
	m = int(p.size());
	while ((1<<pp) < m) ++pp;
	vector<ll> init(1<<pp, 1LL);
	for (int i = 0; i < m; ++i)
		init[i] = p[i].second + 1;
	
	SegmentTree<ll, mul, 1LL> st(pp, init);
	
	ll ans = 1LL;
	for (int i = 0; i < m; ++i) {
		ll divs = 1LL;
		if (i > 0) divs *= st.query(0, i - 1);
		if (i < m - 1) divs *= st.query(i + 1, m - 1);
		
		ll V = 1LL;
		for (int e = 1; e <= p[i].second; ++e) {
			V = (V * p[i].first) % MOD;
			ll contr = modpow(V, divs, MOD);
			ans = (ans * contr) % MOD;
		}
	}
	
	cout << ans << endl;
	
	return 0;
}
