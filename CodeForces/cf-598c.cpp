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

ld MY_PI = 3.14159265358979323846;

struct point {
	ll x, y;
	int id;
	ld pv = 0.0;
	point() : x(0LL), y(0LL), id(0) { }
	point(ll x, ll y, int id) : x(x), y(y), id(id) {
		pv = atan2(y, x);
		while (pv < 0) pv += 2 * MY_PI;
		while (pv >= 2 * MY_PI) pv -= 2 * MY_PI;
	}
	bool operator<(const point &rhs) const {
		return pv < rhs.pv;
	}
};

int main() {
	
	int n;
	scanf("%d", &n);
	vector<point> pts(n, point());
	for (int i = 0; i < n; ++i) {
		int x, y;
		scanf("%d %d", &x, &y);
		pts[i] = point(ll(x), ll(y), i + 1);
	}
	
	sort(pts.begin(), pts.end());
	
	ld best = 10.0;
	int l = -1, r = -1;
	for (int i = 0; i < n; ++i) {
		int j = (i + 1) % n;
		ld diff = abs(pts[i].pv - pts[j].pv);
		if (diff > 2 * MY_PI - diff)
			diff = 2 * MY_PI - diff;
		if (diff < best) {
			best = diff;
			l = i;
			r = j;
		}
	}
	
	cout << pts[l].id << ' ' << pts[r].id << endl;
	
	return 0;
}
