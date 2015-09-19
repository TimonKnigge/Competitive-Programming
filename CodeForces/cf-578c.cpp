#include <iostream> 
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
using ld = long double;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

int main() {
	int n;
	scanf("%d", &n);
	
	vector<ll> a(n, 0);
	ll MX = 0;
	for (int i = 0, ai; i < n; ++i) {
		scanf("%d", &ai);
		if ((ai < 0 ? -ai : ai) > MX) MX = (ai < 0 ? -ai : ai);
		a[i] = ll(ai);
	}
	
	ld l = -10002, r = 10002, minsum = 0.0, maxsum = 0.0;
	while (r - l > 1e-11) {
		ld m = (l + r) / 2.0;
		maxsum = a[0] - m; minsum = a[0] - m; 
		ld curMax = a[0] - m, curMin = a[0] - m;
		
		for (int i = 1; i < n; ++i) {
			curMax += a[i] - m;
			if (curMax < a[i] - m) curMax = a[i] - m;
			if (curMax > maxsum) maxsum = curMax;
			curMin += a[i] - m;
			if (curMin > a[i] - m) curMin = a[i] - m;
			if (curMin < minsum) minsum = curMin;
		}

		if (-minsum > maxsum) r = m;
		else l = m;
	}
	
	printf("%.7lf\n", double((abs(maxsum) + abs(minsum)) / 2.0));
	
	return 0;
}
