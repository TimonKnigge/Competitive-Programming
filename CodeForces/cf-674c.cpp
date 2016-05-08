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

void divcon(vi &t, vi &p, int k, int l, int r, int lo, int hi, vector<ld> &dp, vector<ld> &old_dp, vector<ld> &st, vector<ld> &st2) {
	
	int m = (l + r) / 2;
	int fst = min(m, hi);
	ld sum = st2[m] - st2[fst - 1]
		- (p[m] - ld(fst > 0 ? p[fst - 1] : 0LL))
		* (m + 1 < t.size() ? st[t.size() - 1] - st[m] : 0.0);
	dp[m] = old_dp[fst - 1] + sum;
	int A = fst;
	for (int i = fst - 1; i >= max(k - 1, lo); --i) {
		sum += t[i] * (st[m] - st[i - 1]);
		if (dp[m] > old_dp[i - 1] + sum) {
			dp[m] = old_dp[i - 1] + sum;
			A = i;
		}
	}
//	cerr << lo << ' ' << hi << ' ' << k << endl;
//	cerr << l << ' ' << m << ' ' << r << endl;
//	cerr << "dp[" << k - 1 << "]["<< m << "] = " << dp[m] << endl;
	
	if (l < m)
		divcon(t, p, k, l, m - 1, lo, min(A, hi), dp, old_dp, st, st2);
	if (m < r)
		divcon(t, p, k, m + 1, r, max(A, lo), hi, dp, old_dp, st, st2);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	ll n, k;
	cin >> n >> k;
	vi t(n, 0LL), p(n, 0LL);
	vector<ld> reciprocal_sum(n, 0.0);
	for (int i = 0; i < n; ++i) {
		cin >> t[i];
		p[i] = t[i] + (i > 0 ? p[i - 1] : 0LL);
		reciprocal_sum[i] = 1.0 / ld(t[i])
			+ (i > 0 ? reciprocal_sum[i - 1] : 0.0);
	}
	
	vector<ld> prodsum(n, 0.0);
	for (int i = 0; i < n; ++i)
		prodsum[i] = ld(t[i]) * (reciprocal_sum[n - 1] - (i > 0 ? reciprocal_sum[i - 1] : 0.0))
			+ (i > 0  ? prodsum[i - 1] : 0.0);
	
	vector<ld> dp[2];
	dp[0].assign(n, 0.0);
	dp[1].assign(n, 0.0);
	dp[0][0] = 1.0;
	for (int i = 1; i < n; ++i) {
		dp[0][i] = dp[0][i - 1] + ld(p[i]) / ld(t[i]);
	}
	
	int c = 1;
	for (int kk = 1; kk < k; ++kk) {
		
		dp[c][kk] = kk + 1;
		
		divcon(t, p, kk + 1, kk, n - 1, kk, n - 1, dp[c], dp[1 - c], reciprocal_sum, prodsum);
		
		c = 1-c;
	}
	
	printf("%.7lf\n", double(dp[1 - c][n - 1]));
	
	return 0;
}
