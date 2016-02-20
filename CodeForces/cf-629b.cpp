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
	
	vvi count(2, vi(366, 0LL));
	
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		char c;
		int l, r;
		cin >> c >> l >> r;
		int id = (c == 'M' ? 0 : 1);
		while (l <= r) {
			count[id][l - 1]++;
			l++;
		}
	}
	
	ll ans = 0;
	for (int i = 0; i < 366; ++i) {
		ans = max(ans, min(count[0][i], count[1][i]));
	}
	cout << ans*2 << endl;
	
	return 0;
}
