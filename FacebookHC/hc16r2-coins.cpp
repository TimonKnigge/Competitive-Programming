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
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int T;
	cin >> T;
	for (int t = 1; t <= T; ++t) {
		int N, K;
		cin >> N >> K;
		ld p;
		cin >> p;
		
		vector<vector<ld> > P(N + 1, vector<ld>(N + 1, 0.0));
		P[0][0] = 1.0;
		for (int w = 1; w <= N; ++w) {
			P[0][w] = (1 - p) * P[0][w - 1];
			for (int g = 1; g <= w; ++g) {
				P[g][w] = p*P[g-1][w-1] + (1-p)*P[g][w-1];
			}
		}
		
		vector<ld> Pk(N + 1, 0.0);
		for (int w = 1; w <= N; ++w) {
			for (int g = K; g <= w; ++g)
				Pk[w] += P[g][w];
		}
		
		vector<ld> opt(N + 1, 0.0);
		for (int w = 1; w <= N; ++w) {
			for (int u = 0; u < w; ++u)
				opt[w] = max(Pk[w - u] + opt[u], opt[w]);
		}
		
		printf("Case #%d: %.7lf\n", t, double(opt[N]));
	}
	
	return 0;
}
