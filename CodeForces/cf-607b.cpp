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

vi C;
vvi dp;
int N;

int calc(int l, int r) {
	if (l < 0 || r >= N || l > r)
		return 0;
	if (dp[l][r] < INF)
		return dp[l][r];
	
	if (l == r)
		return dp[l][r] = 1;
	for (int s = l; s <= r; ++s) {
		int L = (l < s && C[l] == C[s]
			? (l + 1 == s ? 1 : calc(l + 1, s - 1))
			: 1 + calc(l + 1, s));
		int R = calc(s + 1, r);
		if (L + R < dp[l][r])
			dp[l][r] = L + R;
	}
	return dp[l][r];
}

int main() {
	
	scanf("%d", &N);
	C.assign(N, -1);
	
	for (int i = 0; i < N; ++i)
		scanf("%d", &C[i]);
	
	dp.assign(N, vi(N, INF));
	cout << calc(0, N - 1) << endl;
	
	return 0;
}
