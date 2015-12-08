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
	
	int n, m;
	scanf("%d %d", &n, &m);
	
	
	int lx, lh;
	scanf("%d %d", &lx, &lh);
	int best = lh + (lx - 1);
	bool consistent = true;
	
	for (int j = 1; j < m; ++j) {
		int x, h;
		scanf("%d %d", &x, &h);
		
		if (x - lx < abs(h - lh)) consistent = false;
		else {
			int inb = x - lx - 1;
			inb -= max(0, abs(h - lh));
			if (max(h, lh) + (inb + 1) / 2 > best)
				best = max(h, lh) + (inb + 1) / 2;
		}
		lx = x;
		lh = h;
	}
	
	if (best < lh + n - lx)
		best = lh + n - lx;
	
	if (!consistent) cout << "IMPOSSIBLE" << endl;
	else cout << best << endl;
	
	return 0;
}
