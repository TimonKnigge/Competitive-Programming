// O(p . n^2)

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
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000LL;

int main() {
	
	int p, n;
	scanf("%d %d", &n, &p);
	
	vi a(n, 0), b(n, 0);
	for (int i = 0; i < n; ++i)
		scanf("%d %d", &a[i], &b[i]);
	
	// Split into bad and good intervals as described
	// in the jury solutions.
	vii bad;
	vector<ll> good;
	for (int i = 0; i < n; ++i) {
		bool g = false;
		for (int j = 0; j < n; ++j) {
			if (a[i] <= a[j] && b[i] >= b[j]) {
				// v For duplicate intervals
				if (i < j || a[i] < a[j] || b[i] > b[j])
					g = true;
			}
		}
		if (g) good.push_back(b[i] - a[i]);
		else bad.push_back({a[i], b[i]});
	}
	
	// Sort the bad intervals by increasing a
	sort(bad.begin(), bad.end());
	
	// dp[intervals 0..i used][spread over lines 0..p]
	vector<vector<ll> > dp(bad.size(), vector<ll>(p, -1));
	
	// Fill dp[..][0]
	int l = bad[0].first, r = bad[0].second;
	dp[0][0] = r - l;
	for (int j = 1; j < bad.size(); ++j) {
		l = bad[j].first;
		if (l < r) dp[j][0] = r - l;
		else dp[j][0] = -1;
	}
	
	// Fill other lines
	for (int j = 1; j < p; ++j) {
		// We can start at j, assuming the groups
		// are ordered left to right as well.
		for (int k = j; k < bad.size(); ++k) {
			// find a good splitting point
			l = bad[k].first;
			r = bad[k].second;
			ll best = -1;
			if (dp[k - 1][j - 1] > -1)
				best = r - l + dp[k - 1][j - 1];
			for (int s = k - 1; s >= j; --s) {
				r = bad[s].second;
				if (dp[s - 1][j - 1] == -1) continue;
				if (l >= r) break;
				if (dp[s-1][j-1] + r - l > best)
					best = dp[s-1][j-1] + r - l;
			}
			dp[k][j] = best;
		}
	}
	
	// Turn good into a partial sum array
	sort(good.rbegin(), good.rend());
	for (int i = 1; i < good.size(); ++i)
		good[i] += good[i - 1];
	
	// Decide how many groups to give to the good intervals.
	ll ans = dp[bad.size() - 1][p - 1];
	for (int i = 0; i < good.size(); ++i) {
		if (p - i - 2 < 0) break;
		if (dp[bad.size() - 1][p - i - 2] == -1) continue;
		if (dp[bad.size() - 1][p - i - 2] + good[i] > ans)
			ans = dp[bad.size()-1][p-i-2] + good[i];
	}
	
	cout << ans << endl;
	
	return 0;
}
