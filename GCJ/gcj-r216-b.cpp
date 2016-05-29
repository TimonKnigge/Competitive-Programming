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


ld best(vector<ld> &P, int N, int K, int s) {
	vector<ld> n2(K, 0.0);
	for (int i = 0; i < s; ++i) n2[i] = P[i];
	for (int i = s; i < K; ++i) n2[i] = P[N-K+i];
	
	vector<vector<ld>> prob(K, vector<ld>(K/2+1, 0.0));
	prob[0][0] = 1.0-n2[0];
	prob[0][1] = n2[0];
	for (int i = 1; i < K; ++i) {
		ld yes = n2[i];
		ld no = 1.0 - n2[i];
		for (int n = 0; n <= K/2; ++n) {
			prob[i][n] += no * prob[i - 1][n];
			if (n > 0) prob[i][n] += yes * prob[i-1][n-1];
		}
	}
	return prob[K-1][K/2];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int T;
	cin >> T;
	for (int t = 1; t <= T; ++t) {
		int N, K;
		cin >> N >> K >> ws;
		
		vector<ld> P(N, 0.0);
		for (int i = 0; i < N; ++i) {
			cin >> P[i];
		}
		sort(P.begin(), P.end());
		ld ans = best(P, N, K, 0);
		for (int i = 1; i <= K; ++i)
			ans = max(ans, best(P, N, K, i));
		printf("Case #%d: %.7lf\n", t, double(ans));
	}
	
	return 0;
}
