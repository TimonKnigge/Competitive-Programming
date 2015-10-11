#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using ll = long long;
using vi = vector<int>;

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

// Note: if h.size() is small (<5), consider brute forcing to avoid
// the usual nasty computational-geometry-edge-cases.
ll rotating_calipers(vector<point> &p, vector<int> &h) {
	int n = h.size();
	ll best = 0LL;
	int i = 0, j = 1, k = 2, l = 3%n;
	while (i < 2 * n) {
		// Move k to maximize the distance between i and k
		int ii = (i+1)%n;
		int kk = (k+1) % n;
		if (det(p[h[ii]].x - p[h[i % n]].x, p[h[ii]].y - p[h[i % n]].y,
			p[h[kk]].x - p[h[k]].x, p[h[kk]].y - p[h[k]].y)
			> 0) k = (k + 1) % n;
		else i++;
		
		// Move j and l accordingly:
		if (j == i % n) j = (j + 1) % n;
		ii = (i + 1) % n;
		int jj = (j + 1) % n;
		while (j != k &&
		    det(p[h[k]].x - p[h[i%n]].x, p[h[k]].y - p[h[i%n]].y,
			p[h[jj]].x - p[h[j]].x, p[h[jj]].y - p[h[j]].y)
			< 0) { 
			j = jj; jj = (j + 1) % n; 
			ll thistime = (abs(det(p[h[i%n]], p[h[j]], p[h[k]]))+
				abs(det(p[h[i%n]], p[h[l]], p[h[k]]))) / 2;
			if (thistime > best) best = thistime;
		}
		
		ll thistime2 = (abs(det(p[h[i%n]], p[h[j]], p[h[k]]))+
			abs(det(p[h[i%n]], p[h[l]], p[h[k]]))) / 2;
		if (thistime2 > best) best = thistime2;
		
		if (l == k) l = (l + 1) % n;
		int L = (l + 1) % n;
		while (l != i % n &&
		    det(p[h[i%n]].x - p[h[k]].x, p[h[i%n]].y - p[h[k]].y,
			p[h[L]].x - p[h[l]].x, p[h[L]].y - p[h[l]].y)
			< 0) { 
			l = L; L = (l + 1) % n;
			
			ll thistime = (
				abs(det(p[h[i%n]], p[h[j]], p[h[k]])) + 
				abs(det(p[h[i%n]], p[h[l]], p[h[k]]))
					) / 2;
			if (thistime > best) best = thistime;
		}
		
		thistime2 = (abs(det(p[h[i%n]], p[h[j]], p[h[k]]))+
			abs(det(p[h[i%n]], p[h[l]], p[h[k]]))) / 2;
		if (thistime2 > best) best = thistime2;
		
//		cerr << i << ' ' << j << ' ' << k  <<  ' '<< l << ' ' << thistime2 << endl;
	}
	return best;
}

ll solve(vector<point> &pts, vector<int> &h) {
	if (h.size() <= 3) {
		if (h.size() <= 2) return 0;
		else return abs(det(pts[h[0]], pts[h[1]], pts[h[2]])/2);
	} else return rotating_calipers(pts, h);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int T;
	cin >> T;
	while (T--) {
		int N;
		cin >> N;
		
		vector<point> pts(N, {0LL, 0LL});
		for (int i = 0; i < N; ++i) {
			cin >> pts[i].x >> pts[i].y;
			pts[i].x *= 2;
			pts[i].y *= 2;
		}
		
		ConvexHull ch(pts);
//		for (int i = 0; i < ch.h.size(); ++i)
//		cerr << ch.h[i] << ' '; cerr<<endl;
		ll ans = solve(pts, ch.h);
		cout << (ans / 4);
		if (ans % 4 == 2) cout << ".5";
		cout << '\n';
		cout << flush;
	}
	cout << flush;
	
	return 0;
}

