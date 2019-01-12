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

constexpr ll M = 1000000000LL * 1000000000LL;

template <class T>
struct FenwickTree {		// use 1 based indices!!!
	int n; vector<T> tree;
	FenwickTree(int n) : n(n) { tree.assign(n + 1, 0); }
	T query(int l, int r) { return (M+query(r)-query(l - 1))%M; }
	T query(int r) {
		T s = 0;
		for(; r > 0; r -= (r & (-r))) s = (s+tree[r])%M;
		return s;
	}
	void update(int i, T v) {
		for(; i <= n; i += (i & (-i))) tree[i] = (tree[i]+v)%M;
	}
};

ll SIZE;
vector<ll> primes, spf;

void sieve(ll size=1e6) {	// Initialize once in main.
	spf.assign((SIZE = size) + 1, -1);
	spf[0] = spf[1] = 1;
	for (ll i = 2; i <= SIZE; i++)
		if (spf[i] < 0) {
			spf[i] = i, primes.push_back(i);
			for (ll j = i * i; j <= SIZE; j += i)
				if (spf[j] < 0) spf[j] = i;
		}
}
struct Factor{ ll p; ll exp; };
using FS = vector<Factor>;
FS factor(ll n){ // Up to SIZE^2
	FS fs;
	for (size_t i = 0; i < primes.size() && n > SIZE; ++i)
		if (n % primes[i] == 0) {
			fs.push_back({primes[i], 0});
			while (n % primes[i] == 0)
				fs.back().exp++, n /= primes[i];
		}
	if (n <= SIZE) {
		for(; n>1; n /= spf[n]) {
			if (!fs.empty() && fs.back().p == spf[n])
				++fs.back().exp;
			else fs.push_back({spf[n], 1});
		}
	} else fs.push_back({n, 1});
	return fs;
}

void solve() {
	int N;
	cin >> N;
	sieve(N+5);
	cerr << "Done sieving" << endl;

	vi dt(N+1);
	dt[1] = 1;
	for (ll n = 2LL; n <= N; ++n) {
		FS f1 = factor((n&1) ? n : n/2);
		FS f2 = factor((n&1) ? (n+1)/2 : n+1);

		unordered_map<ll, ll> fm;
		for (Factor f : f1) fm[f.p] += f.exp;
		for (Factor f : f2) fm[f.p] += f.exp;

		ll ds = 1LL;
		for (auto it : fm) ds *= (1 + it.second);
		dt[n] = ds;
	}
	ll MX = *max_element(dt.begin(), dt.end());
	cout << "No more than " << MX << " factors" << endl;

	ll ans = 0LL;
	FenwickTree<ll> ft1(MX+5);
	FenwickTree<ll> ft2(MX+5);
	for (ll n = N; n >= 1; --n) {
		ans = (ans + ft2.query(dt[n]-1)) % M;
		ft2.update(dt[n], ft1.query(dt[n]-1));
		ft1.update(dt[n], 1);
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
