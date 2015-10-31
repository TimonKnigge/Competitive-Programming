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
using ll = unsigned long long;
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

ll gcd(ll a, ll b) {
	while (b) { a %= b; swap(a, b); } return a;
}

// w * b > t ?
pair<ll, bool> exceed(ll w, ll b, ll t) {
	if (w == 1 || b > t) return {b, (b > t)};
	bool odd = (w&1);
	w /= 2ULL;
	b *= 2ULL;
	pair<ll, bool> ret = exceed(w, b, t);
	if (ret.second) return ret;
	if (odd) ret.first += b / 2ULL;
	return {ret.first, ret.first > t};
}

int main() {

	ll t, w, b;
	cin >> t >> w >> b;
	
	// Compute the gcd of w and b
	ll ggd = gcd(w, b);
	
	// Does the lcm exceed t?
	pair<ll, bool> exc = exceed(w / ggd, b, t);
//	cerr << exc.first << ' ' << exc.second << endl;
	ll ans = 0ULL;
	ll mn = (w > b ? b : w);
	if (!exc.second) {
		ans += mn * (t / exc.first);
//		cerr << ans <<endl;
	}
	ll tm = (t % exc.first) + 1;
//	cerr << mn << ' ' << tm << ' '<<endl;
	ans += mn < tm ? mn : tm;
	if (ans > 0) ans --;
//	cerr << ans << endl;
	
	
	ll u = ans, v = t;
	if (u > 0) {
		ggd = gcd(u, v);
		u /= ggd; v /= ggd;
	} else {u = 0ULL; v = 1ULL;}
	cout << u << '/' << v<<endl;
	
	return 0;
}
