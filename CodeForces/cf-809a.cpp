#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ii = pair<ll, ll>;
using vi = vector<ll>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N;
	cin >> N;
	vi X(N, 0LL);
	for (ll &x : X) cin >> x;
	sort(X.begin(), X.end());
	
	constexpr ll MOD = 1000000007;
	constexpr ll TIN = (MOD + 1LL) / 2LL;
	
	ll R = 1LL, L = 1LL;
	for (int i = 0; i < N; ++i) {
		R = (2LL * R);
		if (R >= MOD) R -= MOD;
	}
	
	ll ans = 0LL;
	for (int i = 0; i + 1 < N; ++i) {
		L = (2LL * L);
		if (L >= MOD) L -= MOD;
		R = (TIN * R) % MOD;
		
		ll d = X[i + 1] - X[i];
		ll subsets = (L + MOD - 1LL) * (R + MOD - 1LL) % MOD;
		ans = (ans + d * subsets % MOD) % MOD;
	}
	cout << ans << endl;
	
	return 0;
}
