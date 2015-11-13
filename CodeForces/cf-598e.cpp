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
const ll LLINF = 9000000000000000000;

int main() {
	
	int t;
	scanf("%d", &t);
	
	// width height size
	int dp[32][32][52];
	for (int i = 0; i < 32; ++i)
		for (int j = 0; j < 32; ++j)
			for (int p = 0; p < 52; ++p)
				dp[i][j][p] = 0;
	
	for (int w = 1; w <= 30; ++w) {
		for (int h = 1; h <= 30; ++h) {
			for (int p = 1; p <= min(w * h, 50); ++p) {
				if (w * h == p) {
					dp[w][h][p] = 0;
					continue;
				}
				int best = INF;
				// cut w
				int ccost = h * h;
				for (int lp = 1; lp < w; ++lp) {
					for (int s = 0; s <= p; ++s) {
						if (s > lp * h || p - s > (w - lp) * h)
							continue;
						if (best > dp[lp][h][s] + dp[w - lp][h][p - s] + ccost)
							best = dp[lp][h][s] + dp[w - lp][h][p - s] + ccost;
					}
				}
				// cut h
				ccost = w * w;
				for (int up = 1; up < h; ++up) {
					for (int s = 0; s <= p; ++s) {
						if (s > w * up || p - s > (h - up) * w)
							continue;
						if (best > dp[w][up][s] + dp[w][h - up][p - s] + ccost)
							best = dp[w][up][s] + dp[w][h - up][p - s] + ccost;
					}
				}
				dp[w][h][p] = best;
//				cerr<<w<<' '<<h<<' '<<p<<' '<<dp[w][h][p]<<endl;
			}
		}
	}
	
	while (t--) {
		int n, m, k;
		scanf("%d %d %d", &n, &m, &k);
		cout << dp[n][m][k] << '\n';
	}
	cout << flush;
	
	return 0;
}
