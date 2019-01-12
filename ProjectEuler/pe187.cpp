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
bool is_prime(ll n) {
	assert(n <= SIZE*SIZE);
	if (n <= SIZE) return spf[n] == n;
	for (ll p : primes) if (n % p == 0LL) return false;
	return true;
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
	sieve(N);

	ll ans = 0LL;
	for (ll n = 2LL; n <= N; ++n) {
		int tot = 0;
		auto f = factor(n);
		for (auto ff : f) tot += ff.exp;
		ans += (tot == 2);
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
