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

using C = ll;	// could be long long or long double
constexpr C EPS = 0LL;	// change to 0 for C=ll
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
	bool operator!=(const P &r) const { return !(*this==r); }
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

struct ConvexHull {
	size_t n;
	vector<size_t> h, c; // Indices of the hull are in `h`, counter clockwise.
	const vector<P> &p;
	ConvexHull(const vector<P> &_p) : n(_p.size()), c(n), p(_p) { compute_hull(); }
	void compute_hull() {
		std::iota(c.begin(), c.end(), 0);
		std::sort(c.begin(), c.end(), [this](size_t l, size_t r) -> bool {
			return p[l].x != p[r].x ? p[l].x < p[r].x : p[l].y < p[r].y; });
		c.erase(std::unique(c.begin(), c.end(), [this](size_t l, size_t r) {
			return p[l] == p[r]; }), c.end());
		for (size_t s = 1, r = 0; r < 2; ++r, s = h.size()) {
			for (size_t i : c) {
				while (h.size() > s && ccw(p[h.end()[-2]], p[h.end()[-1]], p[i]) <= 0)
					h.pop_back();
				h.push_back(i);
			}
			reverse(c.begin(), c.end());
		}
		if (h.size() > 1) h.pop_back();
	}
	size_t size() const { return h.size(); }
	template <class T, void U(const P&, const P&, const P&, T&)>
	void rotating_calipers(T &ans) {
		if (size() <= 2) U(p[h.front()], p[h.back()], p[h.back()], ans); else
		for (size_t i = 0, j = 1, s = size(); i < 2*s; ++i) {
			while (ccw(p[h[(i+1)%s]] - p[h[i%s]], p[h[(j+1)%s]] - p[h[j]], P{0,0}) >= 0)
				j = (j+1)%s;
			U(p[h[i%s]], p[h[(i+1)%s]], p[h[j]], ans);
		}
	}
};
// Example: furthest points.
void update(const P &p1, const P &p2, const P &o, ll &ans) {
	ans = max(ans, max((p1-o).lensq(), (p2-o).lensq()));
}
constexpr ld LDINF = 1e300;

void solve() {
	int N;
	cin >> N;
	vector<P> pts(N);
	for (P &p : pts) cin >> p.x >> p.y;
	ConvexHull ch(pts);
	ll ans = 0LL;
	ch.rotating_calipers<ll, update>(ans);
	printf("%.14lf\n", sqrt(ans));
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout << fixed << setprecision(12);
	
	solve();
	
	return 0;
}
