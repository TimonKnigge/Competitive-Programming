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

const int INF = 2000000000;	                 // 9
const long long LLINF = 9000000000000000000LL;  // 18
const long double LDINF = 1e300;

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<bool> vb;
typedef long long ll;
typedef long double ld;

const int MOD = 1e9 + 7;

#define SZ 4001
int nCk[SZ][SZ];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	
	nCk[0][0] = 1;
	for (int i = 0; i < SZ; ++i) {
		for (int j = (i == 0 ? 1 : 0); j < SZ; ++j) {
			nCk[i][j] = 0;
			if (i > 0) nCk[i][j] = (nCk[i][j] + nCk[i - 1][j]) % MOD;
			if (j > 0) nCk[i][j] = (nCk[i][j] + nCk[i][j - 1]) % MOD;
		}
	}
	// nCk[i][j] = (i + j) choose j

	vector<ll> dp(n + 1, 0);
	dp[0] = dp[1] = 1LL;
	for (int i = 2; i <= n; ++i) {
		for (int j = 0; j < i; ++j) {
			dp[i] = (dp[i] + ((ll(nCk[j][i - 1 - j]) * dp[i - j - 1]) % MOD)) % MOD;
		}
	}

	ll ans = 0LL;
	for (int i = 0; i < n; ++i) {
		ans = (ans + ((ll(nCk[n - i][i])*dp[i]) % MOD)) % MOD;
	}

	cout << ans << endl;

	return 0;
}
