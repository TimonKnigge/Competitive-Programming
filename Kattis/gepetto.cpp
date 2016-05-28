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

int main() {
	
	int N, C;
	scanf("%d %d", &N, &C);
	
	vi E(N, 0LL);
	while (C--) {
		int u, v;
		scanf("%d %d", &u, &v);
		--u; --v;
		E[u] |= 1LL<<v;
		E[v] |= 1LL<<u;
	}
	
	vi dp(1LL<<N, 0LL);
	dp[0] = 1LL;
	for (int u = 0; u < N; ++u) {
		ll b = 1LL<<u;
		for (int m = (1LL<<N) - 1LL; m >= 0; --m) {
			if ((m&E[u]) != 0LL) continue;
			dp[m|b] += dp[m];
		}
//		for (int m = 0; m < (1LL<<N); ++m)
//			cerr << dp[m] << ' ';
//		cerr << endl;
	}
	
	ll ans = 0LL;
	for (int m = 0; m < (1LL<<N); ++m)
		ans += dp[m];
	cout << ans << endl;
	
	return 0;
}
