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
	
	int d, k;
	cin >> d >> k;
	vi r(d, 0LL), p(d, 0LL);
	for (int i = 0; i < d; ++i) cin >> r[i] >> p[i];
	
	vvi dp(d+1, vi(k+1, LLINF));
	dp[0][0] = 0LL;
	for (int g = 1; g <= k; ++g) for (int n = 1; n <= d; ++n) {
		ll a = 0LL, b = 0LL, c = 0LL;
		for (int i = n; i >= 1; --i) {
			a += p[i-1];
			b -= 2LL * p[i-1] * r[i-1];
			c += p[i-1] * r[i-1] * r[i-1];
			if (dp[i - 1][g - 1] == LLINF) continue;
			ll s = (a>0?1:-1)*(b>0?1:-1);
			ll pm = (-s) * (abs(b) / (2LL * abs(a)));
			for (ll p = pm - 2LL; p <= pm + 2LL; ++p) {
				ll cost = dp[i - 1][g - 1];
				cost += a * p * p;
				cost += b * p;
				cost += c;
				if (dp[n][g] == LLINF || dp[n][g] > cost)
					dp[n][g] = cost; 
			}
		}
	}
	
	cout << dp.back().back() << endl;
	
	return 0;
}
