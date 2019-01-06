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

constexpr int INF = 2000000010;
constexpr ll LLINF = 9000000000000000010LL;
constexpr ld PI = acos(-1);

ll gcd(ll a, ll b) { while (b) a %= b, swap(a, b); return a; }
ll lcm(ll a, ll b) { return (a / gcd(a, b)) * b; }
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

vvi pascal(ll n, const ll MOD) {
	vvi nCk(n+1, vi(n+1));
	for (int i = 0; i <= n; ++i)
		nCk[0][i] = 0, nCk[i][0] = 1;
	for (int a = 1; a <= n; ++a)
		for (int b = 1; b <= a; ++b)
			nCk[a][b] = (nCk[a-1][b] + nCk[a-1][b-1]) % MOD;
	return nCk;
}

vvi faulhaber(ll K, const ll MOD) {
	vvi nCk = pascal(2*K, MOD);
	vvi S(K+1);
	for (int k = 0; k <= K; ++k) {
		S[k].push_back(mod_inverse(k+1, MOD));
		for (int i = 0; i < k; ++i) {
			ll T = 0LL;
			for (int j = 0; j <= i; ++j) {
				T = (T + S[k][j] * nCk[k+1-j][k-1-i] % MOD
					* mod_inverse(((i+j)&1) ? (MOD+i-k) : (MOD+k-i), MOD) % MOD) % MOD;
			}
			S[k].push_back(T);
		}
	}
	return S;
}

vi primes(ll N) {
	vi fil(N+1, 1), ret;
	fil[0] = fil[1] = 0;
	for (ll n = 2; n <= N; ++n) {
		if (!fil[n]) continue;
		ret.push_back(n);
		for (ll d = n*n; d <= N; d += n) fil[d] = 0;
	}
	return ret;
}

ll evaluate_faulhaber(ll n, const vi &F, const ll MOD) {
	if (!n) return 0LL;
	ll val = 0LL, m = 1LL;
	for (int i = (int)F.size()-1; i >= 0; --i)
		m = (m * (n % MOD)) % MOD,
		val = (val + m * F[i]) % MOD;
	return val;
}

void solve() {
	ll N, K;
	cin >> N >> K;

	constexpr ll MOD = 1e9+7;
	vvi F = faulhaber(K, MOD);

	vi P = primes((ll)sqrt(N)+10);

	set<ll> _V{N};
	for (auto it = _V.rbegin(); it != _V.rend(); ++it)
		for (ll p : P) {
			ll m = p*p;
			while (m <= *it) _V.insert((*it)/m), m *= p;
		}
	vi V(_V.rbegin(), _V.rend());
	V.push_back(0);

	table<size_t> to_index;
	for (size_t i = 0; i < V.size(); ++i) to_index[V[i]] = i;

	cerr << "Precomputation done" << endl;

	ll ans = 0LL;
	{//for (ll k = 1; k <= K; ++k) {
		// P0 cache.
		vvi cache[2];
		cache[0].assign(K, vi(V.size(), 0));
		cache[1].assign(K, vi(V.size(), 0));
		int cur = 0;
		for (int k = 1; k <= K; ++k)
			for (size_t i = 0; i < V.size(); ++i)
				cache[cur][k-1][i] = evaluate_faulhaber(V[i], F[k], MOD);

		for (size_t j = 0; j < P.size(); ++j) {
			ll p = P[j];
			vi pk(K);
			for (int k = 1; k <= K; ++k) pk[k-1] = powmod(p, k, MOD);
			size_t last = 0;
			for (size_t i = 0; i < V.size(); ++i) {
				if (V[i] < p*p) break;
				vi val(K); //ll val = cache[cur][i];
				for (int k = 1; k <= K; ++k) val[k-1] = cache[cur][k-1][i];
				vi pmk(K);
				for (int k = 1; k <= K; ++k) pmk[k-1] = pk[k-1]*pk[k-1]%MOD;
				for (ll m = 2, pm = p*p/*, pmk = pk*pk%MOD*/; pm <= V[i]; ++m, pm *= p/*, pmk = (pmk * pk) % MOD*/) {
					if(to_index.find(V[i]/pm) == to_index.end()) {
						cerr << "Could not find " << V[i] << "/" << pm <<" = " << V[i]/pm << ", " << "p="<<p<<", m=" << m <<endl;
					}
					if(to_index.find(V[i]/(pm*p)) == to_index.end()) {
						cerr << "Could not find " << V[i] << "/" << pm*p <<" = " << V[i]/(pm*p) << ", " << "p="<<p<<", m=" << m <<endl;
					}
					size_t ind1 = to_index[V[i] / pm];
					size_t ind2 = to_index[V[i] / (pm * p)];
					for (int k = 1; k <= K; ++k) {
						ll SNpm = cache[cur][k-1][ind1]; //cache[cur][to_index[V[i] / pm]];
						ll SNpm1 = cache[cur][k-1][ind2]; //cache[cur][to_index[V[i] / (pm * p)]];
						ll cnt = (SNpm + MOD - SNpm1 * pk[k-1] % MOD);
						ll cor = (MOD - pmk[k-1] + pk[k-1]);
						val[k-1] = (val[k-1] + cnt * cor % MOD) % MOD;
						pmk[k-1] = pmk[k-1] * pk[k-1] % MOD;
					}
				}
				for (int k = 1; k <= K; ++k)
					cache[1-cur][k-1][i] = val[k-1];
				last = i+1;
			}
			if (last < V.size())
				for (int k = 1; k <= K; ++k)
					copy(cache[cur][k-1].begin()+last, cache[cur][k-1].end(), cache[1-cur][k-1].begin()+last);
			cur = 1-cur;
			if (j%100 == 0) cerr << " " << (100.0*j/double(P.size())) << "%" << endl;
		}

		for (int k = 1; k <= K; ++k) {
			ll add = cache[cur][k-1][to_index[N]];
			cerr << "S(" << N << ", " << k << ") = " << add << endl;
			ans = (ans + add) % MOD;
		}
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
