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

ll f(ll n) { return 1LL; }
ll F(ll n) { return n; }
unordered_map<ll, ll> lucy(ll n) {
	ll k = ll(sqrt(n));
	vi V;
	for (ll i = 1; i <= k; ++i) V.push_back(i), V.push_back(n/i);
	sort(V.rbegin(), V.rend());
	V.erase(unique(V.begin(), V.end()), V.end());

	unordered_map<ll, ll> S;
	for (size_t i = 0; i < V.size(); ++i)
		S[V[i]] = F(V[i]) - F(1);

	for (ll p = 2LL; p <= k; ++p)
		if (S[p] > S[p-1]) {
			ll sp = S[p-1];
			for (ll v : V)
				if (v >= p*p)
					S[v] -= f(p)*(S[v/p] - sp);
				else break;
		}
	return S;
}

vi primes(ll N) {
	vi M(N+1, 1), R;
	for (ll n = 2LL; n <= N; ++n)
		if (M[n]) {
			R.push_back(n);
			for (ll d = n*n; d <= N; d += n) M[d] = 0;
		}
	return R;
}

void solve() {
	ll N;
	cin >> N;

	auto S = lucy(N);
	cerr << "Done lucying" << endl;
	vi P = primes((ll)sqrt(N)+4);

	ll ans = 0LL;
	// p^7
	for (ll p : P)
		if (p*p*p*p*p*p*p <= N)
			++ans;
		else
			break;
	// p^3 q
	for (ll p : P)
		if (p*p*p <= N)
			ans += S[N/(p*p*p)] - (p <= N/(p*p*p));
	// p q r
	for (ll p : P)
		for (ll q : P) {
			if (q <= p) continue;
			if (q >= N/(p*q)) break;
			ans += S[N/(p*q)] - S[q];
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
