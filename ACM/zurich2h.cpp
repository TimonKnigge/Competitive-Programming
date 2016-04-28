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

void answer(int t, ll ans) {
	cout << t << ' ' << ans << '\n';
}

ll ways(vi &C, ll lowgoal, ll goal, size_t l) {
	if (l >= C.size() || goal < 0) {
		return (lowgoal <= 0 && 0 <= goal ? 1 : 0);
	}
	vvi dp(1+C.size(), vi(goal + 1, 0LL));
	dp[l][0] = 1LL;
	for (size_t i = 0; i < C.size(); ++i) {
		for (ll v = 0LL; v <= goal; ++v) {
			dp[i + 1][v] += dp[i][v];
			if (C[i] + v <= goal)
				dp[i + 1][C[i] + v] += dp[i][v];
		}
	}
	ll ans = 0LL;
	for (ll v = max(0LL, lowgoal); v <= goal; ++v)
		ans += dp[C.size()][v];
	return ans;
}

void solve(int t) {
	int V, D;
	cin >> V >> D;
	
	vi C(V, 0LL);
	ll sum = 0LL;
	for (int i = 0; i < V; ++i)
		cin >> C[i], sum += C[i];
	sort(C.begin(), C.end());
	
	if (sum <= D) {
		answer(t, 1);
		return;
	}
	
	ll ans = 0LL;
	ll sofar = 0LL;
	for (int i = 0; i < V; ++i) {
//		if (i > 0 && C[i] == C[i - 1]) {
//			sofar += C[i];
//			continue;
//		}
		ans += ways(C, D - sofar - C[i] + 1, D - sofar, i + 1);
		sofar += C[i];
	}
	answer(t, ans);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N, t = 1;
	cin >> N;
	while (N--) solve(t++);
	
	return 0;
}
