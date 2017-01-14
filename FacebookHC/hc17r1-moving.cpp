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
	// towns, roads, families
	int N, M, K;
	cin >> N >> M >> K;
	
	vvi d(N, vi(N, LLINF));
	for (int i = 0; i < N; ++i) d[i][i] = 0LL;
	while (M--) {
		ll a, b, g;
		cin >> a >> b >> g;
		--a; --b;
		d[a][b] = min(d[a][b], g);
		d[b][a] = min(d[b][a], g);
	}
	
	for (int b = 0; b < N; ++b)
		for (int a = 0; a < N; ++a)
			for (int c = 0; c < N; ++c)
				if(d[a][b] < LLINF && d[b][c] < LLINF)
					d[a][c] = min(d[a][c],
						d[a][b] + d[b][c]);
	
	bool impossible = false;
	vii de(K, {-1, -1});
	for (ii &pr : de) {
		cin >> pr.first >> pr.second;
		--pr.first;
		--pr.second;
		impossible = impossible || d[0][pr.first] == LLINF;
		impossible = impossible || d[0][pr.second] == LLINF;
	}
	
	if (impossible) {
		cout << "Case #" << t << ": -1\n";
		return;
	}
	
	vii dp(K, {LLINF, LLINF});
	dp[0].first  = d[0][de[0].first] + d[de[0].first][de[0].second];
	if (K > 1)
		dp[0].second = d[0][de[0].first] + d[de[0].first][de[1].first];
	for (int i = 1; i < K; ++i) {
		dp[i].first = min(
			dp[i-1].first  + d[de[i-1].second][de[i].first]
				+ d[de[i].first][de[i].second],
			dp[i-1].second + d[de[i].first][de[i-1].second]
				+ d[de[i-1].second][de[i].second]);
		if (i + 1 == K) continue;
		dp[i].second = min(
			dp[i-1].first  + d[de[i-1].second][de[i].first]
				+ d[de[i].first][de[i+1].first],
			dp[i-1].second + d[de[i].first][de[i-1].second]
				+ d[de[i-1].second][de[i+1].first]);
	}
	cout << "Case #" << t << ": " << dp.back().first << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int T;
	cin >> T;
	for (int t = 1; t <= T; ++t) solve(t);
	
	return 0;
}
