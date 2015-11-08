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
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000LL;


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

constexpr ll SIZE = 1e6+10;
vector<ll> primes;

vector<ll> mf(SIZE + 1, -1);		// mf[i]==i when prime
void sieve2() { // call at start in main!
	mf[0] = mf[1] = 1;
	for (ll i = 2; i <= SIZE; i++) if (mf[i] < 0) {
		mf[i] = i;
		for (ll j = i * i; j <= SIZE; j += i)
			if(mf[j] < 0) mf[j] = i;
		primes.push_back(i);
	}
}

void prime_divisors(ll n, vector<ll> &d){
	while(n>1){
		if (d.size() == 0 || d.back() != mf[n])
			d.push_back(mf[n]);
		n /= mf[n];
	}
}

// SEGTREE
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
// -SEGTREE

ll MOD = 1e9 + 7;
ll prodmod(ll l, ll r) { return (l * r) % MOD; }

int main() {
	sieve2();
	
	int n;
	scanf("%d", &n);
	vector<int> a(n, 0);
	for (int i = 0; i < n; ++i) {
		scanf("%d", &a[i]);
	}
	
	int p = 1;
	while ((1LL<<p) < n) p++;
	
	vector<ll> init(1<<p, 1LL);
	for (int i = 0; i < n; ++i) {
		init[i] = (ll(a[i])) % MOD;
	}
	SegmentTree<ll, prodmod, 1LL> segtree(p, init);
	
	// Factor each number
	vector<vector<ll> > fact(n, vector<ll>());
	vector<vector<int> > nxt(n, vector<int>());
	map<ll, int> last_occ;
	for (int i = n - 1; i >= 0; --i) {
		prime_divisors(a[i], fact[i]);
		for (int j = 0; j < fact[i].size(); ++j) {
			auto it = last_occ.find(fact[i][j]);
			if (it != last_occ.end()) {
				nxt[i].push_back(it->second);
				it->second = i;
			} else {
				nxt[i].push_back(-1);
				last_occ.insert({fact[i][j], i});
			}
		}
	}
	// Add all intial p-1/p factors
	for (auto it : last_occ) {
		int i = it.second;
		ll j = it.first;
		ll val = segtree.query(i, i);
		val = (val * ll(j - 1)) % MOD;
		val = (val * mod_inverse(ll(j), MOD)) % MOD;
		segtree.update(i, val);
	}
	
	// Take all queries, sort by left endpoint
	int q;
	vvi query(n, vi());
	vvi id(n, vi());
	scanf("%d", &q);
	vector<ll> res(q, 0LL);
	
	for (int i = 0; i < q; ++i) {
		int l, r;
		scanf("%d %d", &l, &r);
		l--;
		r--;
		query[l].push_back(r);
		id[l].push_back(i);
	}
	
	// Calculate all queries
	for (int l = 0; l < n; ++l) {
		for (int i = 0; i < query[l].size(); ++i) {
			int r = query[l][i];
			ll val = segtree.query(l, r);
			res[id[l][i]] = val % MOD;
		}
		
		// Fix all factors
		for (int i = 0; i < fact[l].size(); ++i) {
			int nx = nxt[l][i];
			if (nx == -1) continue;
			ll val = segtree.query(nx, nx);
			val = (val * ll(fact[l][i] - 1)) % MOD;
			val = (val * mod_inverse(ll(fact[l][i]), MOD)) % MOD;
			segtree.update(nx, val);
		}
	}
	
	for (int i = 0; i < res.size(); ++i)
		cout << res[i] << endl;
	
	return 0;
}
