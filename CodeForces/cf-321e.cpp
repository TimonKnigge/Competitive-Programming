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

int u[4001][4001];
int dp[2][4001];

inline int sum(int l, int r) {
	--l;
	return u[r][r] - u[l][r] - u[r][l] + u[l][l];
}

void divide_and_conquer(int l, int r, int lo, int hi, int *dp, int *old_dp) {
	
	int m = (l + r) / 2, opt = min(m, hi);
	dp[m] = old_dp[opt - 1] + sum(opt, m);
	
	for (int i = opt; i >= lo; --i)
		if (old_dp[i - 1] + sum(i, m) < dp[m])
			dp[m] = old_dp[i - 1] + sum(i, m),
			opt = i;
	
	if (l < m) divide_and_conquer(l, m - 1, lo, opt, dp, old_dp);
	if (m < r) divide_and_conquer(m + 1, r, opt, hi, dp, old_dp);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, k;
	cin >> n >> k >> ws;
	
	u[0][0] = 0;
	for (int i = 1; i <= n; ++i)
		u[0][i] = u[i][0] = 0;
	
	string buffer;
	for (int i = 1; i <= n; ++i) {
		getline(cin, buffer);
		for (int j = 1; j <= n; ++j) {
			u[i][j] = buffer[(j - 1) << 1]-'0';
			u[i][j] += u[i - 1][j] + u[i][j - 1];
			u[i][j] -= u[i - 1][j - 1];
		}
	}
	
	dp[0][0] = 0;
	for (int i = 1; i <= n; ++i)
		dp[0][i] = sum(1, i);

	for (int c = 1, j = 2; j <= k; ++j, c = 1 - c)
		divide_and_conquer(j, n, j, n, dp[c], dp[1 - c]);
	
	printf("%d\n", dp[1&~k][n] / 2);
	
	return 0;
}
