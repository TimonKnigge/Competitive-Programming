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

ll mod(ll a, ll b) { return ((a % b) + b) % b; }
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
ll mod_inverse(ll a, ll n) {
	ll x, y, d;
	extended_euclid(a, n, x, y, d);
	return (d > 1 ? -1 : mod(x, n));
}
ll powmod(ll b, ll e, ll m) {
	ll p = e<2 ? 1 : powmod((b*b)%m,e/2,m);
	return e&1 ? p*b%m : p;
}

int logfloor(int n) {
	int b = 0;
	while ((1<<(b+1)) <= n) ++b;
	return b;
}

constexpr ll MOD = 1e9+7;

ll nCk(ll n, ll k, const vi &F, const vi &IF) {
	return F[n] * IF[k] % MOD * IF[n-k] % MOD;
}

void solve() {
	int N;
	cin >> N;

	vi F(N+1), IF(N+1);
	F[0] = IF[0] = F[1] = IF[1] = 1LL;
	for (ll n = 2; n <= N; ++n)
		F[n] = n * F[n-1] % MOD,
		IF[n] = mod_inverse(F[n], MOD);

	ll tN = powmod(2, N, MOD);
	vi tN1cn(N+1);
	tN1cn[0] = 1LL;
	for (ll n = 1LL; n <= N; ++n)
		tN1cn[n] = tN1cn[n-1] * (MOD + tN - 1 - (n - 1)) % MOD
						* mod_inverse(n, MOD) % MOD;

	vi T(N+1), L(N+1), W(N+1);
	T[0] = 1,		W[0] = 0,		L[0] = T[0];
	T[1] = tN-1,	W[1] = T[1],	L[1] = 0;


	
	for (ll n = 2; n <= N; ++n)
		T[n] = tN1cn[n] * F[n] % MOD,
		L[n] = (2*MOD + tN1cn[n-1] * F[n-1] % MOD
					- L[n-1] - L[n-2] * (MOD + tN - 1 - (n-2)) % MOD
									* (n - 1) % MOD) % MOD,
		W[n] = (T[n] - L[n]) % MOD;

	cout << W[N] << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout << fixed << setprecision(12);
	
	solve();
	
	return 0;
}
