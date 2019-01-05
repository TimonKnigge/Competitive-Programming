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

constexpr ll MOD = 1e9+7;

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
// solves ab = 1 (mod n), -1 on failure
ll mod_inverse(ll a, ll n) {
	ll x, y, d;
	extended_euclid(a, n, x, y, d);
	return (d > 1 ? -1 : mod(x, n));
}
ll powmod(ll b, ll e, ll m) {
	ll p = e<2 ? 1 : powmod((b*b)%m,e/2,m);
	return e&1 ? p*b%m : p;
}

struct F { ll p; int e; };
void solve() {
	ll N;
	cin >> N;

	vector<vector<F>> pf(N+1);
	for (ll n = 2; n <= N; ++n) {
		ll nn = n;
		for (ll d = 2; d*d <= nn; ++d) {
			if (nn%d) continue;
			int e = 0;
			while (!(nn%d)) nn /= d, ++e;
			pf[n].push_back({d, e});
		}
		if (nn>1) pf[n].push_back({nn, 1});
	}
	cerr << "Done factoring" << endl;

	ll ans = 1LL;
	map<ll, ll> fac, ct;
	for (ll n = 2; n <= N; ++n) {
		for (F f : pf[n])
			fac[f.p] += f.e;
		for (auto it : fac)
			ct[it.first] += it.second;

		ll inc = 1LL;
		for (auto it : fac) {
			ll p = it.first, e = it.second * (n+1) - 2*ct[it.first];
			ll x = (MOD + 1 - powmod(p, e+1, MOD)) % MOD;
			ll y = (MOD + 1 - p) % MOD;
			inc = inc * x % MOD * mod_inverse(y, MOD) % MOD;
		}
		ans = (ans + inc) % MOD;
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
