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

template <class T>
struct ConvexHullSet {
	struct Line {
		T a, b; mutable ld x; bool type;
		bool operator<(const Line& rhs) const {
			return type || rhs.type ? x < rhs.x : a < rhs.a;
		}
		ld intersect(const Line &rhs) const {
			return ld(b - rhs.b) / ld(rhs.a - a);
		}
	};
	static constexpr ld MAX = std::numeric_limits<T>::max() / 10;
	static constexpr ld MIN = std::numeric_limits<T>::min() / 10;
	set<Line> lines;
	void adjust(typename set<ConvexHullSet<T>::Line>::iterator it) {
		if (it != lines.begin()) {
			auto pit = prev(it);
			pit->x = it != lines.end() ? pit->intersect(*it) : MAX;
		}
	}
	bool empty() { return lines.empty(); }
	T query(T x) {
		auto it = lines.lower_bound(Line{T(0), T(0), ld(x), true});
		return it != lines.end() ? it->a * x + it->b : MIN;
	}
	void insert(T a, T b) {
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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N;
	cin >> N;
	vi a(N, 0LL), d(N, 0LL);
	
	ConvexHullSet<ll> chs;
	chs.insert(0LL, 0LL);
	for (int i = 0; i < N; ++i) {
		ll a, d;
		cin >> a >> d;
		ll sz = chs.query(i) + a;
		chs.insert(-d, sz + i * d);
	}
	cout << chs.query(N) << endl;
	
	return 0;
}
