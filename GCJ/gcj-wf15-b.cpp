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

constexpr ll MOD = 1e9+7;
constexpr ll UB = 1e6+10;

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

// Finds b^e % m in O(lg n) time, ensure that b < m to avoid overflow!
ll powmod(ll b, ll e, ll m) {
	ll p = e<2 ? 1 : powmod((b*b)%m,e/2,m);
	return e&1 ? p*b%m : p;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	// Derangements
	vi D(UB, 0LL);
	D[0] = 1LL;
	D[1] = 0LL;
	D[2] = 1LL;
	for (ll n = 2; n + 1 < UB; ++n) {
		D[n + 1] = n * (D[n] + D[n - 1]) % MOD;
	}
	
	// Factorials
	vi F(UB, 1LL);
	vi Fi(UB, 1LL);
	for (ll n = 2; n < UB; ++n) {
		F[n] = (F[n - 1] * n) % MOD;
		Fi[n] = mod_inverse(F[n], MOD);
	}
	
	int T;
	cin >> T;
	for (int t = 1; t <= T; ++t) {
		
		ll N, X;
		cin >> N >> X;
		
		ll ans = 0LL;
		for (ll k = 0; k <= N - X; ++k) {
//			ll noverk = (F[N] * mod_inverse((F[k] * F[N - k]) % MOD, MOD)) % MOD;
			ll noverk = ((F[N] * Fi[k]) % MOD) * Fi[N-k] % MOD;
			ans = (ans + ((noverk * D[k]) % MOD)) % MOD;
		}
		ans = (ans * F[N]) % MOD;
		
		cout << "Case #" << t << ": " << ans << '\n';
		cerr << t << endl;
	}
	
	return 0;
}
