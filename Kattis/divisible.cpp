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

void solve() {
	int _d, n;
	scanf("%d %d", &_d, &n);
	ll d = ll(_d);
	vector<ll> num(n, 0LL);
	for (int i = 0; i < n; ++i) {
		int x;
		scanf("%d", &x);
		num[i] = ll(x);
	}
	
	// For each position, find out whether it is the end point of a
	// sequence divisible by d.
	map<ll, int> cnt;
	cnt.insert({0, 1});
	ll ans = 0LL, sum = 0LL;
	for (int r = 0; r < n; ++r) {
		sum += num[r];
		sum %= d;
		
		auto it = cnt.find(sum);
		if (it == cnt.end()) cnt.insert({sum, 1});
		else {
			ans += ll(it->second);
			it->second++;
		}
	}
	cout << ans << endl;
}

int main() {
	
	int c;
	scanf("%d", &c);
	while (c--) solve();
	
	return 0;
}
