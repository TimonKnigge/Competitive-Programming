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
	return (ll)(__int128(a)*__int128(b)%__int128(m));
}
// Finds b^e % m in O(lg n) time, ensure that b < m to avoid overflow!
ll powmod(ll b, ll e, ll m) {
	ll p = e<2 ? 1 : powmod(mulmod(b,b,m),e/2,m);
	return e&1 ? mulmod(p,b,m) : p;
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

ll legendre(ll a, ll p) {
	return powmod(a, (p-1)/2, p) == 1 ? 1 : -1;
}
// Returns a root of `a` modulo p, or -1 on failure. Note that if x>0
// is one root, n-x is the other. Exactly half of all values in
// [1..p-1] have two roots, the other half have no root.
// Runtime: O(log^2 p) if the generalized Riemann hypothesis is true.
ll sqrtp(ll a, ll p) {
	a = mod(a, p);
	if (a == 0) return 0;
	if (p == 2) return a;
	if (legendre(a, p) != 1) return -1;
	ll q = p-1, s = 0, z = 1;
	while (!(q&1)) ++s, q >>= 1;
	while (legendre(z, p) != -1) ++z;
	ll x = powmod(a, (q+1)/2, p);
	for (ll c = powmod(z, q, p), t = powmod(a, q, p); t != 1;) {
		ll i = 1, t2i = t*t%p;
		while (t2i != 1) t2i = t2i*t2i%p, ++i;
		ll b = powmod(c, 1LL<<(s-i-1), p);
		x = (x*b)%p, c = (b*b)%p, t = (t*c)%p, s = i;
	}
	return x;
}
void solve() {
	int n;
	cin >> n;
	vi isp(n+1, 1);
	isp[0] = isp[1] = 0;
	for (ll d = 2; d <= n; ++d)
		for (ll m = d*d; m <= n; m += d)
			isp[m] = 0;

	ll ans = 
		0LL +	// 2
		5LL; 	// 3
	for (ll p = 5; p <= n; ++p) {
		if (!isp[p]) continue;

		if (legendre(13, p) < 0) continue;
		ll r = sqrtp(13, p);
		if (r < 0) continue;
		assert(r*r % p == 13 % p);
		ll mans = p*p;
		for (ll a : {r, (p-r)%p}) {
			a = mulmod(powmod(a, p, p*p), powmod(13, (p*p-2*p+1)/2, p*p), p*p);
			ll ti = (p*p+1)/2LL;

			ll n1 = mulmod((3 + a), ti, p*p);
			ll n2 = mulmod(mod(3 - a, p*p), ti, p*p);
			mans = min(mans, min(n1, n2));
		}
		mans %= (p*p);
		ans += mans;
		assert(mans>0);
	}
	cout << ans << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout << fixed << setprecision(12);
	
	solve();
	
	return 0;
}
