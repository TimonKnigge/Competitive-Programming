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
const ll LLINF = 9000000000000000000LL;

ll ds(ll x, ll y) { return x * x + y * y; }

int main() {
	
	int n;
	ll x1, y1, x2, y2;
	cin >> n >> x1 >> y1 >> x2 >> y2;
	
	vector<ll> x(n, 0LL), y(n, 0LL);
	for (int i = 0; i < n; ++i) {
		cin >> x[i] >> y[i];
	}
	
	ll opt = LLINF;
	for (int i = 0; i < n; ++i) {
		ll r1v = ds(x1 - x[i], y1 - y[i]);
		ll r2v = 0LL;
		for (int j = 0; j < n; ++j) {
			if (r1v >= ds(x1 - x[j], y1 - y[j])) continue;
			else r2v = max(r2v, ds(x2 - x[j], y2 - y[j]));
		}
		opt = min(opt, r1v + r2v);
	}
	
	ll rmax = 0;
	for (int i = 0; i < n; ++i)
		rmax = max(rmax, ds(x2 - x[i], y2 - y[i]));
	if (rmax < opt) opt = rmax;
	
	cout << opt << endl;
	
	return 0;
}
