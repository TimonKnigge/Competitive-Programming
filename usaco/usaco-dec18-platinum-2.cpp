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

template <class T>
struct FenwickTree {		// use 1 based indices!!!
	int n; vector<T> tree;
	FenwickTree(int n) : n(n) { tree.assign(n + 1, 0); }
	T query(int l, int r) { return query(r) - query(l - 1); }
	T query(int r) {
		T s = 0;
		for(; r > 0; r -= (r & (-r))) s += tree[r];
		return s;
	}
	void update(int i, T v) {
		for(; i <= n; i += (i & (-i))) tree[i] += v;
	}
};

struct X { ll v; size_t l, r; };
void solve() {
	ifstream fin("itout.in");
	ofstream fout("itout.out");
//	auto &fin = cin;
//	auto &fout = cout;

	int N; ll K;
	fin >> N >> K;

	vi A(N);
	for (ll &a : A) fin >> a;

	vector<vector<X>> lis(1);
	lis[0].push_back(X{A[0], 0, 0});
	for (int i = 1; i < N; ++i) {
		int l = 0, r = (int)lis.size();
		while (l < r) {
			int m = (l + r) / 2;
			if (lis[m].back().v < A[i])
				l = m + 1;
			else
				r = m;
		}
		if (l == (int)lis.size()) lis.emplace_back();
		size_t nl = (l == 0 ? size_t(0) : lis[l-1].size()), nr = nl;
		while (l > 0 && nl > 0 && lis[l-1][nl-1].v < A[i]) --nl;
		lis[l].push_back(X{A[i], nl, nr});
	}
	for (X &x : lis[0]) x.r = 1;

//	cerr << "Results" << endl;
//	for (size_t i = 0; i < lis.size(); ++i) {
//		cerr << ' ' << i << ":" << endl;
//		for (X x : lis[i])
//			cerr << "  (" << x.v << ", [" << x.l << ", " << x.r << "))" << endl;
//	}

	vector<FenwickTree<__int128>> fts;
	for (size_t i = 0; i < lis.size(); ++i) {
		fts.emplace_back(lis[i].size()+3);
	}
	fts.back().update(1, 1);
	for (size_t j = lis.size()-1; j > 0; --j) {
		for (size_t i = 0; i < lis[j].size(); ++i) {
			__int128 pts = fts[j].query(i+1);
			if (pts > K) pts = K+1;
			fts[j-1].update(lis[j][i].l+1,  pts);
			fts[j-1].update(lis[j][i].r+1, -pts);
		}
	}

	vi fseq;
	size_t pid = 0;
	for (size_t i = 0; i < lis.size(); ++i) {
		size_t l = 0;
		while (lis[i][l].r <= pid) ++l;
		size_t r = l;
		while (r < lis[i].size() && lis[i][r].l <= pid) ++r;
//		cerr << i << " -> [" << l << ", " << r << ")" << endl;
		for (size_t j = l; j < r; ++j) {
			__int128 pts = fts[i].query(j+1);
			if (pts >= K) {
				// take lis[i][j]
				fseq.push_back(lis[i][j].v);
				pid = j;
				break;
			} else {
				K -= pts;
			}
		}
	}
	sort(fseq.begin(), fseq.end());

	fout << (N - (int)lis.size()) << endl;
	for (int i = 1, index = 0; i <= N; ++i) {
		if (index < (int)fseq.size() && fseq[index] == i)
			++index;
		else
			fout << i << '\n';
	}
}

int main() {
	ios::sync_with_stdio(false);
	
	solve();
	
	return 0;
}
