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

#define M(x) (((x)+N)%N)

int main() {
	
	constexpr ll Lmax = 1000LL;
	vi TG(Lmax, 0LL);
	vi PG(Lmax, 0LL);
	vi PnG(Lmax, 0LL);
	vi PnS(Lmax, 0LL);
	vvii dp(Lmax, vii(Lmax, {0LL, 0LL}));
	char T[Lmax], P[Lmax];
	
	int N;
	while (scanf("%d", &N) == 1) {
		if (N == 0) break;
		scanf("%s", T);
		scanf("%s", P);
		
		TG[0] = (T[0] == 'G');
		PG[0] = (P[0] == 'G');
		for (int i = 1; i < N; ++i) {
			TG[i] = TG[i - 1] + (T[i] == 'G');
			PG[i] = PG[i - 1] + (P[i] == 'G');
		}
		if (TG[N - 1] != PG[N - 1]) { cout << -1 << '\n'; continue;}
		
		PnG[N - 1] = PnS[N - 1] = N - 1;
		for (int i = N - 2; i >= 0; --i) {
			if (P[i] == 'G') {
				PnG[i] = i;
				PnS[i] = PnS[i + 1];
			} else {
				PnG[i] = PnG[i + 1];
				PnS[i] = i;
			}
		}
		
		// {max laying around, next stack}
		for (int s = 0; s < N; ++s) {
			if (T[s] == 'G')
				dp[s][s] = {PnG[0], PnG[0] + 1LL};
			else	dp[s][s] = {PnS[0], PnS[0] + 1LL};
		}
		for (int l = 0; l + 1 < N; ++l)
			for (int s = 0; s < N; ++s) {
				// spread [s, s+l] to:
				//	- [s-1, s+l]
				//	- [s, s+l+1]
				ll sl = M(s+l);
				ll nxt = dp[s][sl].second;
				// What do we have laying around?
				ll Gs = 0LL, Ss = 0LL;
				if (nxt > 0) {
					Gs = PG[nxt - 1];
					Ss = nxt - PG[nxt - 1];
					ll c = 0LL;
					if (s <= sl)
						c = TG[sl] - (s > 0 ? TG[s - 1] : 0);
					else	c = TG[sl] - TG[s - 1] + TG[N - 1];
					Gs -= c;
					Ss -= l+1-c;
				}
				if (Gs < 0LL) Gs = 0LL;
				if (Ss < 0LL) Ss = 0LL;
				dp[s][sl].first = max(Gs + Ss, dp[s][sl].first);
				ll a = M(s-1LL), b = sl;
				for (int i = 0; i < 2; ++i) {
					if (s == 0 && i == 0) dp[a][b] = {N, 0LL};
					if (s+1< N && i == 1) dp[a][b] = {N, 0LL};
					if (T[a + (b - a) * i] == 'G') {
						if (Gs > 0) { if (dp[a][b] > dp[s][sl]) dp[a][b] = dp[s][sl]; }
						else {
							ii ns = dp[s][sl];
							ns = {max(ns.first, Ss + PnG[ns.second] - ns.second), PnG[ns.second] + 1};
							if (dp[a][b] > ns) dp[a][b] = ns;
						}
					} else {
						if (Ss > 0) { if (dp[a][b] > dp[s][sl]) dp[a][b] = dp[s][sl]; }
						else {
							ii ns = dp[s][sl];
							ns = {max(ns.first, Gs + PnS[ns.second] - ns.second), PnS[ns.second] + 1};
							if (dp[a][b] > ns) dp[a][b] = ns;
						}
					}
					a = (a + 1) % N;
					b = (b + 1) % N;
				}
			}

		ll ans = LLINF;
		for (int s = 0; s < N; ++s) if (ans > dp[s][M(s+N-1)].first) ans = dp[s][M(s+N-1)].first;
		cout << ans << '\n';
	}
	
	return 0;
}
