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
	int N, P, X, Y;
	scanf("%d %d %d %d", &N, &P, &X, &Y);
	X--;
	Y--;
	
	vector<vector<pair<int, ll> > > e(N, vector<pair<int, ll> >());
	while (P--) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		a--;
		b--;
		e[a].push_back({b, ll(c)});
		e[b].push_back({a, ll(c)});
	}
	
	int M;
	scanf("%d", &M);
	vb SWERC(N, false);
	for (int i = 0; i < M; ++i) {
		int x;
		scanf("%d", &x);
		x--;
		SWERC[x] = true;
	}
	
	// [Length][eind]
	vector<vector<ll> > dp(N + 1, vector<ll>(N, -1));
	vector<vb> is_swerc(N + 1, vector<bool>(N, false));
	is_swerc[0][X] = true;
	dp[0][X] = 0;
	
	for (int l = 0; l < N; ++l) {
		for (int u = 0; u < N; ++u) {
			if (dp[l][u] == -1) continue;
			// Branch from u
			for (pair<int, ll> vw : e[u]) {
				int v = vw.first;
				ll w = vw.second;
				
				if (dp[l + 1][v] > dp[l][u] + w || dp[l + 1][v] == -1) {
					dp[l + 1][v] = dp[l][u] + w;
					is_swerc[l+1][v] = is_swerc[l][u] && SWERC[v];
				} else if (dp[l + 1][v] == dp[l][u] + w) {
					is_swerc[l+1][v] = is_swerc[l+1][v]
							&& is_swerc[l][u] && SWERC[v];
				}
			}
		}
	}
	
	// If the edge-wise shortest possible path from X to Y is through SWERC, the
	// answer is infty
	bool infty = false;
	for (int l = 1; l <= N; ++l) {
		if (dp[l][Y] == -1) continue;
		if (is_swerc[l][Y]) infty = true;
		break;
	}
	
	if (infty) {
		cout << "Infinity" << endl;
		return 0;
	}
	
	// For each SWERC path
	ll ans = 0LL;
	for (int l = 1; l <= N; ++l) {
		if (!is_swerc[l][Y]) continue;
		if (dp[l][Y] == -1) continue;
		
		// Find the smallest time for which we beat all other paths:
		// Shorter paths give an upperbound
		// Longer paths a lower bound
		ll lb = 0LL, ub = LLINF;
		
		// lb is the maximum of all lowerbounds, ub the minimum
		// of all upperbounds
		
		for (int m = 1; m < l; ++m) {
			if (is_swerc[m][Y]) continue;
			if (dp[m][Y] == -1) continue;
			ll den = dp[m][Y] - dp[l][Y];
			ll num = l - m;
			// ub should be <= den / num
			if (den % num == 0) den--;
			ub = min(ub, den / num);
		}
		for (int m = l + 1; m <= N; ++m) {
			if (is_swerc[m][Y]) continue;
			if (dp[m][Y] == -1) continue;
			ll den = dp[l][Y] - dp[m][Y];
			ll num = m - l;
			// lb should be > den / num
			lb = max(lb, den / num);
		}
//		cerr << "Length "<< l << " (" << lb << ", " << ub << "]" << endl;
		if (lb < ub)
			ans = max(ans, ub);
	}
	
	if (ans == 0) cout << "Impossible" << endl;
	else cout << ans << endl;
	
	return 0;
}
