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

void solve(int t) {
	int N, M;
	cin >> N >> M;
	
	vi dp[2];
	dp[0].assign(N+1, LLINF);
	dp[1].assign(N+1, LLINF);
	dp[0][0] = 0LL;
	
	for (int i = 0; i < N; ++i) {
		vi pies(M, 0LL);
		for (ll &v : pies) cin >> v;
		sort(pies.begin(), pies.end());
		pies.push_back(0);
		
		int c = (i&1), oc = (1^i&1);
		ll cost = 0LL;
		for (int j = 0; j <= M; ++j) {
			cost += j * j;
			for (int d = i; d + j <= N; ++d) {
				if (dp[c][d] < LLINF)
					dp[oc][d+j] = min(dp[oc][d+j],
							dp[c][d] + cost);
			}
			cost -= j * j;
			cost += pies[j];
		}
	}
	
	cout << "Case #" << t << ": " << dp[N&1][N] << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int T;
	cin >> T;
	for (int t = 1; t <= T; ++t) solve(t);
	
	return 0;
}
