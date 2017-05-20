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
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, k;
	cin >> n >> k;
	
	int m;
	cin >> m;
	vi u(m, 0), v(m, 0), c(m, 0);
	for (int i = 0; i < m; ++i) cin >> u[i] >> v[i] >> c[i];
	
	for (int i = 0; i < m; ++i) {
		--u[i]; --v[i];
		swap(u[i], v[i]);
	}
	
	vector<vvi> dp(k, vvi(n, vi(n, LLINF)));
	for (int i = 0; i < n; ++i)
		dp[0][i][i] = 0;
	for (int j = 1; j < k; ++j) {
		for (int i = 0; i < m; ++i) {
			if (u[i] == v[i]) continue;
			// ui -> vi
			if (u[i] < v[i]) {
				for (int p = u[i]; p >= 0; --p) {
					if (dp[j-1][p][u[i]] == LLINF) continue;
					dp[j][p][v[i]] = min(dp[j][p][v[i]],
						dp[j-1][p][u[i]] + c[i]);
				}
				for (int p = u[i]; p < v[i]; ++p) {
					if (dp[j-1][p][u[i]] == LLINF) continue;
					dp[j][u[i]][v[i]] = min(dp[j][u[i]][v[i]],
						dp[j-1][p][u[i]] + c[i]);
				}
			} else if (u[i] > v[i]) {
				for (int p = u[i]; p < n; ++p) {
					if (dp[j-1][p][u[i]] == LLINF) continue;
					dp[j][p][v[i]] = min(dp[j][p][v[i]],
						dp[j-1][p][u[i]] + c[i]);
				}
				for (int p = u[i]; p > v[i]; --p) {
					if (dp[j-1][p][u[i]] == LLINF) continue;
					dp[j][u[i]][v[i]] = min(dp[j][u[i]][v[i]],
						dp[j-1][p][u[i]] + c[i]);
				}
			}
		}
	}
	
	ll best = LLINF;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			best = min(best, dp[k - 1][i][j]);
	if (best == LLINF) best = -1;
	cout << best << endl;
	
	return 0;
}
