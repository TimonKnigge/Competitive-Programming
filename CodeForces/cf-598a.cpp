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
	
	int t;	
	cin >> t;
	while (t--) {
		ll n;
		cin >> n;
		ll ans = (n * (n + 1)) >> 1;
		
		ll po2 = 1;
		while (po2 <= n) po2 <<= 1;
		ans -= 2 * (po2 - 1);
		cout << ans << endl;
	}
	
	return 0;
}
