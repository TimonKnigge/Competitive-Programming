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

vector<int> calculate_phi(int n) {
	vector<int> phi(n + 1, 0);
	iota(phi.begin(), phi.end(), 0);
	for (int i = 2; i <= n; ++i)
		if (phi[i] == i)
			for (ll j = i; j <= n; j += i)
				phi[j] -= phi[j] / i;
	return phi;
}

ll gcd(ll a, ll b) { while (b) a %= b, swap(a, b); return a; }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	// Cuberoot of N should suffice for PHI.
	ll N, PHI_UB = 5e6;
	cin >> N; // >> PHI_UB;

	ll ans = 0LL;
	vector<int> phi = calculate_phi(PHI_UB);

	// First greedily pick vectors while possible (but end one step early).
	ll len = 2LL;
	for (;; ++len) {
		ll displ = phi[len] * len / 2;
		if (displ <= N) {
			N -= displ;
			ans += phi[len];
		} else break;
	}

	// Now we carefully fill up the remaining N x N box with `len` vectors.
	for (ll a = 1LL; a <= len / 2; ++a) {
		if (gcd(a, len - a) > 1LL) continue;
		if (len <= N) {
			N -= len;
			ans += 2;
		} else if (max(a, len - a) <= N) {
			N -= max(a, len - a);
			++ans;
			break;
		}
	}

	cout << ans+1 << endl;
	
	return 0;
}
