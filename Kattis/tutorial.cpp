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

void outp(bool ac) {
	if (ac) cout << "AC\n";
	else cout << "TLE\n";
}

int main() {
	ll m, n;
	int t;
	cin >> m >> n >> t;
	
	switch (t) {
		case 1:
		{
			ll prod = 1;
			for (ll j = 2; j <= n && prod <= m; ++j)
				prod *= j;
			outp(prod <= m);
			break;
		}
		case 2:
		{
			if (n > 30) {
				outp(false);
			} else {
				ll m2 = 1LL << n;
				outp(m2 <= m);
			}
			break;
		}
		case 3:
		case 4:
		case 5:
		case 7:
		{
			ll prod = 1;
			int e = (t == 3 ? 4 : (t == 4 ? 3 : (t == 5 ? 2 : 1)));
			for (int i = 0; i < e && prod <= m; ++i)
				prod *= n;
			outp(prod <= m);
			break;
		}
		default:
		{
			long double nlogn = n * log2((long double)n);
			outp(nlogn <= m);
			break;
		}
	}
	
	cout << flush;
	
	return 0;
}
