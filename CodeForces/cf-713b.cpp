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

int q(int x1, int y1, int x2, int y2) {
	if (x1 > x2) swap(x1, x2);
	if (y1 > y2) swap(y1, y2);
	cout << "? " << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << endl;
	int res;
	cin >> res;
	return res;
}

bool attempt(ii x1, ii y1, ii x2, ii y2) {
	if (!(x1.second < x2.first || x2.second < x1.first
		|| y1.second < y2.first || y2.second < y1.first))
		return false;
	
	if (x1.first > x1.second) return false;
	if (x2.first > x2.second) return false;
	if (y1.first > y1.second) return false;
	if (y2.first > y2.second) return false;
	
	int a1 = q(x1.first, y1.first, x1.second, y1.second);
	if (a1 != 1) return false;
	int a2 = q(x2.first, y2.first, x2.second, y2.second);
	return (a1 == 1 && a2 == 1);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, m;
	cin >> n;
	m = n;
	
	int x1[2], y2[2], y1[2], x2[2];
	int l, r;
	
	// left
	l = 1; r = m;
	while (l < r) {
		int mid = (l+r+1)/2;
		if (q(mid, 1, m, m) == 2)
			l = mid;
		else	r = mid - 1;
	}
	x1[0] = l;
	l = x1[0]; r = m;
	while (l < r) {
		int mid = (l+r+1)/2;
		if (q(mid, 1, m, m) > 0)
			l = mid;
		else	r = mid - 1;
	}
	x1[1] = l;
	
	// right
	l = 1; r = m;
	while (l < r) {
		int mid = (l+r)/2;
		if (q(1, 1, mid, m) == 2)
			r = mid;
		else	l = mid + 1;
	}
	x2[0] = l;
	l = 1; r = x2[0];
	while (l < r) {
		int mid = (l+r)/2;
		if (q(1, 1, mid, m) > 0)
			r = mid;
		else	l = mid + 1;
	}
	x2[1] = l;
	
	// down
	l = 1; r = m;
	while (l < r) {
		int mid = (l+r+1)/2;
		if (q(1, mid, m, m) == 2)
			l = mid;
		else	r = mid - 1;
	}
	y1[0] = l;
	l = y1[0]; r = m;
	while (l < r) {
		int mid = (l+r+1)/2;
		if (q(1, mid, m, m) > 0)
			l = mid;
		else	r = mid - 1;
	}
	y1[1] = l;
	
	// up
	l = 1; r = m;
	while (l < r) {
		int mid = (l+r)/2;
		if (q(1, 1, m, mid) == 2)
			r = mid;
		else	l = mid + 1;
	}
	y2[0] = l;
	l = 1; r = y2[0];
	while (l < r) {
		int mid = (l+r)/2;
		if (q(1, 1, m, mid) > 0)
			r = mid;
		else	l = mid + 1;
	}
	y2[1] = l;
	
	for (int i1 = 0; i1 < 2; ++i1)
	for (int i2 = 0; i2 < 2; ++i2)
	for (int i3 = 0; i3 < 2; ++i3)
	for (int i4 = 0; i4 < 2; ++i4) {
		if (attempt({x1[i1], x2[i2]}, {y1[i3], y2[i4]}, {x1[1-i1], x2[1-i2]}, {y1[1-i3], y2[1-i4]})) {
			cout << "! ";
			cout << x1[i1] << ' ' << y1[i3] << ' ' << x2[i2] << ' ' << y2[i4] << ' ';
			cout << x1[1-i1] << ' ' << y1[1-i3] << ' ' << x2[1-i2] << ' ' << y2[1-i4] << endl;
			return 0;
		}
	}
	
	return 0;
}
