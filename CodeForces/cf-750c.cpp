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
	
	int n;
	cin >> n;
	
	vii cd(n, {0, 0});
	for (ii &pr : cd) cin >> pr.first >> pr.second;
	
	ll mn = -LLINF, mx = LLINF;
	ll c = 0LL;
	for (ii pr : cd) {
		if (pr.second == 1LL) {
			// x >= 1900-c
			mn = max(mn, 1900 - c);
		} else {
			// x <= 1899-c
			mx = min(mx, 1899 - c);
		}
		c += pr.first;
	}
	
	if (mn > mx) cout << "Impossible" << endl;
	else if (mx == LLINF) cout << "Infinity" << endl;
	else cout << mx+c << endl;
	
	return 0;
}
