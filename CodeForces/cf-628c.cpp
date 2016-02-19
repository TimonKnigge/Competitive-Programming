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
	
	int n, k;
	cin >> n >> k;
	
	string s;
	cin >> s;
	
	for (size_t i = 0; k > 0 && i < s.length(); ++i) {
		if (s[i] <= 'm') {
			int d = min(25 - (s[i] - 'a'), k);
			s[i] = char(s[i] + d);
			k -= d;
		} else {
			int d = min(25 - int('z' - s[i]), k);
			s[i] = char(s[i] - d);
			k -= d;
		}
	}
	
	if (k > 0) cout << -1 << endl;
	else cout << s << endl;
	
	return 0;
}
