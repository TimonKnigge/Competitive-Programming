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
#include <cstdio>

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
	
	int f;
	scanf("%d", &f);
	
	bool possible = true;
	while (f-- && possible) {
		int t, n;
		scanf("%d %d", &t, &n);
	
		vi dis(n, 0);
		for (int i = 0; i < n; ++i) {
			int t1, t2;
			scanf("%d %d", &t1, &t2);
			dis[i] = t2 - t1;
		}
		vb pos[2];
		pos[0].assign(t + 1, true);
		int c = 0;
		for (int i = 0; i < n; ++i) {
			pos[1 - c].assign(t + 1, false);
			for (int j = 0; j <= t; ++j) {
				if (!pos[c][j]) continue;
				if (j - dis[i] >= 0)
					pos[1 - c][j - dis[i]] = true;
				if (j + dis[i] <= t)
					pos[1 - c][j + dis[i]] = true;
			}
			c = 1 - c;
		}
		bool ans = false;
		for (int i = 0; i <= t; ++i)
			ans = ans || pos[c][i];
		possible = possible && ans;
	}
	printf(possible ? "possible\n" : "impossible\n");
	fflush(stdin);
	
	return 0;
}
