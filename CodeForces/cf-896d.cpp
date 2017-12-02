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

ll modpow(ll a, ll b, ll m) {
	if (b == 0) return 1LL;
	return modpow(a*a%m, b/2, m) * ((b&1) ? a : 1LL) % m;
}

template <ll N>
struct nCkMp {
	ll p, phi;
	vi ds, fac, ifac;
	vvi cs;
	nCkMp(ll _p) : p(_p), phi(_p), fac(N+1, 1LL), ifac(N+1, 1LL), cs(N+1) {
		for (int d = 2; d * d <= _p; ++d) {
			if (_p % d != 0) continue;
			ds.push_back(d);
			while (_p % d == 0) _p /= d;
		}
		if (_p > 1) ds.push_back(_p);
		for (ll d : ds) phi = phi / d * (d - 1);
		cs[0].assign(ds.size(), 0LL);
		for (ll i = 1LL; i <= N; ++i) {
			cs[i] = cs[i-1];
			ll nd = i;
			for (size_t j = 0; j < ds.size(); ++j)
				while (nd % ds[j] == 0) ++cs[i][j], nd /= ds[j];
			fac[i] = (nd * fac[i - 1]) % p;
			ifac[i] = modpow(fac[i], phi - 1, p);
		}
	}
	// 0 <= k, n <= N
	ll nCk(ll n, ll k) {
		if (n < k) return 0LL;
		ll ans = fac[n] * ifac[k] % p * ifac[n-k] % p;
		for (size_t j = 0; j < ds.size(); ++j)
			ans = ans * modpow(ds[j], cs[n][j] - cs[k][j] - cs[n-k][j], p) % p;
		return ans;
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, p, l, r;
	cin >> n >> p >> l >> r;

	nCkMp<100020> magic(p);

	ll ans = 0LL;
	for (int length = 0; length <= n; ++length) {
		ll add = magic.nCk(n, n - length);
		ll lt = l, rt = min(r, length);
		if ((lt&1) != (length&1)) ++lt;
		if ((rt&1) != (length&1)) --rt;
		if (lt > rt) continue;

		// If we end up with x \in [lt, rt] in the end, we need exactly:
		// x + (length-x)/2 = (length+x)/2 50's. Note that length/lt/rt are
		// equal mod 2.
		lt = (length + lt) / 2;
		rt = (length + rt) / 2;

		add = add * (p + magic.nCk(length, lt) - magic.nCk(length, rt+1));
		ans = (ans + add) % p;
	}

	cout << ans << endl;
	
	return 0;
}
