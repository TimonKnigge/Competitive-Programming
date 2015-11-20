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


ll eval(vector<ll> &c, ll x) {
	ll ret = 0LL;
	ll val = 1LL;
	for (int i = c.size() - 1; i >= 0; --i) {
		ret += val * c[i];
		val *= x;
	}
	return ret;
}

void int_roots(vector<ll> &c, set<ll> &rt) {
	rt.clear();
	for (int r = -10; r <= 10; ++r) {
		if (eval(c, r) == 0)
			rt.insert(r);
	}
}

void differentiate(vector<ll> &c) {
	int n = c.size() - 1;
	for (int i = 0; i < c.size(); ++i) {
		c[i] *= n;
		n--;
	}
	c.pop_back();
}

int main() {
	
	int n;	
	cin >> n;
	vector<ll> c(n + 1, 0);
	c[0] = 1LL;
	for (int i = 1; i <= n; ++i)
		cin >> c[i];
	
	vector<set<ll> > rts(n + 1, set<ll>());
	for (int i = 0; i <= n; ++i) {
		int_roots(c, rts[i]);
//		cerr << i <<": ";
//		for (ll rr : rts[i]) cerr << rr << ' ';
//		cerr << endl;
		differentiate(c);
	}
	
	// Count all rationanl roots
	int roots = n;
	for (ll root : rts[0]) {
		// If root appears in rts[i] it is an i+1 'th root
		roots--;
		for (int i = 1; i <= n; ++i) {
			if (rts[i].find(root) != rts[i].end())
				roots--;
			else break;
		}
	}
	
	cout << roots << endl;
	
	return 0;
}
