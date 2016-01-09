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

ll step[12] = {-2, 0, -1, -2, 1, -2, 2, 0, 1, 2, -1, 2};
ll add[6] = {0, 0, 0, 0, 1, 0};

int main() {
	
	ll n;
	cin >> n;
	
	ll x = 0LL, y = 0LL;
	if (n > 0) {
		--n;
		x += 1LL;
		y += 2LL;
		
		ll l = 0LL, r = ll(1e9) + ll(5e8);
		while (l < r) {
			ll m = (l + r) / 2LL;
			ll calc = m * (m + 1) * 3LL + m;
			if (calc <= n)  l = m + 1;
			else		r = m;
		}
		ll v = l;
		while (v * (v + 1) * 3LL + v > n) --v;
		n -= v * (v + 1) * 3LL + v;
		x += v;
		y += 2 * v;
		++v;
		
		for (int i = 0; i < 6 && n > 0; ++i) {
			ll st = min(n, v + add[i]);
			n -= st;
			x += st * step[2 * i];
			y += st * step[2*i+1];
		}
	}
	
	cout << x << ' ' << y << endl;
	
	return 0;
}
