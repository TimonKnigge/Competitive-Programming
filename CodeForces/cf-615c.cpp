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

string strrev(string &s) {
	string r = s;
	for (int i = 0; i < int(s.length()) / 2; ++i)
		swap(r[i], r[int(s.length()) - 1 - i]);
	return r;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	string s, t;
	cin >> s >> t;
	string sr = strrev(s);
	string concat = t + '$' + s + '%' + sr;
	
	SuffixArray sa(concat);
	vi &indof = sa.get_array();
	vi byind(indof.size(), 0);
	for (int i = 0; i < int(indof.size()); ++i)
		byind[indof[i]] = i;
	
	// indof[i]: index van de i-e suffix
	// byind[i]: begin van de suffix op plek i
	
	vi shared(concat.size(), 0);
	vi inds(concat.size(), -1);
	vb rev(concat.size(), false);
	shared[0] = shared[1] = -1;
	for (int i = 2; i < int(concat.length()); ++i) {
		int j = byind[i];
		if (j > int(t.length())) {
			// this suffix is part of s or sr
			if (j < t.length() + s.length() + 2) {
				j -= t.length() + 1;
				shared[i] = s.length() - j;
				inds[i] = j;
				rev[i] = false;
			} else {
				j -= t.length() + s.length() + 2;
				shared[i] = s.length() - j;
				inds[i] = j;
				rev[i] = true;
			}
		} else {
			shared[i] = min(shared[i - 1], sa.lcp(byind[i - 1], byind[i]));
			inds[i] = inds[i - 1];
			rev[i] = rev[i - 1];
		}
	}
	for (int i = int(concat.length()) - 2; i >= 2; --i) {
		if (byind[i] > int(t.length())) continue;
		if (shared[i] < min(shared[i+1], sa.lcp(byind[i+1], byind[i]))) {
			shared[i] = min(shared[i+1], sa.lcp(byind[i+1], byind[i]));
			inds[i] = inds[i + 1];
			rev[i] = rev[i + 1];
		}
	}
	
	vector<ll> dp(t.length() + 1, LLINF);
	vi par(t.length() + 1, -1);
	dp[0] = 0LL;
	for (int j = 0; j < int(t.length()); ++j) {
		if (dp[j] == LLINF) continue;
		int i = indof[j];
		if (shared[i] == 0) continue;
		int k = shared[i];
		for (int d = 1; d <= k && j + d <= int(t.length()); ++d) {
			if (dp[j + d] > dp[j] + 1) {
				dp[j + d] = dp[j] + 1;
				par[j + d] = j;
			}
		}
	}
	
	int L = int(t.length());
	if (dp[L] == LLINF) cout << -1 << endl;
	else {
		vii parts;
		while (L > 0) {
			int Ln = par[L];
			int l = inds[indof[Ln]], r;
			if (rev[indof[Ln]]) {
				l = int(s.length()) - l - 1;
				r = l - L + Ln + 1;
			} else {
				r = l + L - Ln - 1;
			}
			parts.push_back({l, r});
			L = Ln;
		}
		cout << int(parts.size())<< endl;
		while (parts.size() > 0) {
			cout << 1+parts.back().first << ' ' << 1+parts.back().second << endl;
			parts.pop_back();
		}
	}
	
	return 0;
}
