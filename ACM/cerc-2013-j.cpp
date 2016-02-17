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

ll P[4010][4010];
ll fib[4010];
void solve() {
	int k, _M;
	ll M;
	scanf("%d %d", &k, &_M);
	M = ll(_M);
	
	for (int i = 0; i < k; ++i) {
		int v;
		scanf("%d", &v);
		P[0][i] = ll(v);
	}
	
	fib[0] = 1LL;
	fib[1] = 2LL;
	for (int i = 2; i <= k; ++i)
		fib[i] = (fib[i-1] + fib[i-2]) % M;
	
	for (int a = 1; a < k; ++a)
		for (int i = a; i < k; ++i)
			P[a][i] = (P[a-1][i] + (M - fib[a - 1]) * P[a-1][i-1]) % M;
	
	vector<ll> A(k, 0LL);
	vector<ll> PJ(k, 0LL);
	for (int i = 0; i < k; ++i)
		PJ[i] = P[i][i];
	
	// Reuse P to save memory.
	// P[i][j] = prod_{k=0..j-1} (F_i - F_k)  % M
	for (int i = 0; i < k; ++i) {
		P[i][0] = mod(fib[i] - fib[0], M);
		for (int j = 1; j < i; ++j)
			P[i][j] = ((fib[i] - fib[j] + M) * P[i][j-1]) % M;
	}
	
	for (int j = k - 1; j >= 0; --j) {
		
		for (int i = j + 1; i < k; ++i) {
			ll t = (M - A[i]) * fib[i];
			PJ[j] = (PJ[j] + (t%M) * (j > 0 ? P[i][j - 1] : 1LL)) % M;
		}
		
		A[j] = (PJ[j] * mod_inverse((fib[j] * (j > 0 ? P[j][j-1] : 1LL)) % M, M)) % M;
	}
	
	ll ans = 0LL;
	for (int i = 0; i < k; ++i) {
		ans = (ans + A[i] * powmod(fib[i], k + 1, M)) % M;
	}
	
	cout << ans << '\n';
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) solve();
	
	return 0;
}
