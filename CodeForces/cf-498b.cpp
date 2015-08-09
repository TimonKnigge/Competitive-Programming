#include <iostream>
#include <iomanip>
#include <vector>	       
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <bitset>
#include <algorithm>
#include <functional>
#include <string>
#include <string.h>  // Include for memset!
#include <complex>
#include <random>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cstdio>

const int INF = 2000000000;			// 9
const long long LLINF = 9000000000000000000LL;	// 18
const long double LDINF = 1e300;

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<bool> vb;
typedef long long ll;
typedef double ld;

ld pw(ld x, int n) {
	if (n == 0) return 1.0;
	if (n == 1) return x;
	if (n % 2 == 0) return pw(x * x, n / 2);
	return x * pw(x * x, (n - 1) / 2);
}

int main(){
	
	int n, T;
	scanf("%d %d", &n, &T);
	vector<int> _t(n, 0);
	vector<ld> p(n, 0.0), pforced(n, 0.0);
	for (int i = 0; i < n; ++i) {
		int paa;
		scanf("%d %d", &paa, &_t[i]);
		p[i] = paa / 100.0;
		pforced[i] = pw(1 - p[i], _t[i] - 1);
	}
	
	ld ans = 0.0;
	vector<vector<ld>> dp(T + 1, vector<ld>(2, 0.0)), dp2(T + 1, vector<ld>(2, 0.0));
	dp[0][0] = dp2[0][0] = 1.0;
	for (int s = 0; s <= n; ++s) {

		for (int t = 0; t <= T; ++t) {
			dp[t][(s + 1)%2] = dp2[t][(s + 1)%2] = 0.0;
		}
		for (int t = 0; t < T; ++t) {
			// dp[ time ] [ songs ]
			ld r = 0.0, a = 0.0;
			if (s + 1 <= n) {
				r = p[s];
				dp[t + 1][(s + 1)%2] += r * dp[t][s%2];
				dp2[t + 1][(s + 1)%2] += r * dp[t][s%2];
				if (t + 1 >= _t[s]) {
					a = pforced[s] * dp2[t + 1 - _t[s]][s%2];
					dp[t + 1][(s + 1)%2] += a * (1 - r);
					dp2[t + 1][(s + 1)%2] += a * (1 - r);
					dp[t][s%2] -= a;
				}
			}
			if (s <= n) {
				dp[t + 1][s%2] += (1 - r) * dp[t][s%2];
			}
		}
		if (s <= n) ans += s*dp[T][s%2];
	}
	
//	for (int s = 0; s <= n; ++s) {
//	for (int tt = 0; tt <= T; ++tt)
//		cerr << dp[tt][s] << '\t';cerr <<endl;}

	printf("%.8lf\n", double(ans));
	
	return 0;
}
