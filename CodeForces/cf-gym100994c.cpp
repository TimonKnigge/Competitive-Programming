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
	
	int n, m;
	scanf("%d %d", &n, &m);
	
	vi xb(n, 0LL), yb(m, 0LL);
	ll s = 0LL;
	for (int r = 0; r < n; ++r)
		for (int c = 0, v; c < m; ++c)
			scanf("%d", &v),
			xb[r] += v,
			yb[c] += v,
			s += ll(v);
	++s;
	
	ll pref = xb[0];
	int x = 0, y = 0;
	while (x + 1 < n && pref < s/2)
		pref += xb[x + 1],
		++x;
	pref = yb[0];
	while (y + 1< m && pref < s/2)
		pref += yb[y + 1],
		++y;
	
	ll work = 2LL * (s - 1);
	for (int i = 0; i < n; ++i)
		work += 2LL * xb[i] * ll(abs(x - i));
	for (int i = 0; i < m; ++i)
		work += 2LL * yb[i] * ll(abs(y - i));
	
	cout << x+1 << ' ' << y+1 << ' ' << work << endl;
	
	return 0;
}
