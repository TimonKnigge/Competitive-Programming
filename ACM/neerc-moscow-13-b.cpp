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
	
	int N, a, b;
	cin >> N >> a >> b;
	
	// ritten over / dagen over
	int dp[21][21][21][21];
	for (int i1 = 0; i1 < 21; ++i1)
	for (int i2 = 0; i2 < 21; ++i2)
	for (int i3 = 0; i3 < 21; ++i3)
	for (int i4 = 0; i4 < 21; ++i4)
		dp[i1][i2][i3][i4] = (i1 > 0) + (i3 > 0);
	
	vb l1(N, false), l2(N, false);
	for (int i = 0; i < N; ++i) {
		int x;
		cin >> x;
		l1[i] = x > 0;
	}
	for (int i = 0; i < N; ++i) {
		int x;
		cin >> x;
		l2[i] = x > 0;
		if (l2[i] && !l1[i]) swap(l2[i], l1[i]);
	}
	
	for (int d = 0; d < N; ++d) {
		if (!l1[i] && !l2[i]) {
			for (int r1o = 0; r1o <= A; ++r1o)
			for (int r2o = 0; r2o <= A; ++r2o)
			for (int d1o = 0; d1o <= B; ++d1o)
			for (int d2o = 0; d2o <= B; ++ d2o) {
				if (d2o == B || d1o == B)
				dp[r1o][d1o][r2o][d2o] = INF;
			}
		}
		if (l1[i] && l2[i]) {
			for (int r1o = 1; r1o <= A; ++r1o)
			for (int d1o = 1; d1o
		}
	}

	return 0;
}
