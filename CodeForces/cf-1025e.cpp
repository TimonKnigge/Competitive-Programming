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

template<class T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<class TIn, class TOut = null_type>
using order_tree = tree<TIn, TOut, less<TIn>, rb_tree_tag,
	tree_order_statistics_node_update>;

constexpr int INF = 2000000010;
constexpr ll LLINF = 9000000000000000010LL;

struct X {
	int x1=0, y1=0, x2=0, y2=0;
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int m, n;
	cin >> n >> m;
	vector<X> is(m);
	for (int i = 0; i < m; ++i)
		cin >> is[i].x1 >> is[i].y1;
	for (int i = 0; i < m; ++i)
		cin >> is[i].x2 >> is[i].y2;

	vector<X> moves;

	// Move all to unique xs.
	sort(is.begin(), is.end(), [](const X &l, const X &r) {
		return l.x1<r.x1;
	});
	// Move left while possible.
	for (int i = 0; i < m; ++i) {
		while (is[i].x1 > i+1 && (i == 0 || is[i-1].x1 + 1 < is[i].x1)) {
			moves.push_back({is[i].x1, is[i].y1, is[i].x1-1, is[i].y1});
			is[i].x1 -= 1;
		}
	}
	// Now move right in reverse.
	for (int i = m-1; i >= 0; --i) {
		while (is[i].x1 < i+1) {
			moves.push_back({is[i].x1, is[i].y1, is[i].x1+1, is[i].y1});
			is[i].x1 += 1;
		}
	}
	// And for y.
	sort(is.begin(), is.end(), [](const X &l, const X &r) {
		return l.y1<r.y1;
	});
	// Move up while possible.
	for (int i = 0; i < m; ++i) {
		while (is[i].y1 > i+1 && (i == 0 || is[i-1].y1 + 1 < is[i].y1)) {
			moves.push_back({is[i].x1, is[i].y1, is[i].x1, is[i].y1-1});
			is[i].y1 -= 1;
		}
	}
	// Now move right in reverse.
	for (int i = m-1; i >= 0; --i) {
		while (is[i].y1 < i+1) {
			moves.push_back({is[i].x1, is[i].y1, is[i].x1, is[i].y1+1});
			is[i].y1 += 1;
		}
	}

	// All in distinct x/y now.
	// Now all sort relative to x2/y2, similar to above.
	sort(is.begin(), is.end(), [](const X &l, const X &r) {
		return l.x2 < r.x2;
	});
	for (int i = 0; i < m; ++i) {
		while (is[i].x1 < i+1) {
			moves.push_back({is[i].x1, is[i].y1, is[i].x1+1, is[i].y1});
			is[i].x1 += 1;
		}
		while (is[i].x1 > i+1) {
			moves.push_back({is[i].x1, is[i].y1, is[i].x1-1, is[i].y1});
			is[i].x1 -= 1;
		}
	}
	sort(is.begin(), is.end(), [](const X &l, const X &r) {
		return l.y2 < r.y2;
	});
	for (int i = 0; i < m; ++i) {
		while (is[i].y1 < i+1) {
			moves.push_back({is[i].x1, is[i].y1, is[i].x1, is[i].y1+1});
			is[i].y1 += 1;
		}
		while (is[i].y1 > i+1) {
			moves.push_back({is[i].x1, is[i].y1, is[i].x1, is[i].y1-1});
			is[i].y1 -= 1;
		}
	}

	// Solve xs: move freely.
	sort(is.begin(), is.end(), [](const X &l, const X &r) {
		return l.x2 < r.x2;
	});
	for (int i = 0; i < m; ++i) {
		while (is[i].x1 < is[i].x2) {
			moves.push_back({is[i].x1, is[i].y1, is[i].x1+1, is[i].y1});
			is[i].x1 += 1;
		}
		while (is[i].x1 > is[i].x2) {
			moves.push_back({is[i].x1, is[i].y1, is[i].x1-1, is[i].y1});
			is[i].x1 -= 1;
		}
	}

	// ys: move while possible.
	sort(is.begin(), is.end(), [](const X &l, const X &r) {
		if (l.y2 != r.y2) return l.y2 < r.y2;
		else return l.x2 < r.x2;
	});
	while (true) {
		bool move = false;
		for (int i = 0; i < m; ++i) {
			// We need to adjust y. Do if possible.
			if (is[i].y1 < is[i].y2 && (i + 1 == m ||
					(is[i].y1+1 != is[i+1].y1 || is[i].x1 != is[i+1].x1))) {
				moves.push_back({is[i].x1, is[i].y1, is[i].x1, is[i].y1+1});
				is[i].y1 += 1;
				move = true;
			}
			if (is[i].y1 > is[i].y2 && (i == 0 || 
					(is[i].y1-1 != is[i-1].y1 || is[i].x1 != is[i-1].x1))) {
				moves.push_back({is[i].x1, is[i].y1, is[i].x1, is[i].y1-1});
				is[i].y1 -= 1;
				move = true;
			}
		}
		if (!move) break;
	}

	cout << moves.size() << endl;
	for (const X &x : moves)
		cout << x.x1 << ' ' << x.y1 << ' ' << x.x2 << ' ' << x.y2 << '\n';

	return 0;
}
