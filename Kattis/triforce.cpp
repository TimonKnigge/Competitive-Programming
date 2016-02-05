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
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

ll MOD = 1e6 + 9;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N;
	cin >> N;
	
	vector<ll> dp(N, 0LL);
	dp[0] = 1;
	for (int i = 0; i < N; ++i) {
	//	cerr << "dp[" << i << "] = " << dp[i] << endl;
		if (i + 1 < N) dp[i + 1] = (dp[i+1] + 2 * dp[i]) % MOD;
		if (i  ==   0) dp[i + 1] = (dp[i+1] +     dp[i]) % MOD;
		if (i+2  == N) dp[i + 1] = (dp[i+1] +     dp[i]) % MOD;
		if (i + 2 < N) dp[i + 2] = (dp[i+2] + 4 * dp[i]) % MOD;
		if (i + 3 < N) dp[i + 3] = (dp[i+3] + 2 * dp[i]) % MOD;
	}
	
	cout << dp[N - 1] << endl;
	
	return 0;
}
