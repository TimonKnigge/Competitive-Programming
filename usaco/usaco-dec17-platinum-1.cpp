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

struct SuffixArray {
	string s;
	int n;
	vvi P;
	SuffixArray(string &_s) : s(_s), n(_s.length()) { construct(); }
	void construct() {
		P.push_back(vi(n, 0));
		compress();
		vi occ(n + 1, 0), s1(n, 0), s2(n, 0);
		for (int k = 1, cnt = 1; cnt / 2 < n; ++k, cnt *= 2) {
			P.push_back(vi(n, 0));
			fill(occ.begin(), occ.end(), 0);
			for (int i = 0; i < n; ++i)
				occ[i+cnt<n ? P[k-1][i+cnt]+1 : 0]++;
			partial_sum(occ.begin(), occ.end(), occ.begin());
			for (int i = n - 1; i >= 0; --i)
				s1[--occ[i+cnt<n ? P[k-1][i+cnt]+1 : 0]] = i;
			fill(occ.begin(), occ.end(), 0);
			for (int i = 0; i < n; ++i)
				occ[P[k-1][s1[i]]]++;
			partial_sum(occ.begin(), occ.end(), occ.begin());
			for (int i = n - 1; i >= 0; --i)
				s2[--occ[P[k-1][s1[i]]]] = s1[i];
			for (int i = 1; i < n; ++i) {
				P[k][s2[i]] = same(s2[i], s2[i - 1], k, cnt) 
					? P[k][s2[i - 1]] : i;
			}
		}
	}
	bool same(int i, int j, int k, int l) {
		return P[k - 1][i] == P[k - 1][j]
			&& (i + l < n ? P[k - 1][i + l] : -1)
			== (j + l < n ? P[k - 1][j + l] : -1);
	}
	void compress() {
		vi cnt(256, 0);
		for (int i = 0; i < n; ++i) cnt[s[i]]++;
		for (int i = 0, mp = 0; i < 256; ++i)
			if (cnt[i] > 0) cnt[i] = mp++;
		for (int i = 0; i < n; ++i) P[0][i] = cnt[s[i]];
	}
	vi &get_array() { return P.back(); }
	int lcp(int x, int y) {
		int ret = 0;
		if (x == y) return n - x;
		for (int k = P.size() - 1; k >= 0 && x < n && y < n; --k)
			if (P[k][x] == P[k][y]) {
				x += 1 << k;
				y += 1 << k;
				ret += 1 << k;
			}
		return ret;
	}
};

size_t owner(size_t pos, const vector<size_t> &start) {
	size_t l = 0, r = start.size();
	while (l < r) {
		size_t m = (l + r + 1) / 2;
		if (start[m] <= pos)
			l = m;
		else
			r = m - 1;
	}
	return l;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	ifstream fin("standingout.in");
	ofstream fout("standingout.out");
	
	int n;
	fin >> n;
	vector<size_t> start;
	string S;
	for (int i = 0; i < n; ++i) {
		string T;
		fin >> T;
		start.push_back(S.size());
		S += T + "$";
	}

	SuffixArray sa(S);
	vi &a = sa.get_array(), ia(a.size());
	for (size_t i = 0; i < a.size(); ++i)
		ia[a[i]] = i;

	vi fi(a.size(), (int)a.size());
	size_t lowner = owner(ia.back(), start);
	for (int i = (int)a.size() - 2; i >= 0; --i) {
		size_t nowner = owner(ia[i], start);
		if (nowner == lowner)
			fi[i] = fi[i+1];
		else
			fi[i] = i+1;
		lowner = nowner;
	}
/*
	for (size_t i = 0; i < ia.size(); ++i) {
		cerr << i;
		cerr << "\t" << owner(ia[i], start) << '\t' << fi[i] << '\t';
		for (size_t j = ia[i]; j < S.size(); ++j) cerr << S[j];
		cerr << endl;
	}
*/
	for (size_t i = 0; i < start.size(); ++i) {
		size_t s = start[i], t = (i + 1 < start.size() 
									? start[i + 1] : S.size());
		size_t ans = 0;
//		cerr << "Cow "<< i << " in [" << s << "," << t << ")" << endl;
		// We are considering string i, located in S[s, t)
		for (size_t j = s; j < t; ++j) {
			// We are now consdiering suffix S[j, t)
			int len = t - j - 1, pos = a[j];
//			cerr << " suffix of length " << len << " at position " << pos << endl;
			int shareup = (pos > 0 ? sa.lcp(ia[pos-1], j) : 0);
			int sharedo = (fi[pos] < a.size() ? sa.lcp(ia[fi[pos]], ia[pos]) : 0);
//			cerr << " su = " << shareup << ", sd = " << sharedo << endl;
			ans += max(0, len - max(shareup, sharedo));
		}
		fout << ans << endl;
	}
	
	return 0;
}
