#include <iostream> 
#include <iomanip>
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
using ld = double;
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

ld dp[2000][2000][4];

int main() {
	
	ll n, h;
	ld p;
	cin >> n >> h >> p;
	
	vector<ll> x;
	for (int i = 0; i < n; ++i) {
		int v;
		cin >> v;
		x.push_back(v);
	}
	sort(x.begin(), x.end());
	
	// Mask: &1 : left fell inward
	// Mask: &2 : right fell inward
	
	for (int j = 0; j < 2000; ++j)
		for (int k = 0; k < 2000; ++k)
			for (int tt = 0;tt<4;++tt) dp[j][k][tt] = 0.0;
	
	vi leftof(n, 0);
	vi rightof(n, n - 1);
	for (int i = 1; i < n; ++i) {
		if (x[i - 1] > x[i] - h) {
			leftof[i] = leftof[i - 1];
		} else leftof[i] = i;
	}
	for (int i = n - 2; i >= 0; --i) {
		if (x[i + 1] < x[i] + h) {
			rightof[i] = rightof[i + 1];
		} else rightof[i] = i;
	}
	
	dp[0][n - 1][0] = 1.0;
	ld ans = 0.0;
	for (int l = 0; l < n; ++l) {
		for (int r = n - 1; r >= 0; --r) {
			if (r < l) continue;
			for (int m = 0; m < 4; ++m) {
				int lp = l > 0 ? x[l - 1] : -INF;
				if ((l > 0) && ((m&1) > 0))
					lp = x[l - 1] + h;
				int rp = r < n - 1 ? x[r+1] : INF;
				if ((r < n-1) && ((m&2) > 0))
					rp = x[r + 1] - h;
				
				/* FALLING OUTWARD */
				ld prob;
				// select left most	0.5
				// prob fall left	p
				int ar = h;
				if (lp >= x[l] - h) ar = x[l] - lp;
				prob = ld(0.5) * p;
				if (l + 1 <= r)
					dp[l + 1][r][m&2] += dp[l][r][m]*prob;
				ans += dp[l][r][m] * ar * prob;
				
				ar = h;
				if (rp <= x[r] + h) ar = rp - x[r];
				prob = ld(0.5) * (ld(1.0) - p);
				if (r - 1 >= l)
					dp[l][r-1][m&1] += dp[l][r][m]*prob;
				ans += dp[l][r][m] * ar * prob;
				
				/* FALLING INWARD */
				// L
				int lst = min(r, rightof[l]);
				// start at l, end at lst
				ar = h + x[lst] - x[l];
				if (rp <= x[lst] + h)
					ar -= x[lst] + h - rp;
				prob = ld(0.5) * (ld(1.0) - p);
				if (lst + 1 <= r)
					dp[lst+1][r][1|m] += dp[l][r][m]*prob;
				ans += prob * ar * dp[l][r][m];
		
				// R
				lst = max(l, leftof[r]);
				ar = h + x[r] - x[lst];
				if (lp >= x[lst] - h)
					ar -= lp - x[lst] + h;
				prob = ld(0.5) * p;
				if (lst - 1 >= l)
					dp[l][lst - 1][2|m] += dp[l][r][m]*prob;
				ans += dp[l][r][m] * prob  * ar;
			}
		}
	}
	
	printf("%.7lf\n", double(ans));
	
	return 0;
}
