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

struct custom_hash {
	static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31); }
	size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM
			= chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM); } };

template<class TOut>
using table = gp_hash_table<uint64_t, TOut, custom_hash>;

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

// All modular inverses of [1..n] mod P in O(n) time.
vi inverses(ll n, ll P) {
	vi I(n+1, 1LL);
	for (ll i = 2; i <= n; ++i)
		I[i] = mod(-(P/i) * I[P%i], P);
	return I;
}

// Solves x = a1 mod m1, x = a2 mod m2, x is unique modulo lcm(m1, m2).
// Returns {0, -1} on failure, {x, lcm(m1, m2)} otherwise.
pair<ll, ll> crt(ll a1, ll m1, ll a2, ll m2) {
	ll s, t, d;
	extended_euclid(m1, m2, s, t, d);
	if (a1 % d != a2 % d) return {0, -1};
	return {mod(s*a2 %m2 * m1 + t*a1 %m1 * m2, m1 * m2) / d, m1 / d * m2};
}

ll binom(ll n, ll k, const vi &invs, ll P) {
	if (k > n/2) k = n-k;
	ll r = 1LL;
	for (ll x = 1LL; x <= k; ++x)
		r = r * (n - x + 1LL) % P * invs[x] % P;
	return r;
}

vi getD(ll n, ll c, ll P) {
	const vi invs = inverses(n+c+5, P);

	vi binoms(c+1, 1LL);
	for (ll k = 1LL; k <= c; ++k)
		binoms[k] = binoms[k-1] * (c - k + 1LL) % P * invs[k] % P;

	vi D(n+1, 0LL);
	D[0] = 1LL;
	D[2] = (c >= 2 ? binoms[2] : 0LL);
	for (ll v = 4LL; v <= n; v += 2LL) {
		if (v % 4 == 2LL) {
			ll z = (v-2LL)/4LL;
			for (ll m = 0LL; 2+4*m <= c && 2*z-2*m >= 0; ++m)
				D[v] = (D[v] + binoms[2+4*m] * D[2*z-2*m]) % P;
		} else {
			ll z = (v-4LL)/4LL;
			for (ll m = 0LL; 4*m <= c && 2*(z+1)-2*m >= 0; ++m)
				D[v] = (D[v] + binoms[4*m]*D[2*(z+1)-2*m]) % P;
		}
	}

	return D;
}

ll nzcnt2(ll n, ll c, ll P) {
	ll ans = 0LL;
	for (ll m = 0LL; m < (1<<n); ++m) {
		if (__builtin_popcount(m) != c) continue;
		vector<int> gaps;
		int cnt = 0;
		for (int j = n-1; j >= 0; --j)
			if ((m>>j)&1LL)
					gaps.push_back(cnt), cnt = 0;
			else	++cnt;
		gaps.push_back(cnt);
		int x = 0;
		for (size_t i = 1; i < gaps.size(); i += 2)
			x ^= gaps[i];
		if (x) ++ans;
	}
	return ans;
}

// Count ordered vectors summing to n with c elements,
// with the xor of even positions nonzero.
ll nzcnt(ll n, ll c, ll P) {
	const vi invs = inverses(n+c+5, P);
	const vi D = getD(n, c/2, P);
	const ll total = binom(n+c-1, c-1, invs, P);

	ll ans = 0LL;
	for (ll i = 0; i <= n; ++i) {
		ans = (ans + D[i] * binom((n-i)+(c+1)/2-1, (c+1)/2-1, invs, P)) % P;
	}
	ans = (total - ans) % P;
	return ans;
}

ll solve_mod(ll n, ll k, ll P) {
	const vi invs = inverses(n+3, P);

	ll ans = 0LL;
	// Silver coin first.
	{
		ans = (ans + binom(n, k+1, invs, P)) % P;
	}
	// Silver coin second.
	{
		ans = (ans + nzcnt(n-(k+1), k+2, P)) % P;
	}
	// Silver coin in spot v > 2.
	{
		ll incr = (nzcnt(n+1-(k+1), k+2, P) + P-nzcnt(n-k, k+1, P)) % P;
		ans = (ans + (k+1 - 2) * incr % P) % P;
	}
	return ans;
}

void solve() {
	long long n, c;
	cin >> n >> c;

	constexpr ll P1 = 1000003LL;
	constexpr ll P2 = 1000033LL;
	ii ans = crt(
		solve_mod(n, c, P1), P1,
		solve_mod(n, c, P2), P2);
	assert(ans.second == P1*P2);
	cout << (long long)ans.first << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout << fixed << setprecision(12);
	
	solve();
	
	return 0;
}
