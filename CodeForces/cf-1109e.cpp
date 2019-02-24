#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
using ll = long long;
using ld = long double;
using ii = pair<ll, ll>;
using vi = vector<ll>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;
using vd = vector<ld>;

template<class T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<class TIn, class TOut = null_type>
using order_tree = tree<TIn, TOut, less<TIn>, rb_tree_tag,
	tree_order_statistics_node_update>;
// .find_by_order(int r) and .order_of_key(TIn v)

constexpr int INF = 2000000010;
constexpr ll LLINF = 9000000000000000010LL;
constexpr ld PI = acos(-1);


ll gcd(ll a, ll b) { while (b) { a %= b; swap(a, b); } return a; }
ll lcm(ll a, ll b) { return (a / gcd(a, b)) * b; }
ll mod(ll a, ll b) { return ((a % b) + b) % b; }
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
// All modular inverses of [1..n] mod P in O(n) time.
vi inverses(ll n, ll P) {
	vi I(n+1, 1LL);
	for (ll i = 2; i <= n; ++i)
		I[i] = mod(-(P/i) * I[P%i], P);
	return I;
}
// (a*b)%m
ll mulmod(ll a, ll b, ll m){
	ll x = 0, y=a%m;
	while(b>0){
		if(b&1) x = (x+y)%m;
		y = (2*y)%m, b /= 2;
	}
	return x % m;
}
// Finds b^e % m in O(lg n) time, ensure that b < m to avoid overflow!
ll powmod(ll b, ll e, ll m) {
	ll p = e<2 ? 1 : powmod((b*b)%m,e/2,m);
	return e&1 ? p*b%m : p;
}
// Solve ax + by = c, returns false on failure.
bool linear_diophantine(ll a, ll b, ll c, ll &x, ll &y) {
	ll d = gcd(a, b);
	if (c % d) {
		return false;
	} else {
		x = c / d * mod_inverse(a / d, b / d);
		y = (c - a * x) / b;
		return true;
	}
}

ll SIZE;
vector<ll> primes;
vector<int> spf;
void sieve(ll size=1e6) {   // Initialize once in main.
	spf.assign((SIZE = size) + 1, 0);
	spf[0] = spf[1] = 1;
	for (ll i = 2; i <= SIZE; i++) {
		if (!spf[i]) primes.push_back(spf[i] = i);
		for (ll p : primes) {
			if (i*p > SIZE) break;
			spf[i*p] = p;
			if (spf[i] == p) break;
		}
	}
}

bool is_prime(ll n) {
	assert(n <= SIZE*SIZE);
	if (n <= SIZE) return spf[n] == n;
	for (ll p : primes) if (n % p == 0LL) return false;
	return true;
}
struct Factor{ ll p; ll exp; };
using FS = vector<Factor>;
FS factor(ll n){ // Up to SIZE^2
	FS fs;
	for (size_t i = 0; i < primes.size() && n > SIZE; ++i)
		if (n % primes[i] == 0) {
			fs.push_back({primes[i], 0});
			while (n % primes[i] == 0)
				fs.back().exp++, n /= primes[i];
		}
	if (n <= SIZE) {
		for(; n>1; n /= spf[n]) {
			if (!fs.empty() && fs.back().p == spf[n])
				++fs.back().exp;
			else fs.push_back({spf[n], 1});
		}
	} else fs.push_back({n, 1});
	return fs;
}

constexpr ll B = 500;

void drop(ll n, int b, ll mod, const FS &fs, vvi &mult, vvi &bmult, vi &blocks, vi &bsing, vi &rval, vvi &pw) {
	ll L = b*B, R = min(b*B+B, n);
	for (int j = L; j < R; ++j) {
		ll pr = 1LL;
	 	for (size_t i = 0; i < fs.size(); ++i)
			mult[i][j] += bmult[i][b], pr = pr * pw[i][mult[i][j]] % mod;
		rval[j] = (rval[j] * bsing[b]) % mod;
	}
	for (size_t i = 0; i < fs.size(); ++i)
		bmult[i][b] = 0;
	bsing[b] = 1LL;
}

void solve() {
	ll n, mod;
	cin >> n >> mod;

	sieve(1e5);
	FS fs = factor(mod);
	cerr << "fs.size() is " << fs.size() << endl;

	vvi mult(10, vi(n));
	vvi bmult(10, vi(B));
	vi blocks(B);
	vi bsing(B, 1);
	vi rval(n);

	vvi pw(10, vi(2e6, 1));
	for (size_t i = 0; i < fs.size(); ++i)
		for (int j = 1; j < 2e6; ++j)
			pw[i][j] = (pw[i][j-1] * fs[i].p) % mod;

	{
		int j = 0;
		for (ll &v : rval) {
			cin >> v;
			blocks[j/B] = (blocks[j/B] + v) % mod;
			for (size_t i = 0; i < fs.size(); ++i)
				while (v % fs[i].p == 0)
					v /= fs[i].p, mult[i][j]++;
			++j;
		}
	}

	cerr << "Preprocessed" << endl;

	int q;
	cin >> q;
	while (q--) {
		int t;
		cin >> t;
		if (t == 1) {
			int l, r, x;
			cin >> l >> r >> x;
			--l;
			for (int b = 0; b * B < n; ++b) {
				int L = b*B, R = min(b*B+B, n);
				if (r <= L || R <= l) continue;
				if (l <= L && R <= r) {
					blocks[b] = (blocks[b] * x) % mod;
					// Contained
					for (size_t i = 0; i < fs.size(); ++i)
						while (x % fs[i].p == 0)
							x /= fs[i].p, bmult[i][b]++;
					bsing[b] = (bsing[b] * x) % mod;
				} else {
					drop(n, b, mod, fs, mult, bmult, blocks, bsing, rval, pw);
					vi tmult(10);
					for (size_t i = 0; i < fs.size(); ++i)
						while (x % fs[i].p == 0)
							x /= fs[i].p, ++tmult[i];
					for (int j = L; j < R; ++j) {
						ll pr = 1LL;
					 	for (size_t i = 0; i < fs.size(); ++i)
							pr = pr * pw[i][mult[i][j]] % mod;
						ll ov = rval[j] * pr % mod;

						if (l <= j && j < r) {
							blocks[b] = (blocks[b] + mod - ov) % mod;
							for (size_t i = 0; i < fs.size(); ++i)
								mult[i][j] += tmult[i], pr = pr * pw[i][tmult[i]] % mod;
							rval[j] = (rval[j] * x) % mod;
							ll nv = rval[j] * pr % mod;
							blocks[b] = (blocks[b] + nv) % mod;
						}
					}
				}
			}
		} else if (t == 2) {
			int p, x;
			cin >> p >> x;
			--p;
			vi tmult(10);
			for (size_t i = 0; i < fs.size(); ++i)
				while (x % fs[i].p == 0)
					x /= fs[i].p, ++tmult[i];
			x = mod_inverse(x, mod);
			assert(x > 0);
			int b = p/B;
			drop(n, b, mod, fs, mult, bmult, blocks, bsing, rval, pw);
			ll opr = 1LL, npr = 1LL;
			for (size_t i = 0; i < fs.size(); ++i)
				opr = opr * pw[i][mult[i][p]] % mod, mult[i][p] -= tmult[i], npr = npr * pw[i][mult[i][p]] % mod;
			blocks[b] = (blocks[b] + mod - rval[p] * opr % mod) % mod;
			rval[p] = (rval[p] * x) % mod;
			blocks[b] = (blocks[b] + rval[p] * npr) % mod;
		} else {
			int l, r;
			cin >> l >> r;
			--l;

			ll ans = 0LL;
			for (int b = 0; b * B < n; ++b) {
				int L = b*B, R = min(b*B+B, n);
				if (r <= L || R <= l) continue;
				if (l <= L && R <= r) {
					ans = (ans + blocks[b]) % mod;
				} else {
					drop(n, b, mod, fs, mult, bmult, blocks, bsing, rval, pw);
					for (int j = L; j < R; ++j) {
						ll pr = 1LL;
					 	for (size_t i = 0; i < fs.size(); ++i)
							pr = pr * pw[i][mult[i][j]] % mod;
						ll ov = rval[j] * pr % mod;

						if (l <= j && j < r) {
							ans = (ans + ov) % mod;
						}
					}
				}
			}
			cout << ((ans%mod+mod)%mod) << endl;
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout << fixed << setprecision(12);
	
	solve();
	
	return 0;
}
