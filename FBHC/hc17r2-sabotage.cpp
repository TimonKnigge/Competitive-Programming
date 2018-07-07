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

void answer(int t, int ans) {
	cout << "Case #" << t << ": " << (ans == INF ? -1 : ans) << '\n';
}

int  solve(int N, int M, int K) {
	if (K >= M) return INF;
	if (K + K + 3LL > N)
		return INF;
	ll ans = (M + K - 1LL) / K;
	if (M >= K + K + 1LL)
		ans = min(ans, 2LL + (K + 2LL + K - 1LL) / K);
	return ans;
}

void solve(int t) {
	int N, M, K;
	cin >> N >> M >> K;
	answer(t, min(solve(N, M, K), solve(M, N, K)));
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int T;
	cin >> T;
	for (int t = 1; t <= T; ++t) solve(t);
	
	return 0;
}
