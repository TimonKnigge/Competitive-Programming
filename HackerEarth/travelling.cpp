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

vvi smpf;
void smf(int M) {
	vb vis(M+1, false);
	smpf.assign(M+1, vi());
	smpf[1].push_back(1);
	
	for (int i = 2; i <= M; ++i) {
		if (vis[i]) continue;
		for (int j = i; j <= M; j += i) {
			if (vis[j]) continue;
			vis[j] = true;
			smpf[i].push_back(j);
		}
	}
}

constexpr ll MOD = 1000000003;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N, M;
	cin >> N >> M;
	
	ll S0, P, Q, R;
	ll W0, X, Y, Z;
	cin >> S0 >> P >> Q >> R;
	cin >> W0 >> X >> Y >> Z;
	
	smf(M);
	
	vi exist;
	for (int i = 1; i <= M; ++i)
		if (smpf[i].size() > 0)
			exist.push_back(i);
	
	vi A(M+1, S0), B(M+1, W0);
	for (int i = 1; i <= M; ++i) {
		S0 = (P*(S0*S0%MOD)%MOD + ((Q*S0 + R)%MOD)) % MOD;
		W0 = (X*(W0*W0%MOD)%MOD + ((Y*W0 + Z)%MOD)) % MOD;
		A[i] = S0;
		B[i] = W0;
	}
	
	vvi dp(2, vi(M+1, 0LL));
	for (int a = 1; a < N; ++a) {
		int c = a%2;
		for (int i = 0; i <= M; ++i) dp[c][i] = LLINF;
		
		for (int i : exist) {
			
			ll bn = -1LL;
			ll b1 = LLINF, b2 = LLINF;
			for (int j : smpf[i]) {
				if (b1 > B[j] + dp[1-c][j]) { 
					b2 = b1;
					bn = j;
					b1 = B[j] + dp[1-c][j];
				}
				else if (b2 > B[j] + dp[1-c][j]) { 
					b2 = B[j] + dp[1-c][j];
				}
			}
			
			for (int j : smpf[i]) {
				dp[c][j] = dp[1-c][j] + A[j];
				if (bn != j)
					dp[c][j] = min(dp[c][j], b1);
				else if (b2 < LLINF)
					dp[c][j] = min(dp[c][j], b2);
				dp[c][1] = min(dp[c][1],
					dp[1-c][j] + (j == 1 ? A[j] : B[j]));
			}
		}
		
		for (int i = 1; i <= M; ++i) {
			S0 = (P*(S0*S0%MOD)%MOD + ((Q*S0 + R)%MOD)) % MOD;
			W0 = (X*(W0*W0%MOD)%MOD + ((Y*W0 + Z)%MOD)) % MOD;
			A[i] = S0;
			B[i] = W0;
		}
	}
	
	ll mn = LLINF;
	for (int i : exist)
		for (int j : smpf[i])
			mn = min(mn, dp[(N+1)%2][j]);
	
	cout << mn << endl;
	
	return 0;
}
