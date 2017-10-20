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

ll cube_sum(ll n, ll m) {
	ll l = n, r = n + 1LL;
	if (l&1LL) r /= 2LL; else l /= 2LL;
	ll prod = (l % m) * (r % m) % m;
	return prod * prod % m;
}

constexpr ll MOD = 1000000000;

int main() {

	ll N;
	cin >> N;
	int SN = int(sqrt(N));
	cerr << "N = " << N << ", N^(1/2) = " << SN << endl;

	// Gather all primes upto SN.
	vi isp(SN+1, 1), cbm(1, 1LL);
	map<ll, size_t> ps;
	isp[0] = isp[1] = 0;
	for (ll p = 2; p <= SN; ++p) {
		if (!isp[p]) continue;
		ps.insert({p, 0});
		for (ll v = p * p; v <= SN; v += p)
			isp[v] = 0;
	}
	{
		// Initialize primes at 1, keep room for `1`.
		size_t i = 1;
		for (auto &pr : ps)
			pr.second = i++,
			cbm.push_back((pr.first * pr.first % MOD) * pr.first % MOD);
	}

	// Gather all v that can be written as N / k.
	map<ll, size_t> vs;
	for (ll d = 1LL; d * d <= N; ++d) {
		vs[N / d] = 0;
		if (N / (N / d) == d)
			vs[d] = 0;
	}
	{
		size_t i = 0;
		for (auto &pr : vs) pr.second = i++;
	}
	cerr << "|ps| = " << ps.size() << ", |vs| = " << vs.size() << endl;

	// Compute sum of cube of primes. That is:
	//	S[n][p] = sum of all i^3 for i from 2 to n, and i either prime or not
	// 	divisible by a number upto p.
	vvi S(vs.size());
	for (auto it = vs.begin(); it != vs.end(); ++it) {
		ll v = it->first;
		size_t i = it->second;
		if (i % 10000 == 0) cerr << "Status: " << v << ' ' << i << endl;
		{
			auto it2 = ps.lower_bound(ll(sqrt(v)) + 2LL);
			if (it2 == ps.end()) --it2;
			S[i].assign(it2->second + 1, 0);
		}
		S[i][0] = cube_sum(v, MOD);
		for (auto it2 = ps.begin(); it2 != ps.end(); ++it2) {
			ll p = it2->first;
			size_t j = it2->second;
			if (j == 0) continue;
			if (j >= S[i].size()) break;
			S[i][j] = S[i][j - 1];
			if (p * p > v) continue;
			ll df = MOD;
			{
				size_t vi = vs[v / p];
				size_t vj = min(j, S[vi].size()) - 1;
				df += S[vi][vj];
				df -= S[vs[p - 1]].back();
				df %= MOD;
			}
			S[i][j] = (ll(S[i][j] + MOD - (df * cbm[j] % MOD)) % MOD);
		}
	}

	cerr << "Check: Sum of prime cubes upto N is " << S.back().back() << endl;

	ll ans = 0LL;
	// Loop over the smallest prime in the product.
	for (ll s = 1LL; s <= SN; ++s) {
		if (!isp[s]) continue;
		ll rhs = (S[vs[N / s]].back() + MOD - S[vs[s]].back()) % MOD;
		ans = (ans + cbm[ps[s]] * rhs % MOD) % MOD;
	}
	cout << ans << endl;
	
	return 0;
}
