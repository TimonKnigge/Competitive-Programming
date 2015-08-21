#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef long double ld;

template <class T>
struct point {
	T x, y;
	point(T x, T y) : x(x), y(y) { }
	point() : x(0), y(0) { }
};

template<class T>
T det(T x1, T y1, T x2, T y2) {
	return x1 * y2 - x2 * y1;
}
template<class T>
T det(T x1, T y1, T x2, T y2, T x3, T y3) {
	return det<T>(x2 - x1, y2 - y1, x3 - x1, y3 - y1);
}

bool intersect(point<ll> &p, ll vx, ll vy, point<ll> &l1, point<ll> &l2, ld &t1, ld &t2) {
	ll s2x, s2y;
	s2x = l2.x - l1.x; s2y = l2.y - l1.y;
	ll denom = det<ll>(vx, vy, s2x, s2y);
	if (denom == 0) {
		// coincidence
		if (det(l1.x, l1.y, l2.x, l2.y, p.x, p.y) == 0) {
			ld _t1, _t2;
			if (vx != 0) {
				_t1 = (l1.x - p.x) / vx;
				_t2 = (l2.x - p.x) / vx;
			} else {
				_t1 = (l1.y - p.y) / vy;
				_t2 = (l2.y - p.y) / vy;
			}
			if (_t1 > _t2) swap(_t1, _t2);
			if (_t2 < 0) return false;
			t1 = max(ld(0.0), _t1);
			t2 = _t2;
			return true;
		} else return false;
	} else {
		long double l = det(vx, vy, p.x - l1.x, p.y - l2.y) / ld(denom);
		long double m = det(s2x, s2y, p.x - l1.x, p.y - l2.y) / ld(denom);
		if (l < 0) return false;
		if (m < 0 || m > 1) return false;
		t1 = l;
		t2 = l;
		return true;
	}
}

pair<ld, ld> ptime(vector<point<ll> > &p1, vector<point<ll> > &p2, ll vx, ll vy) {
	ld m = 1e300, M = -1e300;
	for (point<ll> p : p1) {
		for (int i = 0, j = 1; i < p2.size(); ++i, j = (j+1)%p2.size()) {
			ld t1, t2;
			if (intersect(p, vx, vy, p2[i], p2[j], t1, t2)) {
				m = min(m, min(t1, t2));
				M = max(M, max(t1, t2));
			}
		}
	}
	return {m, M};
}

ld shared_area(vector<point<ll> > &p1, vector<point<ll> > &p2, ld vx, ld vy) {
	
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	vector<point<ll> > p1, p2;
	int n;
	cin >> n;
	ll vx, vy, vx2, vy2;
	for (int i = 0; i < n; ++i) {
		p1.push_back({0, 0});
		cin >> p1[i].x >> p1[i].y;
	}
	cin >> vx >> vy;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		p2.push_back({0, 0});
		cin >> p2[i].x >> p2[i].y;
	}
	cin >> vx2 >> vy2;
	vx -= vx2; vy -= vy2;
	// 1  beweegt wél, 2 beweegt niét
	
	if (vx == 0 && vy == 0) cout << "never" << endl;
	else {
		auto t1 = ptime(p1, p2, vx, vy), t2 = ptime(p2, p1, -vx, -vy);
		pair<ld, ld> t = {min(t1.first, t2.first), max(t1.second, t2.second)};
		
		
	}
	
	
	return 0;
}

