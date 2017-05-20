#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using iiii = pair<pair<int, int>, pair<int, int>>;
using ii = pair<ll, ll>;
using vi = vector<ll>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

constexpr ll MOD = 1000000007LL;

ii query(ll x, ll y, ll k, ll M) {
	if (x <= 0 || y <= 0 || M <= 0 || k < 0) return {0LL, 0LL};

	ll TK = (1LL << k), cnt = 0LL, sum = 0LL;

	// Bottom out recursion if at least one of x/y is large enough.
	if (TK <= max(x, y)) {
		ll each = min(TK, min(x, y)) % MOD;
		ll upto = min(M, TK) % MOD;
		cnt = each * upto % MOD;
		sum = each * (upto * (upto + 1LL) / 2LL % MOD) % MOD;
	} else if (k > 0LL) {
		// Subquery!
		ll TKS = TK / 2LL;
		ii r00 = query(x, y, k - 1LL, M);
		ii r10 = query(x - TKS, y, k - 1LL, M - TKS);
		ii r01 = query(x, y - TKS, k - 1LL, M - TKS);
		ii r11 = query(x - TKS, y - TKS, k - 1LL, M);
		
		sum = r00.first + r10.first + r01.first + r11.first;
		sum %= MOD;
		sum += (r10.second + r01.second) * TKS % MOD;
		sum %= MOD;
		
		cnt = r00.second + r01.second + r10.second + r11.second;
		cnt %= MOD;
	}
	
	return {sum, cnt};
}

void query() {
	ll x1, y1, x2, y2, M;
	cin >> x1 >> y1 >> x2 >> y2 >> M;
	
	ll k = 1LL;
	while ((1LL << k) <= max(x2, y2)) ++k;
	ll ans = query(x2, y2, k, M).first
		- query(x2, y1 - 1LL, k, M).first
		- query(x1 - 1LL, y2, k, M).first
		+ query(x1 - 1LL, y1 - 1LL, k, M).first;
	ans = (ans % MOD + MOD) % MOD;
	cout << ans << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int q;
	cin >> q;
	while (q--) query();
	
	return 0;
}
