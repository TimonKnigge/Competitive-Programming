#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <cmath>

using namespace std;
typedef long long ll;

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
	vector<int> h;	// incides of the hull in p, ccw
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
typedef long double ld;
long double dist(point &l, point &r) {
	return sqrt((l.x - r.x)*(l.x - r.x) + (l.y - r.y)*(l.y - r.y));
}
long double area(point &p1, point &p2, point &p3) {
	return abs(ld(p3.x - p1.x)*ld(p2.y - p1.y)
		- ld(p3.y - p1.y)*ld(p2.x - p1.x)) / 2.0;
}

ll eenevijf = ll(1e5);

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	vector<point> pts;
	for (int i = 0; i < n; ++i) {
		ll x, y, v;
		cin >> x >> y >> v;
		if (x + v <= eenevijf)
			pts.push_back({x+v, y});
		else {
			if (y - (x + v - eenevijf) >= 0)
				pts.push_back({eenevijf, y - (x + v - eenevijf)});
			else pts.push_back({eenevijf, 0});
			if (y + (x + v - eenevijf) <= eenevijf)
				pts.push_back({eenevijf, y + (x + v - eenevijf)});
			else pts.push_back({eenevijf, eenevijf});
		}
		if (x - v >= 0)
			pts.push_back({x-v, y});
		else {
			if (y - (v - x) >= 0)
				pts.push_back({0, y - (v - x)});
			else pts.push_back({0, 0});
			if (y + (v - x) <= eenevijf)
				pts.push_back({0, y + (v - x)});
			else pts.push_back({0, eenevijf});
		}
		if (y + v <= eenevijf)
			pts.push_back({x, y+v});
		else {
			if (x - (y + v - eenevijf) >= 0)
				pts.push_back({x - (y + v - eenevijf), eenevijf});
			else pts.push_back({0, eenevijf});
			if (x + (y + v - eenevijf) <= eenevijf)
				pts.push_back({x + (y + v - eenevijf), eenevijf});
			else pts.push_back({eenevijf, eenevijf});
		}
		if (y - v >= 0)
			pts.push_back({x, y-v});
		else  {
			if (x - (v - y) >= 0)
				pts.push_back({x - (v - y), 0});
			else pts.push_back({0, 0});
			if (x + (v - y) <= eenevijf)
				pts.push_back({x + (v - y), 0});
			else pts.push_back({0, eenevijf});
		}
	}
//	for (int i = 0; i < pts.size(); ++i) cout<<' '<<pts[i].x <<' '<<pts[i].y<<endl;
	ConvexHull ch(pts);
	vector<int> &h = ch.h;
//	for (int i : h) cout <<' '<< pts[i].x << ' ' << pts[i].y << endl;
	long double best = 0.0;
	int ib = 0, jb = 1, kb = 2;
	for (int i = 0; i < h.size(); ++i) {
		int j = (i + 1)%h.size(), k = (i + 2)%h.size();
		long double ab = dist(pts[h[i]], pts[h[j]]),
			bc = dist(pts[h[j]], pts[h[k]]),
			ca = dist(pts[h[k]], pts[h[i]]);
		long double ar = area(pts[h[i]], pts[h[j]], pts[h[k]]);
		if (ar < 1e-6) continue;
		if (ab * bc * ca * 0.25 / ar >= best) {
			best = ab * bc * ca * 0.25 / ar;
			ib = h[i]; jb = h[j]; kb = h[k];
		}
//		cout << (ab * bc * ca * 0.25 / ar) << endl;
	}
	cout << pts[ib].x << ' ' << pts[ib].y << '\n';
	cout << pts[jb].x << ' ' << pts[jb].y << '\n';
	cout << pts[kb].x << ' ' << pts[kb].y << endl;
	
	return 0;
}
