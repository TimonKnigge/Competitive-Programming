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

template<class T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<class TIn, class TOut = null_type>
using order_tree = tree<TIn, TOut, less<TIn>, rb_tree_tag,
	tree_order_statistics_node_update>;

constexpr int INF = 2000000010;
constexpr ll LLINF = 9000000000000000010LL;

constexpr ll MOD = 1e9+7;

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

ll modpow(ll a, ll b) {
	if (!b) return 1LL;
	if (b == 1LL) return a;
	ll r = modpow(a * a % MOD, b / 2);
	if (b&1) r = (r * a) % MOD;
	return r;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N, K;
	cin >> N >> K;

	ll ans = 0LL, binom = 1LL;
	for (int i = 0; i <= K; ++i) {
		ll mul = ((i&1) ? -1 : 1);
		ll pw = modpow(K - i, N);
		ans = (ans + mul * pw * binom % MOD + MOD) % MOD;
		binom = (binom * (N + 1LL - i) % MOD) * mod_inverse(i + 1, MOD) % MOD;
	}
	cout << ans << endl;
	
	return 0;
}
