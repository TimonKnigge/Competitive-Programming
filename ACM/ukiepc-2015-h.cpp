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
const ll LLINF = 9000000000000000000;

ll det(ll x1, ll y1, ll x2, ll y2) {
	return x1 * y2 - x2 * y1;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	vector<ll> X(n, 0LL), H(n, 0LL);
	for (int i = 0; i < n; ++i)
		cin >> X[i] >> H[i];
	
	vi lnv(n, -1), rnv(n, n);
	for (int i = 1; i < n; ++i) {
		lnv[i] = i - 1;
		while (true) {
			int r = lnv[i];
			if (r < 0) break;
			int l = lnv[r];
			if (l < 0) break;
			ll dt = det(X[r] - X[i], H[r] - H[i], X[l] - X[i], H[l] - H[i]);
			if (dt <= 0) lnv[i] = l;
			else break;
		}
	}
	for (int i = n - 2; i >= 0; --i) {
		rnv[i] = i + 1;
		while (true) {
			int r = rnv[i];
			if (r >= n) break;
			int l = rnv[r];
			if (l >= n) break;
			ll dt = det(X[r] - X[i], H[r] - H[i], X[l] - X[i], H[l] - H[i]);
			if (dt >= 0) rnv[i] = l;
			else break;
		}
	}
	
	for (int i = 0; i < n; ++i) {
		ll lx, ly, mx, my, rx, ry;
		mx = X[i]; my = H[i];
		if (lnv[i] == -1) {
			lx = mx - 1;
			ly = my;
		} else {
			lx = X[lnv[i]];
			ly = H[lnv[i]];
			if (ly < H[i]) ly = H[i];
		}
		if (rnv[i] == n) {
			rx = mx + 1;
			ry = my;
		} else {
			rx = X[rnv[i]];
			ry = H[rnv[i]];
			if (ry < H[i]) ry = H[i];
		}
		ld ang = atan2(ly - my, lx - mx) - atan2(ry - my, rx - mx);
		printf("%.7lf\n", double(ang / acos(-1.0) * 12.0));
	}
	
	return 0;
}
