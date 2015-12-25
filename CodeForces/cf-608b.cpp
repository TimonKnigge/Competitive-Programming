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
	
	string a, b;
	cin >> a >> b;
	int n = a.size(), m = b.size();
	
	vi z(n, 0);
	z[0] = (a[0] == '0');
	for (int i = 1; i < n; ++i) 
		z[i] = z[i - 1] + (a[i] == '0');
	
	ll ans = 0LL;
	for (int j = 0; j < m; ++j) {
		int L = max(0, j - (m - n));
		int R = min(n - 1, j);
		int sz = z[R] - (L > 0 ? z[L - 1] : 0);
		if (b[j] == '0')
			sz = R - L + 1 - sz;
		ans += sz;
	}
	
	cout << ans << endl;
	
	return 0;
}
