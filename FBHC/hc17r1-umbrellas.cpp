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

constexpr ll MOD = 1e9 + 7;

// binom mod N from TCR
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
vi inverses;
void precompute_inverses() {
	inverses.assign(2002LL, 1LL);
	for (ll i = 2LL; i < 2002LL; ++i)
		inverses[i] = mod_inverse(i, MOD);
}

vi factorials;
constexpr ll iv = 40LL;
void precompute_factorials() {
	ll UB = MOD + 2000LL + 3LL;
	factorials.assign(UB / iv, 1LL);
	for (ll n = 2LL, p = 1LL; n <= UB; ++n) {
		p = (p * n) % MOD;
		if (n % iv == 0LL)
		factorials[n / iv] = p;
	}
}
inline ll compfac(ll n) {
	ll r = factorials[n / iv];
	for (ll i = iv * (n / iv) + 1LL; i <= n; ++i)
		r = (r * i) % MOD;
	return r;
}

void answer(int t, ll ans) {
	cout << "Case #" << t;
	cout << ": " << ans << '\n';
	cerr << "Case " << t << " is " << ans << endl;
}

void solve(int t) {
	cerr << "Starting case " << t << endl;
	ll N, M, sum = 0LL;
	cin >> N >> M;
	vi R(N, 0LL);
	for (ll &v : R) cin >> v, sum += v+v;
	
	if (N == 1) {
		answer(t, M);
		return;
	}
	
	ll n2f = 1LL;
	for (ll n = 2; n + 2 <= N; ++n)
		n2f = (n2f * n) % MOD;
	
	ll ans = 0LL;
	for (int i = 0; i < N; ++i)
		for (int j = i + 1; j < N; ++j) {
			ll space = M - (sum - R[i] - R[j]) - 1LL;
			if (space < 0) continue;
			ll add = (inverses[N] * inverses[N-1]) % MOD;
			add = (add * compfac(space + N)) % MOD;
			add = (add * mod_inverse(compfac(space), MOD)) % MOD;
			//for (ll i = space + 1LL; i <= space + N; ++i)
			//	add = (add * i) % MOD;
			//lucas(space + N, N, MOD);
			//add = (add * n2f) % MOD;
			ans = (ans + add) % MOD;
		}
	
	answer(t, (2LL * ans) % MOD);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	precompute_inverses();
	precompute_factorials();
	
	cerr << "Did precomputation" << endl;
	
	int T;
	cin >> T;
	for (int t = 1; t <= T; ++t) solve(t);
	
	return 0;
}
