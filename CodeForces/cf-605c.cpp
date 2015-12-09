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
using ld = long double;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

ll det(ll x1, ll y1, ll x2, ll y2) {
	return x1 * y2 - x2 * y1;
}
ll det (ll x1, ll y1, ll x2, ll y2, ll x3, ll y3) {
	return det(x1 - x3, y1 - y3, x2 - x3, y2 - y3);
}

int main() {
	
	int n, p, q;
	scanf("%d %d %d", &n, &p, &q);
	
	vector<pair<ll, ll> > pts;
	int maxx = -1, maxy = -1;
	for (int i = 0; i < n; ++i) {
		int x, y;
		scanf("%d %d", &x, &y);
		maxx = max(maxx, x);
		maxy = max(maxy, y);
		pts.push_back({x, y});
	}
	pts.push_back({0, maxy});
	
	sort(pts.begin(), pts.end());
	vi hull;
	for (int i = 0; i < pts.size(); ++i) {
		if (hull.size() < 2) {
			hull.push_back(i);
			continue;
		}
		while (!hull.empty() && pts[hull.back()].first == pts[i].first && pts[hull.back()].second != 0) hull.pop_back();
		while (hull.size() >= 2) {
			ll d = det(pts[i].first, pts[i].second, pts[hull.back()].first, pts[hull.back()].second, pts[hull[hull.size() - 2]].first, pts[hull[hull.size() - 2]].second);
			if (d <= 0) hull.pop_back();
			else break;
		}
		hull.push_back(i);
	}
	pts.push_back({maxx, 0});
	hull.push_back(pts.size() - 1);
	
//	for (int i = 0; i < hull.size(); ++i)
//		cerr << pts[hull[i]].first << ' ' << pts[hull[i]].second << endl;
	
	// Cut p, q with the hull
	ld ans = 0.0;
	for (int i = 0; i < hull.size() - 1; ++i) {
		ll s1x = p, s1y = q;
		ll x1 = pts[hull[i]].first, y1 = pts[hull[i]].second;
		ll x2 = pts[hull[i + 1]].first, y2 = pts[hull[i + 1]].second;
		ll s2x = x2 - x1, s2y = y2 - y1;
		
		ld denom = det(s1x, s1y, s2x, s2y);
//		cerr << denom << endl;
		if (denom == 0) cerr << "Oh snap." << endl;
		else {
			ld l = det(s1x, s1y, 0 - x1, 0 - y1) / denom;
			ld m = det(s2x, s2y, -x1, -y1) / denom;
//			cerr << l << ' ' << m << endl;
			ans = max(ans, 1 / m);
		}
	}
	
	printf("%.7lf\n", double(ans));
	
	return 0;
}
