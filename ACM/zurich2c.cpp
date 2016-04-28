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

struct point { ll x, y; };
bool operator==(const point &l, const point &r) {
	return l.x == r.x && l.y == r.y; }

ll dsq(const point &p1, const point &p2) {
	return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y); }
ll det(ll x1, ll y1, ll x2, ll y2) {
	return x1 * y2 - x2 * y1; }
ll det(const point &p1, const point &p2, const point &d) {
	return det(p1.x - d.x, p1.y - d.y, p2.x - d.x, p2.y - d.y); }
bool comp_lexo(const point &l, const point &r) {
	return l.y != r.y ? l.y < r.y : l.x < r.x; }
bool comp_angl(const point &l, const point &r, const point &c) {
	ll d = det(l, r, c);
	if (d != 0) return d > 0;
	else return dsq(c, l) < dsq(c, r);
}

struct ConvexHull {
	vector<point> &p;
	vi h;	// incides of the hull in p, ccw
	ConvexHull(vector<point> &_p) : p(_p) { compute_hull(); }
	void compute_hull() {
		int pivot = 0, n = p.size();
		vector<int> ps(n + 1, 0);
		for (int i = 1; i < n; ++i) {
			ps[i] = i;
			if (comp_lexo(p[i], p[pivot])) pivot = i;
		}
		ps[0] = ps[n] = pivot; ps[pivot] = 0;
		sort(ps.begin()+1, ps.end()-1, [this, &pivot](int l, int r) {
			return comp_angl(p[l], p[r], p[pivot]); });

		h.push_back(ps[0]);
		size_t i = 1; ll d;
		while (i < ps.size()) {
			if (p[ps[i]] == p[h.back()]) { i++; continue; }
			if (h.size() < 2 || ((d = det(p[h.end()[-2]],
				p[h.back()], p[ps[i]])) > 0)) { // >= for col.
				h.push_back(ps[i]);
				i++; continue;
			}
			if (p[h.end()[-2]] == p[ps[i]]) { i++; continue; }
			h.pop_back();
			if (d == 0) h.push_back(ps[i]);
		}
		if (h.size() > 1 && h.back() == pivot) h.pop_back();
	}
};

ll dot(ll x1, ll y1, ll x2, ll y2) {
	return x1*x2 + y1*y2;
}
ll dot(point &p1, point &p2) {
	return dot(p1.x, p1.y, p2.x, p2.y);
}

ld dissq(point &p1, point &p2, point &x) {
	ld lambda = dot(x.x - p1.x, x.y - p1.y, p2.x - p1.x, p2.y - p1.y)
		  / ld(dot(p2.x - p1.x, p2.y - p1.y, p2.x - p1.x, p2.y - p1.y));
	lambda = min(ld(1.0), max(ld(0.0), lambda));
	ld dx = ld(p1.x) + ld(p2.x - p1.x) * lambda - x.x;
	ld dy = ld(p1.y) + ld(p2.y - p1.y) * lambda - x.y;
	return dot(dx, dy, dx, dy);
}

bool intersect(point &p1, point &p2, point &p3, point &p4) {
	ll v1 = det(p1.x - p3.x, p1.y - p3.y, p4.x - p3.x, p4.y - p3.y);
	ll v2 = det(p2.x - p3.x, p2.y - p3.y, p4.x - p3.x, p4.y - p3.y);
	if (v1 * v2 >= 0) return false;
	v1 = det(p3.x - p1.x, p3.y - p1.y, p2.x - p1.x, p2.y - p1.y);
	v2 = det(p4.x - p1.x, p4.y - p1.y, p2.x - p1.x, p2.y - p1.y);
	return (v1 * v2 < 0);
}

constexpr ld EPSILON = 1e-3;
bool solve(int D, int P) {
	vector<point> dp, pp;
	while (D--) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		dp.push_back({x1, y1});
		dp.push_back({x1, y2});
		dp.push_back({x2, y1});
		dp.push_back({x2, y2});
	}
	while (P--) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		pp.push_back({x1, y1});
		pp.push_back({x1, y2});
		pp.push_back({x2, y1});
		pp.push_back({x2, y2});
	}
	
	ConvexHull chd(dp), phd(pp);
	vi &dh = chd.h, &ph = phd.h;
	
	bool p = false, n = false;
	for (size_t i = 0; i < dh.size(); ++i) {
		size_t ii = (i + 1) % dh.size();
		ll d = det(pp[ph[0]].x - dp[dh[i]].x, pp[ph[0]].y - dp[dh[i]].y,
			dp[dh[ii]].x - dp[dh[i]].x, dp[dh[ii]].y - dp[dh[i]].y);
		if (d < 0) n = true; else if (d > 0) p = true;
	}
	if (!p || !n) {
//		cerr << "inside1"<< endl;
		return false;
	}
	p = false; n = false;
	for (size_t i = 0; i < ph.size(); ++i) {
		size_t ii = (i + 1) % ph.size();
		ll d = det(dp[dh[0]].x - pp[ph[i]].x, dp[dh[0]].y - pp[ph[i]].y,
			pp[ph[ii]].x - pp[ph[i]].x, pp[ph[ii]].y - pp[ph[i]].y);
		if (d < 0) n = true; else if (d > 0) p = true;
	}
	if (!p || !n) {
//		cerr << "inside2" << endl;
		return false;
	}
	
	ld dis = 1e300;
	for (size_t i = 0; i < dh.size(); ++i) {
		for (size_t j = 0; j < ph.size(); ++j) {
			size_t ii = (i + 1) % dh.size();
			size_t jj = (j + 1) % ph.size();
			dis = min(dis, min(
				dissq(dp[dh[i]], dp[dh[ii]], pp[ph[j]]),
				dissq(pp[ph[j]], pp[ph[jj]], dp[dh[i]])));
			if (intersect(dp[dh[i]], dp[dh[ii]], pp[ph[j]], pp[ph[jj]])) {
//				cerr << "intersect" << endl;
//				cerr << dp[dh[i]].x << "," << dp[dh[i]].y << " ";
//				cerr << dp[dh[ii]].x << "," << dp[dh[ii]].y << " ";
//				cerr << pp[ph[j]].x << "," << pp[ph[j]].y << " ";
//				cerr << pp[ph[jj]].x << "," << pp[ph[jj]].y << " ";
//				cerr << endl;
				return false;
			}
		}
	}
	return dis > EPSILON;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int D, P, t = 1;
	while (cin >> D >> P) {
		if (D == 0 && P == 0) break;
		if (t > 1) cout << '\n';
		cout << "Case " << t << ": ";
		++t;
		if (solve(D, P)) {
			cout << "It is possible to separate the two groups of vendors.\n";
		} else {
			cout << "It is not possible to separate the two groups of vendors.\n";
		}
	}
	
	return 0;
}
