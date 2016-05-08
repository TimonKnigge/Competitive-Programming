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

void divide_and_conquer(
	int l, int r, int lo, int hi,
	vi &T, vi &P, vector<ld> &recip_suff, vector<ld> &prod_sum,
	vector<ld> &dp, vector<ld> &old_dp) {
	
	int m = (l + r) / 2;
	int my_hi = min(m, hi);
	int opt = my_hi;
	ld sum = prod_sum[my_hi] - prod_sum[m + 1]
		- recip_suff[m + 1]
		* ld(P[m] - P[my_hi - 1]);
	dp[m] = old_dp[my_hi - 1] + sum;
	for (int i = my_hi - 1; i >= lo; --i) {
		sum += ld(T[i]) * (recip_suff[i] - recip_suff[m + 1]);
		if (old_dp[i - 1] + sum < dp[m]) {
			dp[m] = old_dp[i - 1] + sum;
			opt = i;
		}
	}
	
	if (l < m) 
		divide_and_conquer(l, m-1, lo, opt, T, P, recip_suff, prod_sum, dp, old_dp);
	if (m < r)
		divide_and_conquer(m+1, r, opt, hi, T, P, recip_suff, prod_sum, dp, old_dp);
}

int main() {
	
	int N, K;
	scanf("%d %d", &N, &K);
	vi T(N, 0LL), P(N, 0LL);
	for (int i = 0, v; i < N; ++i) {
		scanf("%d", &v);
		T[i] = v;
		P[i] = (i > 0 ? P[i - 1] : 0LL) + T[i];
	}
	
	vector<ld> recip_suff(N + 1, 0.0), prod_sum(N + 1, 0.0);
	for (int i = N - 1; i >= 0; --i)
		recip_suff[i] = recip_suff[i + 1] + 1.0 / ld(T[i]),
		prod_sum[i] = prod_sum[i + 1] + T[i] * recip_suff[i];
	
	vector<vector<ld>> dp(2, vector<ld>(N, 0.0));
	dp[0][0] = 1.0;
	for (int i = 1; i < N; ++i)
		dp[0][i] = dp[0][i - 1] + ld(P[i]) / ld(T[i]);
	int c = 1;
	
	for (int j = 1; j < K; ++j) {
		
		divide_and_conquer(
			j, N - 1, j, N - 1,
			T, P, recip_suff, prod_sum,
			dp[c], dp[1 - c]);
		
		c = 1 - c;
	}
	
	printf("%.7lf\n", double(dp[1 - c][N - 1]));

	return 0;
}
