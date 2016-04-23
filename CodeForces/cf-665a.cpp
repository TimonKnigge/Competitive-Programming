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
	
	ll a, ta, b, tb, hh, mm;
	char tmp;
	cin >> a >> ta >> b >> tb >> hh >> tmp >> mm;
	
	ll time = 60LL * hh + mm, ans = 0LL;
	for (ll f = 300LL; f <= 23LL * 60LL + 59LL; f += b) {
		if (f < time + ta && f + tb > time)
			++ans;
	}
	
	cout << ans << endl;
	
	
	return 0;
}
