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

ll nsum(ll N) {
	return N * (N + 1LL) / 2LL;
}

ll solve(ll S, ll K) {
	if (S <= 1) return S;
	if (K >= S) K = LLINF;
	
	// divide S into K+1 parts
	ll sz = S/(K+1);
	ll rem = S % (K+1);
//	if (rem == 0) rem = K+1;
	
	// rem parts of size sz+1, the rest of size sz
	return rem * nsum(sz+1) + (K+1 - rem) * nsum(sz);
}

int main() {
	
	int N, M, K;
	scanf("%d %d %d", &N, &M, &K);
	
	vi S(M, 0LL);
	while (N--) {
		int v;
		scanf("%d", &v);
		S[v - 1]++;
	}
	
	vector<vector<ll> > dp(M, vector<ll>(K + 1, LLINF));
	for (int m = 0; m < M; ++m) {
		dp[m][0] = nsum(S[m]) + (m > 0 ? dp[m-1][0] : 0LL);
		for (int s = 0; s <= K; ++s) {
			ll cost = solve(S[m], s);
			if (m == 0) dp[m][s] = cost;
			else for (int r = 0; r + s <= K; ++r)
				dp[m][r+s] = min(dp[m][r+s], dp[m-1][r]+cost);
		}
	}
	
	ll ans = dp[M - 1][0];
	for (int s = 1; s <= K; ++s)
		ans = min(ans, dp[M - 1][s]);
	cout << ans << endl;
	
	return 0;
}
