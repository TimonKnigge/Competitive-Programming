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
	
	vb type;
	bool curtype = true;
	char c;
	
	while (true) {
		scanf(" %c", &c);
		type.push_back(curtype);
		scanf(" %c", &c);
		if (c == '=') break;
		curtype = (c == '+');
	}
	
	ll n, pos = 0, neg = 0;
	int _n;
	scanf("%d", &_n);
	n = ll(_n);
	for (size_t i = 0; i < type.size(); ++i)
		(type[i] ? pos : neg) += 1;
	
	if (pos * n - neg >= n && pos - n * neg <= n) {
		cout << "Possible" << endl;
		ll val = pos * n - neg;
		vi ans(type.size(), -1LL);
		for (size_t i = 0; i < type.size(); ++i) {
			if (type[i]) ans[i] = n;
		}
		
		for (size_t i = 0; i < type.size(); ++i) {
			if (val > n) {
				ll diff = min(n - 1, val - n);
				ans[i] -= diff;
				val -= diff;
			}
			if (i > 0) cout << (type[i] ? " + " : " - ");
			cout << abs(ans[i]);
		}
		cout << " = " << n << endl;
	} else cout << "Impossible" << endl;
	
	
	return 0;
}
