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
using ii = pair<int,int>;
using iii = pair<int, ii>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int T;
	cin >> T;
	for (int t = 1; t <= T; ++t) {
		ll N;
		cin >> N;
		
		ld W[2], L[2];
		cin >> W[0] >> W[1] >> L[0] >> L[1];
		
		// The chance of player one winning/losing in:
		// [2^k games][if he (p1) plays color 0/1]
		ld dp[35][2];
		dp[0][0] = 1 - L[0];
		dp[0][1] = 1 - L[1];
		
		for (int k = 1; k < 35; ++k) {
			// We play 2^k games. We want it to be our turn at the end
			dp[k][0] = 
				dp[k-1][0] *max(dp[k-1][0], dp[k-1][1])
			+  (1 - dp[k-1][0])*min(dp[k-1][0], dp[k-1][1]);
			dp[k][1] =
				dp[k-1][1] *max(dp[k-1][0], dp[k-1][1])
			+  (1 - dp[k-1][1])*min(dp[k-1][0], dp[k-1][1]);
			
//			cerr << "dp[" << k << "][0] = " << dp[k][0]<<endl;
//			cerr << "dp[" << k << "][1] = " << dp[k][1] << endl;
		}
		
		ld dp2[2];
		dp2[0] = W[0];
		dp2[1] = W[1];
		ll M = N - 1;
		for (int i = 0; i < 35; ++i) {
			if (((M >> i)&1LL) != 1LL) continue;
			ld t1[2];
//			cerr << dp[i][0] << ' ' << dp[i][1] << ' ' << dp2[0] << ' ' << dp2[1] << endl;
			t1[0] = dp[i][0] *min(dp2[0], dp2[1])
			+  (1 - dp[i][0])*max(dp2[0], dp2[1]);
			t1[1] = dp[i][1] *min(dp2[0], dp2[1])
			+  (1 - dp[i][1])*max(dp2[0], dp2[1]);
			
			dp2[0] = t1[0];
			dp2[1] = t1[1];
		}
		
		printf("Case #%d: %.7lf\n", t, double(dp2[0]));
	}
	
	return 0;
}
