#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

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

// Note: if h.size() is small, consider bruteforcing to avoid
// the usual nasty computational-geometry-edge-cases.
bool rotating_calipers(vector<point> &p1, vector<point> &p2, vector<int> &h) {
	int n = p1.size(), i = 0, j = 1, a = 0, b = 1;
	while (i < 2 * n) {
		// >= 0 => move a
		// < 0  => move i
		if (det(p1[j].x - p1[i%n].x, p1[j].y - p1[i%n].y,
			p2[h[b]].x - p2[h[a]].x, p2[h[b]].y - p2[h[a]].y) <= 0) {
			a = (a + 1) % h.size();
			b = (b + 1) % h.size();
		} else {
			i++; // Not %n !!
			j = (j + 1) % n;
		}

//		cout << i << ' ' << j << ' ' << a << ' '  << b << endl;

		// Make computations on the pairs:
		// 	h[i%n], h[a]
		//	h[j], h[a]
		ll d = det(p1[j], p2[h[a]], p1[i%n]);
		if (d <= 0) return false;
	}
	return true;
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	vector<point> A(n, {0,0});
	for (int i = n - 1; i >= 0; --i) {
		ll x, y;
		cin >> x >> y;
		A[i] = {x, y};
	}

	int m;
	cin >> m;
	vector<point> B;
	for (int j = 0; j < m; ++j) {
		ll x, y;
		cin >> x >> y;
		B.push_back({x, y});
	}

	ConvexHull ch(B);

	bool strict = rotating_calipers(A, B, ch.h);
	cout << (strict ? "YES" : "NO") << endl;
	
	return 0;
}

