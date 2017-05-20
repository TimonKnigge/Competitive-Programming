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
	
	ll n, k;
	cin >> n >> k;
	
	vi a(n, 0);
	ll mn = LLINF;
	for (ll &v : a) {
		cin >> v;
		mn = min(mn, v);
	}
	
	ll t = 0;
	bool pos = true;
	for (ll v : a) {
		v -= mn;
		if (v % k != 0)
			pos = false;
		else	t += v / k;
	}
	
	if (!pos) t = -1;
	cout << t << endl;
	
	return 0;
}
