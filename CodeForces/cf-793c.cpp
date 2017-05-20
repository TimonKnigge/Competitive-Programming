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

const ll INF = ll(1e8);
const ll LLINF = 9000000000000000000;

bool lt(ii a, ii b) {
	ll l = a.first * b.second;
	ll r = b.first * a.second;
	if (a.second < 0) swap(l, r);
	if (b.second < 0) swap(l, r);
	return l < r;
}
ii ltmin(ii a, ii b) { return lt(a, b) ? a : b; }
ii ltmax(ii a, ii b) { return lt(a, b) ? b : a; }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	
	ll x1, y1, x2, y2;
	cin >> x1 >> y1 >> x2 >> y2;
	
	ii m = {0, 1}, M = {INF, 1};
	for (int i = 0; i < n; ++i) {
		ll rx, ry, vx, vy;
		cin >> rx >> ry >> vx >> vy;
		
		ii mx, Mx, my, My;
		if (vx == 0) {
			mx = ii(0, 1);
			Mx = ii(x1 < rx && rx < x2 ? INF : -1, 1);
		} else {
			mx = ii(x1 - rx, vx);
			Mx = ii(x2 - rx, vx);
			if (lt(Mx, mx)) swap(Mx, mx);
		}

		if (vy == 0) {
			my = ii(0, 1);
			My = ii(y1 < ry && ry < y2 ? INF : -1, 1);
		} else {
			my = ii(y1 - ry, vy);
			My = ii(y2 - ry, vy);
			if (lt(My, my)) swap(My, my);
		}
		
		m = ltmax(m, mx);
		M = ltmin(M, Mx);
		m = ltmax(m, my);
		M = ltmin(M, My);
	}
	
	if (!lt(m, M))
		printf("-1\n");
	else	printf("%.10lf\n", double(ld(m.first) / ld(m.second)));
	
	return 0;
}
