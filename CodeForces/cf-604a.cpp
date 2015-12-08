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
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	ll x[5] = {500, 1000, 1500, 2000, 2500};
	ll m[5], w[5];
	for (int i = 0; i < 5; ++i) cin >> m[i];
	for (int i = 0; i < 5; ++i) cin >> w[i];
	
	ll hs, hu;
	cin >> hs >> hu;
	
	ll score = 0LL;
	for (int i = 0; i < 5; ++i) {
		ll lhs = 25 * 3 * x[i];
		ll rhs = (250 - m[i]) * x[i] - 250 * 50 * w[i];
		score += lhs > rhs ? lhs : rhs;
	}
	
	score /= 250;
	score += 50 * (2 * hs - hu);
	cout << score << endl;
	
	return 0;
}
