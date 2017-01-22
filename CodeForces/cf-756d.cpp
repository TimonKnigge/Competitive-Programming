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

constexpr ll MOD = 1e9+7;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N;
	string S;
	cin >> N >> S;
	
	vi prev(26, -1LL);
	vector<vector<int>> dp(N, vector<int>(N, 0));
	for (int i = 0; i < N; ++i)
		dp[0][i] = i+1;
	prev[S[0] - 'a'] = 0;
	
	for (int i = 1; i < N; ++i) {
		int c = int(S[i] - 'a');
		for (int j = 0; j < N; ++j) {
			// Characters [0..i] positions [0..j].
			ll v = 1LL + ll(j > 0 ? dp[i-1][j-1] : 0);
			if (prev[c] >= 0) {
				v--;
				v -= (j > 0 ? dp[prev[c]][j-1] : 0);
			}
			v += dp[i-1][j];
			if (j > 0)
				v += dp[i][j-1] - dp[i-1][j-1];
			dp[i][j] = int((v%MOD+MOD)%MOD);
		}
		prev[c] = i;
	}
	
	cout << ((MOD + dp[N-1][N-1] - (N > 1 ? dp[N-1][N-2] : 0))%MOD) << endl;
	
	return 0;
}
