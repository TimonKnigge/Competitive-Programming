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

ll zeroes(ll V) {
	ll ret = 0LL;
	ll d = 5LL;
	while (d <= V) {
		ret += V / d;
		d *= 5LL;
	}
	return ret;
}

ll fst(ll V) {
	ll L = 0LL;
	ll R = 1LL;
	while (zeroes(R) <= V) R *= 2LL;
	while (L < R) {
		if (zeroes((L + R) / 2LL) < V)
			L = (L+R) / 2LL + 1LL;
		else	R = (L+R) / 2LL;
	}
	return L;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	ll V;
	cin >> V;
	
	ll L = fst(V), R = fst(V+1LL);
	cout << (R - L) << endl;
	bool sp = false;
	while (L < R) { 
		if (sp) cout << ' '; else sp = true;
		cout << L;
		++L;
	}
	cout << endl;
	
	return 0;
}
