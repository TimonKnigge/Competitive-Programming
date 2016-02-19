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
	
	string s;
	cin >> s;
	
	vi d(s.length(), 0);
	for (size_t i = 0; i < s.length(); ++i)
		d[i] = (s[i] - '0');
	
	ll ans = 0LL;
	for (int i = 0; i < int(s.length()); ++i) {
		if (d[i] % 4 == 0) ans++;
		if (i > 0 && (10 * d[i-1] + d[i]) % 4 == 0)
			ans += ll(i);
	}
	
	cout << ans << endl;
	
	return 0;
}
