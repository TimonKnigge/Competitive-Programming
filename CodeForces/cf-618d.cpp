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
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 1000000000000000000;

void root(int u, vi &p, vvi &e) {
	for (int v : e[u]) {
		if (v == p[u]) continue;
		p[v] = u;
		root(v, p, e);
	}
}

// total cheapest, cheapest path
pair<ll, bool> calc(int u, vi &p, vvi &e, ll x, ll y) {
	
	ll r = 0;
	int add = 2;
	for (int v : e[u]) {
		if (v == p[u]) continue;
		pair<ll, int> a = calc(v, p, e, x, y);
		r += a.first;
		if (add > 0 && a.second) { ++r; --add; }
		
	}
	return {r, add > 0};
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	ll x, y;
	cin >> n >> x >> y;
	
	vvi e(n, vi());
	for (int i = 0; i < n - 1; ++i) {
		int a, b;
		cin >> a >> b;
		--a; --b;
		e[a].push_back(b);
		e[b].push_back(a);
	}
	
	vi p(n, -1);
	root(0, p, e);
	
	if (x < y) {
		ll c = calc(0, p, e, x, y).first;
		cout << c * x + (n - c - 1) * y << endl;
	} else {
		bool star = false;
		for (int i = 0; i < n; ++i) {
			if (int(e[i].size()) == n - 1) star = true;
		}
		if (n == 1) cout << 0 << endl;
		else cout << (star ? x + ((n-2) * y) : (n-1) * y) << endl;
	}
	
	return 0;
}
