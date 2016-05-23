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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	ll px[2], py[2], tx, ty;
	cin >> px[0] >> py[0] >> px[1] >> py[1] >> tx >> ty;
	
	int n;
	cin >> n;
	
	vi x(n, 0LL), y(n, 0LL);
	vector<ld> dist(n, 0.0);
	ld sumdist = 0.0;
	for (int i = 0; i < n; ++i) {
		cin >> x[i] >> y[i];
		sumdist += 2.0 * (dist[i] = hypot(x[i] - tx, y[i] - ty));
	}
	
	ld bestdiff[2][2];
	int id[2][2];
	for (int a = 0; a < 2; ++a) {
		bestdiff[a][0] = bestdiff[a][1] = 0.0;
		id[a][0] = id[a][1] = -1;
		for (int i = 0; i < n; ++i) {
			ld change = dist[i] - hypot(x[i] - px[a], y[i] - py[a]);
			if (change > bestdiff[a][0] || id[a][0] == -1) {
				bestdiff[a][1] = bestdiff[a][0];
				id[a][1] = id[a][0];
				bestdiff[a][0] = change;
				id[a][0] = i;
			} else if (change > bestdiff[a][1] || id[a][1] == -1) {
				bestdiff[a][1] = change;
				id[a][1] = i;
			}
		}
	}
	
	ld best_sub
		= max(	bestdiff[0][0] + (id[0][0] == id[1][0]
			? bestdiff[1][1] : bestdiff[1][0]),
			bestdiff[1][0] + (id[0][0] == id[1][0]
			? bestdiff[0][1] : bestdiff[0][0]));
	
	best_sub = max(best_sub, max(bestdiff[0][0], bestdiff[1][0]));
	
	printf("%.7lf\n", double(sumdist - best_sub));
	
	return 0;
}
