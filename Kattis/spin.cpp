#define _GLIBCXX_DEBUG
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
using ll = long long;
using ld = long double;
using ii = pair<ll, ll>;
using vi = vector<ll>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;
using vd = vector<ld>;

template<class T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<class TIn, class TOut = null_type>
using order_tree = tree<TIn, TOut, less<TIn>, rb_tree_tag,
	tree_order_statistics_node_update>;
// .find_by_order(int r) and .order_of_key(TIn v)

constexpr int INF = 2000000010;
constexpr ll LLINF = 9000000000000000010LL;
constexpr ld PI = acos(-1);

// CONVEXHULL
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
		vi ps(n + 1, 0);
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
//-CONVEXHULL

using C = ll;	// could be long long or long double
constexpr C EPS = 0LL;//1e-10;	// change to 0 for C=ll
struct P {		// may also be used as a 2D vector
	C x, y;
	P(C x = 0, C y = 0) : x(x), y(y) {}
	P operator+ (const P &p) const { return {x + p.x, y + p.y}; }
	P operator- (const P &p) const { return {x - p.x, y - p.y}; }
	P operator* (C c) const { return {x * c, y * c}; }
	P operator/ (C c) const { return {x / c, y / c}; }
	C operator* (const P &p) const { return x*p.x + y*p.y; }
	C operator^ (const P &p) const { return x*p.y - p.x*y; }
	P perp() const { return P{y, -x}; }
	C lensq() const { return x*x + y*y; }
	ld len() const { return sqrt((ld)lensq()); }
	static ld dist(const P &p1, const P &p2) {
		return (p1-p2).len(); }
	bool operator==(const P &r) const {
		return ((*this)-r).lensq() <= EPS*EPS; }
};
C det(P p1, P p2) { return p1^p2; }
C det(P p1, P p2, P o) { return det(p1-o, p2-o); }
C det(const vector<P> &ps) {
	C sum = 0; P prev = ps.back();
	for(auto &p : ps) sum += det(p, prev), prev = p;
	return sum;
}
// Careful with division by two and C=ll
C area(P p1, P p2, P p3) { return abs(det(p1, p2, p3))/C(2); }
C area(const vector<P> &poly) { return abs(det(poly))/C(2); }
int sign(C c){ return (c > C(0)) - (c < C(0)); }
int ccw(P p1, P p2, P o) { return sign(det(p1, p2, o)); }


//#include "../geometry/essentials.cpp"
bool lexo_yx(const P &l, const P &r) {
	return l.y != r.y ? l.y < r.y : l.x < r.x;
}
int quad(P p) {
	if (p.x > 0 && p.y >= 0) return 0;	// This `quad` is different from
	if (p.y > 0 && p.x <= 0) return 1;	// the one in planar-rotation.cpp,
	if (p.x < 0 && p.y <= 0) return 2;	// make sure to not mix the two.
	if (p.y < 0 && p.x >= 0) return 3;
	return 0; // p.x = 0 \land p.y = 0, go with 0 arbitrarily.
}
bool on_segment(P p1, P p2, P a) {
	return ccw(p1, p2, a) == 0LL
		&& min(p1.x, p2.x) <= a.x && a.x <= max(p1.x, p2.x)
		&& min(p1.y, p2.y) <= a.y && a.y <= max(p1.y, p2.y);
}
struct ConvexPolygon {
	// 21 Polygon is cut up into quadrants, where quadrant
	// 30 i is given by the segment [s[i], s[i+1])
	size_t s[5], N;
	vector<P> Ps;

	// TODO: describe input. Strict non-degenerate convex only!!
	ConvexPolygon(const vector<P> &_Ps) : N(_Ps.size()), Ps(_Ps) {
		size_t l = 0;
		for (size_t j = 1; j < N; ++j) l = (lexo_yx(Ps[l], Ps[j]) ? l : j);
		if (l != 0) std::rotate(Ps.begin(), Ps.begin()+l, Ps.end());
		cerr << "TODO: Copy last value or all?" << endl;
//		Ps.push_back(Ps.front());
		for (size_t i = 0; i < N; ++i) Ps.push_back(Ps[i]);
		s[0] = 0;
		for (int i = 1; i <= 4; ++i) {
			s[i] = s[i-1];
			while (s[i] < N && quad(Ps[s[i]+1] - Ps[s[i]]) < i) ++s[i];
		}
	}

	// Runs in O(lg n). Returns 1 for inside, 0 for border, -1 for outside.
	int contains(const P &p) const {
		if (p.y < Ps[s[0]].y || Ps[s[2]].y < p.y) return -1;
		{	// right hull
			size_t l = s[0], r = s[2];
			while (l < r) {
				size_t m = (l + r) / 2;
				if (Ps[m+1].y < p.y) l = m + 1; else r = m;
			}
			int side = ccw(Ps[l+1], p, Ps[l]);
			if (side < 0) return -1;
			if (side == 0) {
				if (max(Ps[l].x, Ps[l+1].x) <  p.x) return -1;
				if (min(Ps[l].x, Ps[l+1].x) <= p.x) return 0;
			}
		}{	// left hull
			size_t l = s[2], r = s[4];
			while (l < r) {
				size_t m = (l + r) / 2;
				if (Ps[m+1].y > p.y) l = m + 1; else r = m;
			}
			int side = ccw(Ps[l+1], p, Ps[l]);
			if (side < 0) return -1;
			if (side == 0) {
				if (min(Ps[l].x, Ps[l+1].x) >  p.x) return -1;
				if (max(Ps[l].x, Ps[l+1].x) >= p.x) return 0;
			}
		}
		return 1;
	}

	// Returns some i such that Ps[i] * v is maximal.
	size_t extreme(const P &v) const {
		size_t l, r;
		if (v.x > 0 || (v.x == 0LL && v.y < 0LL))
				l = s[0], r = s[2];
		else	l = s[2], r = s[4];
		while (l < r) {
			size_t m = (l + r) / 2;
			if ((Ps[m+1] - Ps[m]) * v <= 0LL)
					r = m;
			else	l = m + 1;
		}
		l %= N;
		// When there are two possible outputs, l is one of them. If l is the
		// 'largest' of the two, then this code moves to the 'smallest', if
		// it is not l (then it must be l-1). Only keep if this is important.
		if (Ps[(N+(l-1))%N] * v >= Ps[l] * v) l = (N+(l-1))%N;
		return l;
	}

	// Returns i such that p -> Ps[i] is right-tangent to Ps, cq j left.
	std::pair<size_t, size_t> tangent(const P &p) const {
//		assert(this->contains(p) < 0);
		size_t rt, lt;
		{	// right tangent
			size_t l, r;
			if (p.x < Ps[s[1]].x && (p.y <= Ps[s[0]].y || ccw(Ps[s[1]], p, Ps[s[0]]) < 0LL))
				l = s[0], r = s[1]; else
			if (p.y < Ps[s[2]].y && (p.x >= Ps[s[1]].x || ccw(Ps[s[2]], p, Ps[s[1]]) < 0LL))
				l = s[1], r = s[2]; else
			if (p.x > Ps[s[3]].x && (p.y >= Ps[s[2]].y || ccw(Ps[s[3]], p, Ps[s[2]]) < 0LL))
				l = s[2], r = s[3]; else
			if (p.y > Ps[s[4]].y && (p.x <= Ps[s[3]].x || ccw(Ps[s[4]], p, Ps[s[3]]) < 0LL))
				l = s[3], r = s[4]; else assert(false);
			while (l < r) {
				size_t m = (l + r) / 2;
				if ((Ps[m+1] - Ps[m]) * (p - Ps[m]) >= 0LL || ccw(Ps[m], Ps[m+1], p) < 0)
						l = m + 1;
				else	r = m;
			}
			rt = l % N;
		}{	// left tangent
			size_t l, r;
			if (p.y >= Ps[s[0]].y && (p.x > Ps[s[1]].x || ccw(Ps[s[1]], p, Ps[s[0]]) < 0LL))
				l = s[0], r = s[1]; else
			if (p.x <= Ps[s[1]].x && (p.y > Ps[s[2]].y || ccw(Ps[s[2]], p, Ps[s[1]]) < 0LL))
				l = s[1], r = s[2]; else
			if (p.y <= Ps[s[2]].y && (p.x < Ps[s[3]].x || ccw(Ps[s[3]], p, Ps[s[2]]) < 0LL))
				l = s[2], r = s[3]; else
			if (p.x >= Ps[s[3]].x && (p.y < Ps[s[4]].y || ccw(Ps[s[4]], p, Ps[s[3]]) < 0LL))
				l = s[3], r = s[4]; else assert(false);
			while (l < r) {
				size_t m = (l + r + 1) / 2;
				if ((Ps[m-1] - Ps[m]) * (p - Ps[m]) >= 0LL || ccw(Ps[m], Ps[m-1], p) > 0)
						r = m - 1;
				else	l = m;
			}
			lt = l % N;
		}
		return {rt, lt};
	}
	P operator[](int i) const { return Ps[i%N]; }
	P &operator[](int i) { return Ps[i%N]; }
};

constexpr int TYPE_ENTRY = 0, TYPE_EXIT = 1;
struct event {
	P d;
	int type, id;
};

bool angcomp(const P &l, const P &r) {
	// First compare by quadrant.
	int ql = quad(l), qr = quad(r);
	if (ql != qr) return ql < qr;
	// ccw?
	int c = ccw(l, r, P{0LL, 0LL});
	return c > 0LL;
}

void solve() {
/*	{
		vector<P> Ps {
			P{2, 0}, P{4, 0},
			P{6, 2}, P{6, 4},
			P{4, 6}, P{2, 6},
			P{0, 4}, P{0, 2},
		};

		ConvexPolygon cp(Ps);
		cerr << "Done computing. Intervals";
		cerr << " [" << cp.s[0] << ", " << cp.s[1] << "),";
		cerr << " [" << cp.s[1] << ", " << cp.s[2] << "),";
		cerr << " [" << cp.s[2] << ", " << cp.s[3] << "),";
		cerr << " [" << cp.s[3] << ", " << cp.s[4] << ")" << endl;

		cerr << "contains (1, 0) " << cp.contains(P{1, 0}) << endl;
		cerr << "contains (2, 0) " << cp.contains(P{2, 0}) << endl;
		cerr << "contains (3, 0) " << cp.contains(P{3, 0}) << endl;
		cerr << "contains (4, 0) " << cp.contains(P{4, 0}) << endl;
		cerr << "contains (5, 0) " << cp.contains(P{5, 0}) << endl;
		cerr << "contains (1, 1) " << cp.contains(P{1, 1}) << endl;
		cerr << "contains (2, 1) " << cp.contains(P{2, 1}) << endl;
		cerr << "contains (1, 6) " << cp.contains(P{1, 6}) << endl;
		cerr << "contains (2, 6) " << cp.contains(P{2, 6}) << endl;
		cerr << "contains (3, 6) " << cp.contains(P{3, 6}) << endl;
		cerr << "contains (4, 6) " << cp.contains(P{4, 6}) << endl;
		cerr << "contains (5, 6) " << cp.contains(P{5, 6}) << endl;
		cerr << "contains (4, 4) " << cp.contains(P{4, 4}) << endl;
		cerr << "contains (0, 4) " << cp.contains(P{0, 4}) << endl;
		cerr << "contains (1, 4) " << cp.contains(P{1, 4}) << endl;
		cerr << "contains (-1, 5) " << cp.contains(P{-1, 5}) << endl;
		cerr << "contains (10, 10) " << cp.contains(P{10, 10}) << endl;
		cerr << "contains (10, 2) " << cp.contains(P{10, 2}) << endl;
		cerr << "contains (3, -1) " << cp.contains(P{3, -1}) << endl;
		cerr << "contains (3, 7) " << cp.contains(P{3, 7}) << endl;

		cerr << "extreme (1, 0) " << cp.extreme(P{1, 0}) << endl;
		cerr << "extreme (1, 1) " << cp.extreme(P{1, 1}) << endl;
		cerr << "extreme (2, 1) " << cp.extreme(P{2, 1}) << endl;
		cerr << "extreme (0, -1) " << cp.extreme(P{0, -1}) << endl;
		cerr << "extreme (-1, -10) " << cp.extreme(P{-1, -10}) << endl;
		cerr << "extreme (-1, 0) " << cp.extreme(P{-1, 0}) << endl;
		cerr << "extreme (-1, -1) " << cp.extreme(P{-1, -1}) << endl;

		cerr << "tangent.f (0, 0) " << cp.tangent(P{0, 0}).first << endl;
		cerr << "tangent.f (0, 1) " << cp.tangent(P{0, 1}).first << endl;
		cerr << "tangent.f (0, -1) " << cp.tangent(P{0, -1}).first << endl;
		cerr << "tangent.f (5, 0) " << cp.tangent(P{5, 0}).first << endl;
		cerr << "tangent.f (6, 0) " << cp.tangent(P{6, 0}).first << endl;
		cerr << "tangent.f (7, 0) " << cp.tangent(P{7, 0}).first << endl;
		cerr << "tangent.f (6, 5) " << cp.tangent(P{6, 5}).first << endl;
		cerr << "tangent.f (6, 6) " << cp.tangent(P{6, 6}).first << endl;
		cerr << "tangent.f (6, 7) " << cp.tangent(P{6, 7}).first << endl;
		cerr << "tangent.f (1, 6) " << cp.tangent(P{1, 6}).first << endl;
		cerr << "tangent.f (0, 6) " << cp.tangent(P{0, 6}).first << endl;
		cerr << "tangent.f (-1, 6) " << cp.tangent(P{-1, 6}).first << endl;
		cerr << "tangent.f (3, -1) " << cp.tangent(P{3, -1}).first << endl;
		cerr << "tangent.f (3, -2) " << cp.tangent(P{3, -2}).first << endl;
		cerr << "tangent.f (3, 7) " << cp.tangent(P{3, 7}).first << endl;
		cerr << "tangent.f (3, 8) " << cp.tangent(P{3, 8}).first << endl;
		cerr << "tangent.f (-1, 3) " << cp.tangent(P{-1, 3}).first << endl;
		cerr << "tangent.f (-2, 3) " << cp.tangent(P{-2, 3}).first << endl;
		cerr << "tangent.f (7, 3) " << cp.tangent(P{7, 3}).first << endl;
		cerr << "tangent.f (8, 3) " << cp.tangent(P{8, 3}).first << endl;
	}*/

	int n, ones = 0;
	cin >> n;
	vector<P> Ps[2];
	for (int i = 0, a, b, c; i < n; ++i)
		cin >> a >> b >> c,
		Ps[c].push_back(P{a, b}),
		ones += c;

	// Compute convex hull of Ps[1]
	{
		vector<point> pts;
		for (const P &p : Ps[1]) pts.push_back(point{p.x, p.y});
		ConvexHull ch(pts);
		vector<P> Ps1;
		for (int i : ch.h) Ps1.push_back(Ps[1][i]);
		swap(Ps1, Ps[1]);
	}

	// Hardcode convex hulls of sizes 1 and .. 2 ?
	if (Ps[1].size() == 1) {
		// Ans is number of identical values to Ps[1][0].
		int ans = ones;
		for (const P &p : Ps[0])
			ans += (p == Ps[1][0]);
		cout << (ones == 1 ? 1 : ans) << endl;
		return;
	}
	if (Ps[1].size() == 2) {
		// Ans is number of values on the path between the two.
		int ans = ones;
		for (const P &p : Ps[0])
			ans += (int)on_segment(Ps[1][0], Ps[1][1], p);
		cout << ans << endl;
		return;
	}

	ConvexPolygon cp(Ps[1]);
	Ps[1].clear();

	int internal = 0;
	{
		vector<P> Ps0;
		for (const P &p : Ps[0])
			if (cp.contains(p) >= 0)
				++internal;
			else
				Ps0.push_back(p);
		swap(Ps0, Ps[0]);
	}

	// event { P d; int type; int id; }
	vector<event> evs;
	for (size_t i = 0; i < Ps[0].size(); ++i) {
		const P &p = Ps[0][i];

		// Tangent vectors.
		size_t rt, lt;
		tie(rt, lt) = cp.tangent(p);
		P rtp = cp[rt] - p, ltp = cp[lt] - p;

		// Compute all 4 events.
		evs.push_back(event{rtp, TYPE_ENTRY, (int)(2*i)});
		evs.push_back(event{rtp * (-1), TYPE_ENTRY, (int)(2*i+1)});
		evs.push_back(event{ltp, TYPE_EXIT, (int)(2*i)});
		evs.push_back(event{ltp * (-1), TYPE_EXIT, (int)(2*i+1)});
	}
	sort(evs.begin(), evs.end(), [](const event &l, const event &r) {
		if (angcomp(l.d, r.d)) return true;
		if (angcomp(r.d, l.d)) return false;
		return l.type < r.type;
	});

	// Do one cycle to get the correct count.
	int covered = 0;
	vector<int> have(2*Ps[0].size(), 0);
	for (size_t l = 0, r = 0; l < evs.size(); l = r) {
		while (r < evs.size() && evs[l].d == evs[r].d) ++r;

		// [l, r) have the same tangent, batch process.) entries, [m, r) exits
		for (size_t i = l; i < r; ++i) {
			if (evs[i].type == TYPE_ENTRY) {
				if (!have[evs[i].id]) ++covered;
				have[evs[i].id] = 1;
			} else {
				if (have[evs[i].id]) --covered;
				have[evs[i].id] = 0;
			}
		}
	}

	// Get answer.
	int ans = (evs.size() > 0 ? 1e9 : 0);
	for (size_t l = 0, r = 0; l < evs.size(); l = r) {
		ans = min(ans, covered);

		while (r < evs.size() && evs[l].d == evs[r].d) ++r;

		// [l, r) have the same tangent, batch process.) entries, [m, r) exits
		for (size_t i = l; i < r; ++i) {
			if (evs[i].type == TYPE_ENTRY) {
				if (!have[evs[i].id]) ++covered;
				have[evs[i].id] = 1;
			} else {
				if (have[evs[i].id]) --covered;
				have[evs[i].id] = 0;
			}
		}

		ans = min(ans, covered);
	}

	cout << ones + internal + ans << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout << fixed << setprecision(12);
	
	solve();
	
	return 0;
}
