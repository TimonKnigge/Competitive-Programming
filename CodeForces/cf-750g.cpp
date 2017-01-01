#include <iostream> 
#include <cstdio>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <bitset>
#include <numeric>
#include <iterator>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <cassert>

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

#define W(x) cerr << #x << ": " << x << endl;

constexpr ll B = 52;

// carry, bit n., bits
ll dp[2][B+1][B+B+1];

ll solve(ll sum, ll bits, ll dmax, ll emax) {
	ll lastbit = 1;
	while ((1LL<<lastbit) <= sum) ++lastbit;

	for (int carry = 0; carry < 2; ++carry)
		for (int b = 0; b <= bits; ++b)
			dp[carry][0][b] = 0;
	dp[0][0][0] = 1;
	
	for (int b = 1; b < lastbit; ++b) {
		sum >>= 1;
		if (sum&1)
			for (int bt = 0; bt <= bits; ++bt) {
				// turn nothing on
				dp[0][b][bt] = dp[1][b-1][bt];
				// turn d on
				if (bt > 0 && b <= dmax) dp[0][b][bt] += dp[0][b-1][bt-1];
				// turn e on
				if (bt > 0 && b <= emax) dp[0][b][bt] += dp[0][b-1][bt-1];
				// turn d,e on
				if (bt > 1 && b <= dmax && b <= emax)
					dp[1][b][bt] = dp[1][b-1][bt-2];
				else	dp[1][b][bt] = 0;
			}
		else for (int bt = 0; bt <= bits; ++bt) {
				// turn nothing on
				dp[0][b][bt] = dp[0][b-1][bt];
				dp[1][b][bt] = 0; // reset for ease
				// turn d on
				if (bt > 0 && b <= dmax) dp[1][b][bt] += dp[1][b-1][bt-1];
				// turn e on
				if (bt > 0 && b <= emax) dp[1][b][bt] += dp[1][b-1][bt-1];
				// turn d,e on
				if (bt > 1 && b <= dmax && b <= emax)
					dp[1][b][bt] += dp[0][b-1][bt-2];
			}
	}
	ll r = dp[0][lastbit - 1][bits];
	return r;
}

int main() {
	ll s, ans = 0;
	cin >> s;
	
	for (ll d = 1; d <= B; ++d)
		for (ll e = 1; e <= B; ++e) {
			ll G = ((1LL << d) + (1LL << e) - 3LL);
			ll x = s/G;
			if (x < 1) continue;
			ll r = s - x * G;
			r -= ((1LL << (e - 1)) - 1LL);
			if (r < 0) continue;
			if (r > (1LL << d) + (1LL << e) - d - e - 2LL)
				continue;
//			cerr << "Trying " << d << ' ' << e << ", making " << r << ", starting at " << x << endl;
			for (ll bits = r % 2; bits < max(2LL, d + e - 2LL); bits += 2)
				ans += solve(r+bits, bits, d-2, e-2);
		}
	
	cout << ans << endl;
	
	return 0;
}
