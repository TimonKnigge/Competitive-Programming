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
	
	constexpr ll H = 20000;
	
	ll h = 0LL;
	bool v = true;
	for (int i = 0; i < n; ++i) {
		ll t;
		string d;
		cin >> t >> d;
		if (d[0] == 'N') {
			h -= t;
			if (h < 0) v = false;
		} else if (d[0] == 'S') {
			h += t;
			if (h > H) v = false;
		} else	if (h == 0 || h == H) v = false;
	}
	v = v && h == 0LL;
	
	cout << (v ? "YES" : "NO") << endl;
	
	return 0;
}
