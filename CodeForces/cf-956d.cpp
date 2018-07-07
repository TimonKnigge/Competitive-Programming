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

struct F {
	ll a, b;
	F(ll _a, ll _b) : a(abs(_a)), b(abs(_b))  { }
	friend bool operator<(const F &l, const F &r) {
		return l.a * r.b < r.a * l.b;
	}
	friend bool operator>(const F &l, const F &r) {
		return l.a * r.b > r.a * l.b;
	}
	friend bool operator==(const F &l, const F &r) {
		return l.a * r.b == r.a * l.b;
	}
	friend bool operator!=(const F &l, const F &r) {
		return l.a * r.b != r.a * l.b;
	}
};
struct I { F l, r; };

ll count3(vector<pair<F, int>> &evs) {
	sort(evs.begin(), evs.end());
	ll ans = 0LL, closes = 0LL;
	for (auto &ev : evs) {
//		cerr << ' ' << ev.first.a << '/' << ev.first.b << ' ' << ev.second << endl;
		if (ev.second == 0) ans += closes;
		if (ev.second == 1) closes++;
	}
//	cerr << "Returning " << ans << " (" << closes << " found)" << endl;
	return ans;
}

ll count2(vector<I> &l, vector<I> &r) {
	vector<pair<F, int>> t1, t2;
	for (int i = 0; i < (int)l.size(); ++i)
		t1.push_back({l[i].l, 0}),
		t2.push_back({l[i].r, 1});
	for (int i = 0; i < (int)r.size(); ++i)
		t2.push_back({r[i].l, 0}),
		t1.push_back({r[i].r, 1});
//	cerr << l.size() << " vs " << r.size() << endl;
	return ll(l.size()) * ll(r.size()) - count3(t1) - count3(t2);
}

ll count1(vector<I> &ivs) {
	vector<pair<F, pair<int, int>>> evs;
	for (int i = 0; i < (int)ivs.size(); ++i)
		evs.push_back({ivs[i].l, {0, i}}),
		evs.push_back({ivs[i].r, {1, i}});
	sort(evs.begin(), evs.end(),
		 [&ivs](const pair<F, pair<int, int>> &l,
				const pair<F, pair<int, int>> &r) {
			if (l.first != r.first) return l.first < r.first;
			if (l.second.first != r.second.first) return l.second.first < r.second.first;
			return ivs[l.second.second].l > ivs[r.second.second].l;
		});

	ll ans = 0LL;
	
	order_tree<pair<F, int>> sts;
	for (int l = 0, r = 0; l < (int)evs.size(); l = r) {
		while (r < (int)evs.size() && evs[l].first == evs[r].first) ++r;

		// Add intervals
		for (int i = l; i < r; ++i) {
			if (evs[i].second.first != 0) continue;
			sts.insert({evs[i].first, evs[i].second.second});
		}

		// Count containment
		for (int i = l; i < r; ++i) {
			if (evs[i].second.first != 1) continue;
			ans += sts.order_of_key({ivs[evs[i].second.second].l, INF}) - 1;
			sts.erase(sts.find({ivs[evs[i].second.second].l, evs[i].second.second}));
		}

	}

//	cerr << "Returning " << ans << endl;
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, w;
	cin >> n >> w;

	vii pos, neg;
	for (int i = 0; i < n; ++i) {
		int x, v;
		cin >> x >> v;
		if (x < 0)
			pos.push_back({x, v});
		else
			neg.push_back({x, v});
	}

	vector<I> pi, ni;
	for (ii xv : pos) {
		ll x = xv.first, v = xv.second;
		pi.push_back(I{F{-x, v+w}, F{-x, v-w}});
	}
	for (ii xv : neg) {
		ll x = xv.first, v = xv.second;
		ni.push_back(I{F{-x, v-w}, F{-x, v+w}});
	}

	ll ans = count1(pi) + count1(ni) + count2(pi, ni);
	cout << ans << endl;
	
	return 0;
}
