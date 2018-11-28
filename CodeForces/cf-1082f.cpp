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

struct iv {
	int l, r, h;
	ll w;
};

struct dominating_set {
	map<ll, ll> m;
	void insert(ll a, ll b) {
		auto it = m.upper_bound(a);
		if (!m.empty() && it != m.begin() && (--it)->second >= b)
			return;
		while (!m.empty()) {
			if ((it = m.lower_bound(a)) != m.end()) {
				if (it->first >= a && it->second <= b)
					m.erase(it); else break;
			} else break;
		}
		m[a] = b;
	}
	ll best_before(ll c) {
		if (m.empty()) return 0LL;
		auto it = m.lower_bound(c);
		if (it == m.begin()) return 0LL;
		else return (--it)->second;
	}
};

void solve() {
	int n, k;
	cin >> n >> k;

	vector<string> no(n);
	vi we(n);
	{
		vector<pair<string, ll>> inp(n);
		for (auto &i : inp) cin >> i.first >> i.second;
		sort(inp.begin(), inp.end());
		for (int i = 0; i < n; ++i)
			tie(no[i], we[i]) = inp[i];
	}

	cerr << "Read IO" << endl;

	vi wp(n);
	wp[0] = we[0];
	for (int i = 1; i < n; ++i) wp[i] = we[i] + wp[i-1];

	vi lcp(n-1, 0LL);
	for (int i = 0; i+1 < n; ++i) {
		size_t j = 0;
		while (j < no[i].length() && j < no[i+1].length()
				&& no[i][j] == no[i+1][j])
			++j;
		lcp[i] = (ll)j;
	}
	vi l(n-1, -1), r(n-1, n-1);
	for (int i = 0; i < n-1; ++i) {
		l[i] = i-1;
		while (l[i] >= 0 && lcp[l[i]] > lcp[i]) l[i] = l[l[i]];
	}
	for (int i = n-2; i >= 0; --i) {
		r[i] = i+1;
		while (r[i] < n-1 && lcp[r[i]] >= lcp[i]) r[i] = r[r[i]];
	}

//	cerr << "Computed l/r" << endl;

	iv ivs[2000];
	for (int i = 0; i < n; ++i)
		ivs[i] = iv{i, i, (int)no[i].length(), we[i]};
	int c = n;
	for (int i = 0; i < n-1; ++i) {
		if (l[i] >= 0 && lcp[l[i]] == lcp[i]) continue;
		int il = l[i]+1;
		int ir = r[i];
		int ih = lcp[i];
		ll iw = wp[ir] - (il>0 ? wp[il-1] : 0LL);
		ivs[c++] = iv{il, ir, ih, iw};
	}
	sort(ivs, ivs+c, [](const iv &l, const iv &r) {
		if (l.l != r.l)
			return l.l < r.l;
		else
			return l.r > r.r;
	});
//	cerr << "Built intervals" << endl;

	vvi dp(k+1, vi(c, LLINF));
	for (int i = c-1; i >= 0; --i) {
		const iv &v = ivs[i];
		ll self = v.w*v.h;
		dp[0][i] = 0LL;
		dp[1][i] = self;
		dominating_set best[11];
		dominating_set bestf[11];
		for (int m = 0; m <= k; ++m)
			best[m].insert(v.l-1, 0LL),
			bestf[m].insert(v.l-1, 0LL);
		for (int j = i+1; j < c; ++j) {
			const iv &w = ivs[j];
//			cerr << "Considering ["<<w.l<<' '<<w.r<<"]"<<endl;
			if (!(v.l<=w.l&&w.r<=v.r)) continue;
			ll del = w.w * -v.h;
//			cerr << "  del = " << del << endl;
			for (int m = 1; m <= k; ++m) {
				for (int o = 1; o < m; ++o) {
					ll ndp = del + dp[o][j] + best[m-o].best_before(w.l);
					best[m].insert(w.r, ndp);
//					cerr << "  best["<<m<<"]+=("<<w.r<<","<<ndp<<")" << endl;
//					cerr << "  best["<<m<<"].size()=="<<best[m].m.size()<<endl;
				}
				for (int o = 1; o <= m; ++o) {
					ll ndp = dp[o][j] + bestf[m-o].best_before(w.l);
					bestf[m].insert(w.r, ndp);
				}
			}
		}
//		cerr << i << ' ' << v.l << ' ' << v.r << endl;
		for (int m = 1; m <= k; ++m) {
			dp[m][i] = max(
				bestf[m].best_before(v.r+1),
				self + best[m].best_before(v.r+1)
			);
//			cerr << ' ' << m << ' ' << dp[m][i] << endl;
//			cerr << ' ' << bestf[m].best_before(v.r+1) << endl;
//			cerr << ' ' << self << "+"<<best[m].best_before(v.r+1) << endl;
		}
	}

	ll ans = 0LL;
	for (int i = 0; i < n; ++i)
		ans += ll(no[i].length()) * we[i];
	ans -= dp[k][0];
	cout << ans << endl;
}
/*
struct iv {
	int l, r, h;
	ll w;
};
*/

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout << fixed << setprecision(12);
	
	solve();
	
	return 0;
}
