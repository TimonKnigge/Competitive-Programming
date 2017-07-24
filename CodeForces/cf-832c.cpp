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

constexpr int INF = 2000000000;
constexpr ll LLINF = 9000000000000000000;

struct ConvexHullSet {
	static constexpr ld MAX = std::numeric_limits<ld>::max();
	static constexpr ld DEFAULT = std::numeric_limits<ld>::min();
	struct Line {
		ld a, b; mutable ld x; bool type;
		bool operator<(const Line& rhs) const {
			return type || rhs.type ? x < rhs.x : a < rhs.a;
		}
		ld intersect(const Line &rhs) const {
			return ld(b - rhs.b) / ld(rhs.a - a);
		}
	};
	set<Line> lines;
	ld query(ld x) {
		auto it = lines.lower_bound(Line{0.0, 0.0, x, true});
		return it != lines.end() ? it->a * x + it->b : DEFAULT;
	}
	void adjust(set<Line>::iterator it) {
		if (it != lines.begin()) {
			auto pit = prev(it);
			pit->x = it != lines.end() ? pit->intersect(*it) : MAX;
		}
	}
	void insert(ld a, ld b) {
		Line ln = Line{a, b, 0.0, false};
		auto it = lines.lower_bound(ln);
		if (it != lines.end() && it->a == a) {
			if (it->b >= b) return;
			adjust(it = lines.erase(it));
		}
		ln.x = it != lines.end() ? it->intersect(ln) : MAX;
		while (it != lines.end() && ln.x >= it->x) {
			adjust(it = lines.erase(it));
			ln.x = it != lines.end() ? it->intersect(ln) : MAX;
		}
		while (it != lines.begin()) {
			--it;
			ld nx = it->intersect(ln);
			if (nx >= it->x) return;
			if (it != lines.begin() && prev(it)->x >= nx)
				adjust(it = lines.erase(it));
			else break;
		}
		it = lines.insert(ln).first;
		adjust(it); adjust(next(it));
	}
};

constexpr int L = 0, R = 1000000;

vector<ld> solve(vii &pairs, int s) {
	vector<ld> d(R-L+1, 1e300);
	sort(pairs.begin(), pairs.end());
	ConvexHullSet chs;
	for (int i = 0, p = L; p <= R; ++p) {
		while (i < (int)pairs.size() && pairs[i].first == p) {
			int x = pairs[i].first, v = pairs[i].second;
			ld a = 1.0 / ld(s - v) - ld(v) / (ld(s - v) * ld(s+v));
			ld b = - ld(x) / ld(s - v) + ld(x) / ld(s + v)
				+ ld(v) * ld(x)  / (ld(s - v) * ld(s + v));
			chs.insert(-a, -b);
			++i;
		}
		d[p] = -chs.query(p);
	}
	return d;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, s;
	cin >> n >> s;
	
	vi x(n, 0), v(n, 0), t(n, 0);
	ld lr = 1e300, rr = 1e300;
	int minl = R+1, maxr = L-1;
	for (int i = 0; i < n; ++i) {
		cin >> x[i] >> v[i] >> t[i];
		if (t[i] == 1) {
			lr = min(lr, ld(x[i]) / ld(v[i]));
			if (x[i] < minl) minl = x[i];
		} else {
			rr = min(rr, ld(R - x[i]) / ld(v[i]));
			if (x[i] > maxr) maxr = x[i];
		}
	}
	
	cerr << "lr = " << lr << ", rr = " << rr << endl;
	
	vector<ld> lp, rp;
	{
		vii pairs[2];
		for (int i = 0; i < n; ++i)
			pairs[t[i]-1].push_back({x[i], v[i]});
		for (ii &pr : pairs[1]) pr.first = R-pr.first;
		lp = solve(pairs[0], s);
		rp = solve(pairs[1], s);
		reverse(rp.begin(), rp.end());
	}

	ld ans = max(lr, rr);
	for (int p = L; p <= R; ++p)
		ans = min(ans, max(min(lr, lp[p]), min(rr, rp[p])));
	
	printf("%.10lf\n", double(ans));
	return 0;
}
