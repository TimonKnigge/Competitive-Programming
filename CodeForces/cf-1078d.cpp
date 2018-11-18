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

template <class T, const T&(*op)(const T&, const T&)>
struct SegmentTree {
	int n; vector<T> tree; T id;
	SegmentTree(int _n, T _id) : n(_n), tree(2 * n, _id), id(_id) { }
	void update(int i, T val) {
		for (tree[i+n] = val, i = (i+n)/2; i > 0; i /= 2)
			tree[i] = op(tree[2*i], tree[2*i+1]);
	}
	T query(int l, int r) {
		T lhs = T(id), rhs = T(id);
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (  l&1 ) lhs = op(lhs, tree[l++]);
			if (!(r&1)) rhs = op(tree[r--], rhs);
		}
		return op(l == r ? op(lhs, tree[l]) : lhs, rhs);
	}
};

int la(int x, int n) {
	return (x%n+n)%n;
}

void solve() {
	int n;
	cin >> n;
	vi r(n);
	for (ll &v : r) cin >> v;

	if (n == 1) {
		cout << 0 << endl;
		return;
	}

	vector<SegmentTree<ll, std::min>> lhs;
	vector<SegmentTree<ll, std::max>> rhs;
	lhs.emplace_back(n, INF);
	rhs.emplace_back(n,-INF);
	for (int i = 0; i < n; ++i)
		lhs[0].update(i, i-r[i]),
		rhs[0].update(i, i+r[i]);

	for (int k = 1; k < 20; ++k) {
		lhs.emplace_back(n, INF);
		rhs.emplace_back(n,-INF);
		for (int i = 0; i < n; ++i) {
			int fl = lhs[k-1].query(i, i);
			int fr = rhs[k-1].query(i, i);
	//		cerr << k << ' ' << i << " starting with " << fl << ' ' << fr << endl;

			if (fr-fl >= n-1) {
				lhs[k].update(i, i-n);
				rhs[k].update(i, i+n);
				continue;
			}

			int nfl = fl, nfr = fr;
			if (fl >= 0 && fr < n)
				nfl = lhs[k-1].query(fl, fr),
				nfr = rhs[k-1].query(fl, fr);
			else if (fl < 0 && fr < n)
				nfl = min(lhs[k-1].query(0, fr), lhs[k-1].query(la(fl, n), n-1)-n),
				nfr = max(rhs[k-1].query(0, fr), rhs[k-1].query(la(fl, n), n-1)-n);
			else if (fl >= 0 && fr >= n)
				nfl = min(lhs[k-1].query(fl, n-1), lhs[k-1].query(0, fr%n)+n),
				nfr = max(rhs[k-1].query(fl, n-1), rhs[k-1].query(0, fr%n)+n);
			else
				assert(false);

			fl = nfl, fr = nfr;
			lhs[k].update(i, fl);
			rhs[k].update(i, fr);
//			cerr << k << ' ' << i << ' '<< fl << ' '<<fr << endl;
		}
	}

	for (int i = 0; i < n; ++i) {
//		cerr << " now doing "<< i << endl;
		int lmx = i, rmx = i, ans = 0;
		for (int k = 20-1; k >= 0; --k) {
//			cerr << "  jumping from " << k << endl;
//			cerr << "  have  " << lmx << ' '<< rmx << endl;

			int nlmx, nrmx;
			if (lmx >= 0 && rmx < n)
				nlmx = lhs[k].query(lmx, rmx),
				nrmx = rhs[k].query(lmx, rmx);
			else if (lmx < 0 && rmx < n)
				nlmx = min(lhs[k].query(0, rmx), lhs[k].query(la(lmx, n), n-1)-n),
				nrmx = max(rhs[k].query(0, rmx), rhs[k].query(la(lmx, n), n-1)-n);
			else if (lmx >= 0 && rmx >= n)
				nlmx = min(lhs[k].query(lmx, n-1), lhs[k].query(0, rmx%n)+n),
				nrmx = max(rhs[k].query(lmx, n-1), rhs[k].query(0, rmx%n)+n);
			else
				assert(false);

			if (nrmx-nlmx < n-1)
				lmx = nlmx,
				rmx = nrmx,
				ans += (1<<k);
		}
		cout << ans+1 << " \n"[i+1==n];
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout << fixed << setprecision(12);
	
	solve();
	
	return 0;
}
