#include <bits/stdc++.h>

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

using C = ll;	// could be long long or long double
constexpr C EPS = 1e-10;	// change to 0 for C=ll
struct P {		// may also be used as a 2D vector
	C x, y;
	P(C x = 0, C y = 0) : x(x), y(y) {}
	P operator+ (const P &p) const { return {x + p.x, y + p.y}; }
	P operator- (const P &p) const { return {x - p.x, y - p.y}; }
	P operator* (C c) const { return {x * c, y * c}; }
	P operator/ (C c) const { return {x / c, y / c}; }
	bool operator==(const P &r) const { return y == r.y && x == r.x; }
	C lensq() const { return x*x + y*y; }
	ld len() const { return sqrt((ld)lensq()); }
};
C sq(C x){ return x*x; }
C dot(P p1, P p2){ return p1.x*p2.x + p1.y*p2.y; }
ld dist(P p1, P p2) { return (p1-p2).len(); }
C det(P p1, P p2) { return p1.x * p2.y - p1.y * p2.x; }
C det(P p1, P p2, P o) { return det(p1-o, p2-o); }
int sign(C c){ return (c > C(0)) - (c < C(0)); }
int ccw(P p1, P p2, P p3) { return sign(det(p1, p2, p3)); }

// bool: non-parallel (P is valid), p = a*l1+(1-a)*l2 = b*r1 + (1-b)*r2
pair<bool,pair<ld, ld>> intersect(
	P l1, P l2, P r1, P r2, ld &a, ld &b, bool &intern){
	P dl = l2-l1, dr = r2-r1; ld d = det(dl,dr);
	if(abs(d)<=EPS) return {false,{0,0}};	// parallel
	C x = det(l1,l2)*(r1.x-r2.x) - det(r1,r2)*(l1.x-l2.x);
	C y = det(l1,l2)*(r1.y-r2.y) - det(r1,r2)*(l1.y-l2.y);
	pair<ld, ld> rr = {ld(x)/ld(d), ld(y)/ld(d)};
	a = ld(det(r1-l1,dr)/d); b = ld(det(r1-l1,dl))/d;
	intern = 0<= a && a <= 1 && 0 <= b && b <= 1;
	return {true,rr};
}

int prev(int i, vector<P> &pts) { return (i + (int)pts.size() - 1) % (int)pts.size(); }
int next(int i, vector<P> &pts) { return (i + 1) % (int)pts.size(); }

ld dist(int i, int j, vector<P> &pts) {
	int ip = prev(i, pts), in = next(i, pts);
	ll dip = det(pts[ip], pts[j], pts[i]);
	ll din = det(pts[j], pts[in], pts[i]);
	ll dpn = det(pts[ip], pts[in], pts[i]);
	if (dpn > 0LL && dip > 0LL && din > 0LL)
		return 0.0;
	if (dpn < 0LL && (dip > 0LL || din > 0LL))
		return 0.0;
	
	ld ret = 1e9;
	for (int k = 0; k < (int)pts.size(); ++k) {
		int nk = next(k, pts);
		ll dk = det(pts[k], pts[j], pts[i]);
		ll dnk = det(pts[j], pts[nk], pts[i]);
		ld ca = 0.0, cb = 0.0; bool it = false;
		pair<bool, pair<ld, ld>> is = intersect(
			pts[i], pts[j],
			pts[k], pts[nk], ca, cb, it);
		if (ca < -EPS) continue;
		if ((dk > 0LL && dnk > 0LL) || (dk < 0LL && dnk < 0LL)) {
			ld dis = sqrt(ld(
				(pts[i].x-is.second.first)*
				(pts[i].x-is.second.first)+
				(pts[i].y-is.second.second)*
				(pts[i].y-is.second.second)));
			ret = min(ret, dis);
			continue;
		}
	}

	for (int k = in; k != i; k = next(k, pts)) {
		int nk = next(k, pts), pk = prev(k, pts);
		ll dpk = det(pts[pk], pts[j], pts[i]);
		ll dk = det(pts[k], pts[j], pts[i]);
		ll dnk = det(pts[j], pts[nk], pts[i]);

		ld ca = 0.0, cb = 0.0; bool it = false;
		intersect(pts[i], pts[j], pts[k], pts[nk], ca, cb, it);
		if (dk != 0LL) continue;
		if (ca < -EPS) continue;
		if (dpk > 0LL) {
			if (dnk > 0LL)
				ret = min(ret, dist(pts[i], pts[k]));
			if (dnk == 0LL && dist(pts[i], pts[k])
					> dist(pts[i], pts[nk]))
				ret = min(ret, dist(pts[i], pts[k]));
		} else if (dpk == 0LL) {
			if (dist(pts[i], pts[k]) > dist(pts[i], pts[pk])
				&& dnk > 0LL) {
				ret = min(ret, dist(pts[i], pts[k]));
			}
		}
	}
	return ret;
}

ld solve(int i, int j, vector<P> &pts) {
	return dist(i, j, pts) + dist(j, i, pts) - dist(pts[i], pts[j]);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N; cin >> N;
	vector<P> pts(N, {0, 0});
	for (int i = 0, u, v; i < N; ++i)
		cin >> u >> v,
		pts[i] = {u, v};
	
	ld best = 0.0;
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			if (i != j)
				best = max(best, solve(i, j, pts));
	printf("%.9lf\n", double(best));

	return 0;
}
