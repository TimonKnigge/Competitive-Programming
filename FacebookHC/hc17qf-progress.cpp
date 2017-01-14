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

ld PI = ld(2.0) * atan2(ld(1), ld(0));

bool f() {
	ll P, X, Y;
	cin >> P >> X >> Y;
	X -= 50LL;
	Y -= 50LL;
	swap(X, Y);
	if (X*X + Y*Y > 50LL*50LL) return false;
	if (Y == 0)
		return (X < 0 ? (P >= 50) : (P > 0));
	ld at = atan2(ld(Y), ld(X));
	if (at < 0) at += 2 * PI;
	return (ld(P) / 50.0 * PI >= at);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int T;
	cin >> T;
	for (int t = 1; t <= T; ++t)
		cout << "Case #" << t << ": ",
		cout << (f() ? "black" : "white") << endl;
	
	return 0;
}
