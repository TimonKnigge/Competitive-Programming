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
const ll LLINF = 9000000000000000000LL;

int main() {
	int N;
	scanf("%d", &N);
	vi P(N, 0), P2(N, 0);
	for (int i = 0; i < N; ++i) { scanf("%d", &P[i]); P[i]--; }
	for (int i = 0; i < N; ++i) {
		int x;
		scanf("%d", &x);
		x--;
		P2[x] = i;
	}
	for (int i = 0; i < N; ++i) P[i] = P2[P[i]];
	
	// Fix all cycles
	vii ans;
	ll cost = 0LL;
	for (int i = 0; i < N; ++i) {
		if (P[i] == i) continue;
		while (P[i] != i) {
			// Find the cheapest benificial swap in the cycle
			int j = i, bestcost = INF, bestj = -1;
			if ((j > P[j] && P[P[j]] > P[j]) ||
			    (j < P[j] && P[P[j]] < P[j])) {
				bestj = j;
				bestcost = abs(j - P[j]) + abs(j - P[P[j]])
					- abs(P[j] - P[P[j]]);
			}
			j = P[j];
			while (j != i) {
				if ((j > P[j] && P[P[j]] > P[j]) ||
				    (j < P[j] && P[P[j]] < P[j])) {
					if (abs(j - P[j]) - abs(P[j] - P[P[j]]) + abs(j - P[P[j]]) <= bestcost) {
						bestj = j;
						bestcost = abs(j - P[j]) - abs(P[j] - P[P[j]]) + abs(j - P[P[j]]);
					}
				}
				j = P[j];
			}
			j = bestj;
			cost += abs(j - P[j]);
			ans.push_back({j, P[j]});
			int Pj = P[j];
			P[j] = P[Pj];
			P[Pj] = Pj;
//			cerr << P[0] << ' ' << P[1] << ' ' << P[2] << ' ' << P[3] << endl;
		}
	}
	
	printf("%I64d\n", cost);
	printf("%d\n", int(ans.size()));
	for (int i = 0; i < ans.size(); ++i)
		printf("%d %d\n", 1 + ans[i].first, 1 + ans[i].second);
	
	return 0;
}
