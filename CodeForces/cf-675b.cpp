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
	
	ll n, a, b, c, d;
	cin >> n >> a >> b >> c >> d;
	
	ll x5 = a-d;
	ll x4 = b-c;
	ll x3 = b-c + a-d;
	cerr << x5 << ' ' << x4 << ' ' << x3 << endl;
	
	ll D = max(max(x5, 0LL), max(x4, x3)) - min(min(x5, 0LL), min(x4, x3));
	
	cout << n * max(0LL, n - D) << endl;
	
	return 0;
}
