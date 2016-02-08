#include <iostream> 
#include <cstdio>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <bitset>
#include <numeric>
#include <iterator>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <cassert>

using namespace std;
using ll = long long;
using ld = long double;
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

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


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	string S;
	while (getline(cin, S)) {
		size_t N = S.length();
		if (N == 0) continue;
		S = S + S;
		S.pop_back();
		SuffixArray sa(S);
		
		vi rev(N + N - 1, -1);
		for (size_t i = 0; i < N + N - 1; ++i)
			rev[sa.get_array()[i]] = i;
		for (size_t i = 0; i < N + N - 1; ++i)
			if (rev[i] < N)
				cout << S[rev[i] + N - 1];
		cout << '\n';
	}
	cout << flush;
	
	return 0;
}
