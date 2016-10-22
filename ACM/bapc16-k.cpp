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

constexpr ll MOD = 123456789;
ll fix(ll v) {
	return (v%MOD+MOD)%MOD;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	ll S, L;
	cin >> L >> S;
	
	vi dp(L, 0LL);
	dp[0] = 1LL;
	
	ll sum = 1LL;
	for (int i = 1; i < L; ++i) {
		dp[i] = sum;
		if (i >= S) sum -= dp[i - S];
		sum = fix(sum + dp[i]);
	}
	
	// rewrite to dp[i] = sum dp[0..i]
	for (int i = 1; i < L; ++i) {
//		cerr << "dp[" << i << "] = " << dp[i] << endl;
		dp[i] = fix(dp[i] + dp[i - 1]);
//		cerr << "dp[" << i << "] = " << dp[i] << endl;
	}
	
	ll ans = 0LL;
	for (int i = 0; i < S; ++i) {
		ll add = dp[L - 1 - i];
		if (L > S) add -= dp[L - S - 1];
//		cerr << i << ": " << add << endl;
		ans = fix(ans + add);
	}
	
	cout << ans << endl;
	
	return 0;
}
