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
	
	ll S, X;
	cin >> S >> X;
	
	S -= X;
	if ((S&1) || S < 0) {
		cout << 0 << endl;
		return 0;
	}
	cerr << S << ' ' << X << endl;
	S /= 2LL;
	int exp = __builtin_popcountll(X&~S);
	ll ans = 1LL << exp;
	if (S == 0) ans -= 2LL;
	if (ans < 0LL || ((X&S) != 0LL)) ans *= 0LL;
	cout << ans << endl;
	
	return 0;
}
