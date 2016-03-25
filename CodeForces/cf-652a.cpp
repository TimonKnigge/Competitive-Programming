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
	
	ll h1, h2, a, b;
	cin >> h1 >> h2 >> a >> b;
	
	ll d = h2 - h1;
	d -= a * 8LL;
	if (d <= 0) {
		cout << 0 << endl;
	} else if (b >= a) {
		cout << -1 << endl;
	} else {
		d += b * 12LL;
		ll days = 0LL;
		while (true) {
			d -= 12LL * a;
			++days;
			if (d <= 0) break;
			d += 12LL * b;
		}
		cout << days << endl;
	}
	
	return 0;
}
