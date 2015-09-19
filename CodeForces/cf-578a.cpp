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
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	ll _a, _b;
	cin >> _a >> _b;
	if (_a < _b) cout << -1 << endl;
	else if (_a == _b) cout << _a << endl;
	else {
		ld a = _a, b = _b, xp = 1e300, xn = 1e300;
		
		ll k = ll(a / (2 * b) + 1/2.0);
		if (k > 0) xp = ((a + b) / 2.0) / k;
		k = ll(a / (2 * b) - 1/2.0);
		if (k > 0) xn = ((a - b) / 2.0) / k;
		
		printf("%.10lf\n", double(min(xp, xn)));
	}
	
	return 0;
}
