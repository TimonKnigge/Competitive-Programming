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

ll gcd(ll a, ll b) {
	while (a) {
		b %= a;
		swap(a, b);
	}
	return b;
}

bool iscolinear(ii bx, vii &pts) {
	set<ii> seen;
	for (ii pt : pts) {
		pt.first  -= bx.first;
		pt.second -= bx.second;
		int sign = (pt.first>0?1:-1)*(pt.second>0?1:-1);
		pt.first = abs(pt.first);
		pt.second = abs(pt.second);
		
		ll g = gcd(pt.first, pt.second);
		ii v = {pt.first / g, pt.second / g * sign};
		if (seen.find(v) != seen.end()) return true;
		seen.insert(v);
	}
	return false;
}

void solve() {
	int N;
	cin >> N;
	--N;
	
	ii bx;
	cin >> bx.first >> bx.second;
	
	vii pts(N, {0LL, 0LL});
	for (ii &pt : pts) cin >> pt.first >> pt.second;
	
	if (iscolinear(bx, pts)) {
		cout << 0 << endl;
		return;
	}
	
	
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int T;
	cin >> T;
	while (T--) solve();
	
	return 0;
}
