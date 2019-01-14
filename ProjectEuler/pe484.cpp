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

vi primes(ll N) {
	vector<bool> f(N/2+15, true);
	vi r{2,3,5};
	r.reserve(N / ll(log(N)) + 10);
	for (ll d = 3*3; d <= N; d += 6) f[d/2] = 0;
	for (ll d = 5*5; d <= N; d += 10) f[d/2] = 0;
	for (ll n = 9; n <= N+2; n += 6) {
		// n-2
		if (f[(n-2)/2]) {
			ll nn = n-2;
			r.push_back(nn);
			for (ll d = nn*nn; d <= N; d += (nn<<1))
				f[d/2] = 0;
		}
		// n+2
		if (f[(n+2)/2]) {
			ll nn = n+2;	
			r.push_back(nn);
			for (ll d = nn*nn; d <= N; d += (nn<<1))
				f[d/2] = 0;
		}
	}
	while (r.back() > N) r.pop_back();
	return r;
}
vi makeV(ll N, const vi &P) {
	set<ll> V{N, 0LL};
	vi ret;
	for (auto it = V.rbegin(); it != V.rend(); ++it) {
		ll v = *it;
		for (ll p : P) {
			ll m = p*p;
			if (m > v) break;
			while (true) { //m <= v) {
				V.insert(v/m);
				if (m > v/p) break;
				m *= p;
			}
		}
		ret.push_back(v);
	}
	return ret;
}

ll gcd(ll a, ll b) { while (b) a %= b, swap(a, b); return a; }
ll bruteforce(ll N) {
	vi spf(N+1, 0LL);
	for (ll n = 2; n <= N; ++n) {
		if (spf[n]) continue;
		spf[n] = n;
		for (ll d = n*n; d <= N; d += n)
			if (!spf[d]) spf[d] = n;
	}
	vi D(N+1, 0LL);
	for (ll n = 2; n <= N; ++n) {
		if (spf[n] == n)
				D[n] = 1LL;
		else	D[n] = D[spf[n]]*(n/spf[n]) + spf[n]*D[n/spf[n]];
	}
	vi G(N+1, 0LL);
	for (ll n = 2; n <= N; ++n)
		G[n] = gcd(D[n], n);
	return std::accumulate(G.begin(), G.end(), 0LL);
}

size_t index_of(ll v, const vi &V) {
	auto it = lower_bound(V.rbegin(), V.rend(), v);
	assert((*it) == v);
	return distance(it, --V.rend());
}
ll lucy(ll N) {
	vi P = primes((ll)sqrt(N)+3);
	cerr << "Done sieving." << endl;
	vi V = makeV(N, P);
	cerr << "Done preprocessing, found " << P.size() << " primes and "
		<< V.size() << " stepping values." << endl;

	vi cache[2];
	cache[0].assign(V.size(), 0);
	cache[1].assign(V.size(), 0);
	int cur = 0;
	for (size_t i = 0; i < V.size(); ++i)
		cache[cur][i] = V[i];

	for (size_t j = 0; j < P.size(); ++j) {
		ll p = P[j];
//		cerr << "Now processing prime " << p << endl;
		size_t last = 0;
		for (size_t i = 0; i < V.size(); ++i) {
			if (V[i] < p*p) break;
			ll val = cache[cur][i];
			size_t i1, i2 = index_of(V[i] / (p * p), V);
			for (ll m = 2, pm = p*p; pm <= V[i]; ++m, pm *= p) {
				swap(i1, i2);
				i2 = index_of((V[i]/p >= pm ? V[i] / (pm * p) : 0LL), V);
				ll vpk  = cache[cur][i1];
				ll vpk1 = cache[cur][i2];
				val = val + (vpk - vpk1) * (-1 + ((m%p) ? pm/p : pm));
				if (pm > V[i] / p) break;
			}
			cache[1-cur][i] = val;
			last = i+1;
		}
//		cerr << "Done with prime " << p << ", last = " << last << " which is "
//			<< V[last] << endl;
		if (last < V.size())
			std::copy(	cache[cur].begin()+last,
						cache[cur].end(),
						cache[1-cur].begin()+last);
		cur = 1 - cur;
		if (j%1000 == 0)
			cerr << "  update: " << (100.0*j/double(P.size())) << "%, at prime"
				<< P[j] << " with answer " << cache[cur][0] << endl;
	}
	return cache[cur][0];
}

void solve() {
	long long N;
	cin >> N;

	if (N <= 1e5) {
		cout << "Bruteforce gives " << (long long)bruteforce(N) << endl;
	}
	long long ans = lucy(N);
	cout << "Answer: " << ans << endl;
	cout << "(possibly " << ans-1 << "?)" << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout << fixed << setprecision(12);
	
	solve();
	
	return 0;
}
