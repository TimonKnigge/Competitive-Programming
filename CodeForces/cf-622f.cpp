#define HEADER_H
//#define _GLIBCXX_DEBUG
#include <bits/stdc++.h>
#define REP(i,n)	for(auto i=decltype(n)(0); i<(n); ++i)
#define all(v)		begin(v), end(v)
using namespace std;		using ull= unsigned long long;
using ll = long long;		using ld = long double;
using vi = vector<ll>;		using vvi= vector<vi>;
using vb = vector<bool>;	using ii = pair<ll,ll>;
constexpr bool LOG = true;
void Log() { if(LOG) cerr << "\n"; }
template<class T, class... S> void Log(T t, S... s){
	if(LOG) cerr << t << "\t", Log(s...);
} /* ============== END OF HEADER ============== */


ll mod = 1e9+7;
ll powmod(ll b, ll e) {
	ll p = e<2 ? 1 : powmod((b*b)%mod,e/2);
	return e&1 ? p*b%mod : p;
}
ll modd(ll a, ll b) { return ((a % b) + b) % b; }

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
	return (d > 1 ? -1 : modd(x, n));
}

int main(){
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	ll n, k; cin >> n >> k;

	if(n<=k+1){
		ll ans = 0;
		for(ll i = 1; i <= n; ++i){
			ans += powmod(i,k);
			ans %= mod;
		}
		cout << ans << endl;
	} else {
		vi y(k+2);
		ll sum = 0;
		y[0]=0;
		for(ll i = 1; i <= k+1; ++i){
			sum += powmod(i,k);
			sum %= mod;
			y[i] = sum;
		}

		// now calculate lagrange coefficients
		ll num = 1;
		for(ll i = 0; i <= k+1; ++i)
			num = num*(n-i)%mod;

		vi fac(k+2);
		fac[0] = 1;
		for(ll i = 1; i <= k+1; ++i)
			fac[i] = fac[i-1]*i%mod;

		ll ans = 0;
		for(ll j = 0; j <= k+1; ++j){
			ll numerator = num * mod_inverse(n-j, mod)%mod;
			ll denom = fac[j] * fac[k+1-j]%mod;
			if((k-j+1)&1){ denom = (mod-denom)%mod; }
			ans += numerator * mod_inverse(denom, mod)%mod * y[j]%mod;
			ans %= mod;
		}
		cout << ans << endl;

	}
	return 0;
}


