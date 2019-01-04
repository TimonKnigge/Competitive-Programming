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

constexpr ll MOD = 1e9+7;

void fadd(ll &x, ll &y, ll a, ll b) {
	x = (x*b%MOD + y*a%MOD) % MOD;
	y = y*b%MOD;
}

struct F { ll p; int e; };
void solve() {
	ll n, k;
	cin >> n >> k;

	vector<F> Fs;
	for (ll d = 2; d*d <= n; ++d) {
		if (n%d) continue;
		int e = 0;
		while (!(n%d)) n /= d, ++e;
		Fs.push_back({d, e});
	}
	if (n > 1) Fs.push_back({n, 1});

	ll a = 1LL, b = 1LL;
	for (F f : Fs) {
		vi PN(f.e+1, 0LL), PD(f.e+1, 1LL);
		PN[f.e] = 1LL;

		for (int r = 1; r <= k; ++r) {
			for (int i = 0; i <= f.e; ++i) {
				PD[i] = (PD[i] * (i+1)) % MOD;
				for (int j = 0; j < i; ++j)
					fadd(PN[j], PD[j], PN[i], PD[i]);
			}
		}

		ll x = 0LL, y = 1LL, v = 1LL;
		for (int i = 0; i <= f.e; ++i) {
			fadd(x, y, PN[i]*v%MOD, PD[i]);
			v = (v*f.p) % MOD;
		}
		a = a*x%MOD;
		b = b*y%MOD;
	}
	cout << a*mod_inverse(b, MOD)%MOD << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout << fixed << setprecision(12);
	
	solve();
	
	return 0;
}
