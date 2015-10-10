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

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

int main() {
	freopen("knockout.in", "r", stdin);
	freopen("knockout.out", "w", stdout);
	
	int n, m;
	cin >> n >> m;
	vector<ll> a(n, 0), b(n, 0);
	for (int i = 0; i < n; ++i) cin >> a[i] >> b[i];
	
	for (int q = 0; q < m; ++q) {
		ll x, y, t;
		cin >> x >> y >> t;
		
		int count = 0;
		for (int i = 0; i < n; ++i) {
			ll diff = b[i] - a[i];
			ll myt = t % (2 * abs(diff));
			ll mypos = 0LL;
			if (myt < diff) mypos = a[i] + (diff > 0 ? myt : -myt);
			else mypos = b[i] - (diff > 0 ? myt - diff : diff - myt);
			if (x <= mypos && mypos <= y) count++;
		}
		cout << count << '\n';
	}
	cout << flush;	

	return 0;
}
