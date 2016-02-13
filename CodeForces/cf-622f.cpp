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

ll MOD = 1e9+7;

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

// (a*b)%m
ll mulmod(ll a, ll b, ll m){
	ll x = 0, y=a%m;
	while(b>0){
		if(b&1)
			x = (x+y)%m;
		y = (2*y)%m;
		b/=2;
	}
	return x % m;
}
ll mulmod2(ll a, ll b, ll m){ return __int128(a)*b%m; }

ll pow(ll b, ll e) {		// b^e in logarithmic time
	ll p = e<2 ? 1 : pow(b*b,e/2);
	return e&1 ? p*b : p;
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

ll binom(ll n, ll k){
	ll ans = 1;
	for(ll i = 1; i <= min(k,n-k); ++i) ans = ans*(n+1-i)/i;
	return ans;
}

// Solves x = a1 mod m1, x = a2 mod m2, x is unique modulo lcm(m1, m2).
// Returns {0, -1} on failure, {x, lcm(m1, m2)} otherwise.
pair<ll, ll> crt(ll a1, ll m1, ll a2, ll m2) {
	ll s, t, d;
	extended_euclid(m1, m2, s, t, d);
	if (a1 % d != a2 % d) return {0, -1};
	return {mod(s * a2 * m1 + t * a1 * m2, m1 * m2) / d, m1 / d * m2};
}

// Solves x = ai mod mi. x is unique modulo lcm mi.
// Returns {0, -1} on failure, {x, lcm mi} otherwise.
pair<ll, ll> crt(vector<ll> &a, vector<ll> &m) {
	pair<ll, ll> res = {a[0], m[0]};
	for (ull i = 1; i < a.size(); ++i) {
		res = crt(res.first, res.second, mod(a[i], m[i]), m[i]);
		if (res.second == -1) break;
	}
	return res;
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	ll N, K;
	cin >> N >> K;
	
	vector<ll> pref(K + 2, 0LL);
	vector<ll> fact(K + 2, 1LL);
	for (ll i = 1; i <= K + 1; ++i) {
		pref[i] = (pref[i - 1] + modpow(i, k)) % MOD
		fact[i] = (fact[i - 1] * i) % MOD;
	}
	
	ll ans = 0LL;
	for (int i = 1; i <= K + 1; ++i) {
		
	}
	
	return 0;
}
