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
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

void minf(int &l, int r) {
	if (l > r) l = r;
}

int main() {
	
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; ++t) {
		
		int N;
		scanf("%d", &N);
		vi D(N, 0);
		for (int i = 0; i < N; ++i) {
			scanf("%d", &D[i]);
		}
		
		vvi dp(4, vi(N, INF));
		for (int c = 0; c < 4; ++c)
			dp[c][0] = c;
		
		for (int i = 1; i < N; ++i) {
			for (int c = 0; c < 4; ++c) {
				// Include in same contest
				for (int cc = 0; cc < c; ++cc) {
					if (D[i] < D[i - 1] + c - cc) continue;
					if (D[i] - D[i - 1] > 10 * (c - cc))
						continue;
					minf(dp[c][i], dp[cc][i - 1] + c - cc - 1);
				}
				// Start new contest
				for (int cc = 0; cc < 4; ++cc) {
					minf(dp[c][i], dp[cc][i - 1] + (3 - cc) + c);
				}
			}
		}
		
		int ans = INF;
		for (int c = 0; c < 4; ++c)
			ans = min(ans, dp[c][N - 1] + (3 - c));
		
		printf("Case #%d: ", t);
		printf("%d\n", ans);
	}
	
	return 0;
}
