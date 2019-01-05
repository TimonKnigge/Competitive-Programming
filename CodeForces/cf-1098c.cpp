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


void dfs(int u, int p, const vvi &mch, int &nf) {
	if (p>0) cout << p;
	if (p>0 && nf == (int)mch.size()) {
		cout << endl;
	} else if (p>0) {
		cout << ' ';
	}
	int v = nf++;
	for (int j : mch[u]) dfs(j, v, mch, nf);
}

void solve() {
	ll n, s;
	cin >> n >> s;
	if ((n-1) + n > s || n * (n+1) / 2LL < s) {
		cout << "NO" << endl;
		return;
	}

	if (s == n*(n+1)/2) {
		cout << "YES" << endl;
		for (int i = 1; i < n; ++i)
			cout << i << " \n"[i+1==n];
		return;
	}

	int l = 2, r = n-1;
	while (l < r) {
		int m = (l+r) / 2;
		ll ss = 1LL, rem = n-1, pl = 1LL, d = 1LL;
		while (rem > 0) {
			ll v = min(rem, pl *= m);
			rem -= v;
			ss += v*(++d);
		}
		
		if (ss > s)
			l = m+1;
		else
			r = m;
	}

	int B = l;
	cerr << "Branch " << B << endl;

	vi p(n, -1);
	for (int i = n-1; i > 0; --i)
		p[i] = i-1;
	ll ss = 0LL;
	vi sz(n, 0), ch(n, 0);
	for (int i = n-1; i >= 0; --i) {
		sz[i]++;
		ss += sz[i];
		if (p[i] >= 0) sz[p[i]] += sz[i], ch[p[i]]++;
	}

	vi d(n, 1);
	for (int i = 1; i < n; ++i) d[i] = 1+d[p[i]];

	vvi byl(n+1);
	for (int i = 0; i < n; ++i)
		byl[d[i]].push_back(i);

	l = n, r = 0;
	while (ss - s > 0LL) {
//		cerr << "Now " << ss-s << " remains" << endl;
		
		while (byl[l].empty()) --l;

		for (int j : byl[l]) {
			if (ch[j] > 0 || l != d[j]) continue;

			while (byl[r].empty() || ch[byl[r].back()] == B) {
				if (byl[r].empty()) ++r; else byl[r].pop_back();
			}

			if (l-r-1 <= ss-s) {
				ch[p[j]]--;
				d[j] = r+1;
				p[j] = byl[r].back();
				ss -= l-r-1;
				byl[d[j]].push_back(j);
				ch[p[j]]++;
//				cerr << "Moved " << j << " from level " << l << " to " << r+1 << " with parent " << p[j] << endl;
			} else {
				r = (l-1) - (ss-s);
				while (ch[byl[r].back()] == B) byl[r].pop_back();
				p[j] = byl[r].back();
				ss = s;
				d[j] = r+1;
			}
		}
		--l;
	}

	if (s != accumulate(d.begin(), d.end(), 0LL)) {//x != s) {
		cout << "NO" << endl;
	} else {
		cout << "YES" << endl;

		// Relabel.
		vvi mch(n);
		for (int i = 1; i < n; ++i) mch[p[i]].push_back(i);
		int nf = 1;
		dfs(0, -1, mch, nf);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout << fixed << setprecision(12);
	
	solve();
	
	return 0;
}
