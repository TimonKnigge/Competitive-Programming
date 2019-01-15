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
vector<ll> P;
vector<int> spf;
void sieve(ll size=1e6) {	// Initialize once in main.
	spf.assign((SIZE = size) + 1, 0);
	spf[0] = spf[1] = 1;
	for (ll i = 2; i <= SIZE; i++) {
		if (!spf[i]) P.push_back(spf[i] = i);
		for (ll p : P) {
			if (i*p > SIZE) break;
			spf[i*p] = p;
			if (spf[i] == p) break;
		}
	}
}

void solve() {
	int N, K;
	cin >> N >> K;

	sieve(N);

	ll ans = 0LL;
	vi phi(N+1), L(N+1);
	phi[1] = 1;
	L[1] = 1;
	for (ll n = 2; n <= N; ++n) {
		ll m = n/spf[n];
		if (m%spf[n])
			phi[n] = phi[m]*(spf[n]-1);
		else
			phi[n] = phi[m]*spf[n];

		L[n] = L[phi[n]]+1;
		assert(L[n] > 0 && phi[n] > 0);
		if (L[n] == K && spf[n] == n)
			ans += n, cerr << "Adding " << n << endl;
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
