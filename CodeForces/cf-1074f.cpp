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

constexpr int BSZ = 700;
constexpr int MS = 4e5+1;
constexpr int S = 2e5;

constexpr int CT_SZ = (S+BSZ-1)/BSZ*MS;
short ct[CT_SZ];

void dfs(int u, int p, const vvi &E, vi &l, vi &r, int &t,
		vector<map<int, int>> &cbyr) {
	l[u] = r[u] = t++;
	for (int v : E[u])
		if (v != p)
			dfs(v, u, E, l, r, t, cbyr),
			r[u] = max(r[u], r[v]),
			cbyr[u][r[u]] = v;
}

//inline void radd(int l, int r, int c, /*vector<short> &ct,*/ vector<int> &val, vector<int> &add) {
inline void radd(int l, int r, int c, short *ct, vector<int> &val, vector<int> &add) {
//	cerr << "Got [" << l << ',' << r << "] += "<< c << endl;
	// Block containing i is i/BSZ
	for (int b = l/BSZ; b <= r/BSZ; ++b) {
		if (l <= b*BSZ && (b+1)*BSZ-1 <= r) {
			add[b] += c;
			continue;
		}

		int _l = max(l, b*BSZ), _r = min(r, (b+1)*BSZ-1);
		int sh = MS * b + S;
		for (int i = _l; i <= _r; ++i)
			ct[sh+val[i]]--, val[i] += c, ct[sh+val[i]]++;
	}
}

int dbelow(int u, int v, const vi &l, const vi &r, const vector<map<int, int>> &cbyr) {
	return cbyr[u].lower_bound(l[v])->second;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n, Q;
	cin >> n >> Q;

	vvi E(n);
	for (int i = 1, u, v; i < n; ++i)
		cin >> u >> v,
		--u, --v,
		E[u].push_back(v),
		E[v].push_back(u);

	vi l(n, -1), r(n, -1);
	vector<map<int, int>> cbyr(n);
	int t = 0, root;
	dfs(root = 0 /*rand() % n*/, -1, E, l, r, t, cbyr);

//	for (int i = 0; i < n; ++i)
//		cerr << i << ":\t" << l[i] << '\t' << r[i] << endl;

	int B = (n+BSZ-1)/BSZ;
//	cerr << "Blocks: " << B << endl;
//	vector<short> ct(B*MS, 0);
	std::fill(ct, ct+CT_SZ, 0);
	vector<int> val(n, 0);
	vector<int> add(n, 0);
	for (int i = 0; i < n; ++i)
		ct[MS * (i / BSZ) + S]++;

	int tot = 0;
	set<pair<int, int>> st;
	for (int q = 0, u, v; q < Q; ++q) {
		cin >> u >> v, --u, --v;
		if (u > v) swap(u, v);
//		cerr << "Q1 is " << u << ' '<< v << endl;

		pair<int, int> e = make_pair(u, v);
		int s = -1;
		auto it = st.find(e);
		if (it == st.end())
			s = 1, st.insert(e);
		else
			s = -1, st.erase(it);
		tot += s;

		if (r[u] < l[v] || r[v] < l[u]) {
//			cerr << "Disj case " << endl;
			// Disjoint subtrees.
			radd(l[u], r[u], s, ct, val, add);
			radd(l[v], r[v], s, ct, val, add);
		} else {
//			cerr << "Anc case"<< endl;
			// u ancestor of v
			if (l[v] < l[u]) swap(u, v);
			int w = dbelow(u, v, l, r, cbyr);

			radd(l[root], r[root], s, ct, val, add);
			radd(l[w], r[w], -s, ct, val, add);
			radd(l[v], r[v], s, ct, val, add);
		}

//		cerr << "Post-val is tot=" << tot << endl;
//		for (int i = 0; i < n; ++i)
//			cerr << ' ' << val[i]+add[i/BSZ];
//		cerr << endl;

		// Compute answer.
		int ans = 0;
		for (int b = 0; b < B; ++b)
			ans += ct[MS * b + S + tot - add[b]];
		cout << ans << '\n';
	}
	
	return 0;
}
