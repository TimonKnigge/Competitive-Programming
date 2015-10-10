#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <numeric>

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

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
				occ[i+cnt<n?P[k-1][i+cnt]+1:0]++;
			partial_sum(occ.begin(), occ.end(), occ.begin());
			for (int i = n - 1; i >= 0; --i)
				s1[--occ[i+cnt<n?P[k-1][i+cnt]+1:0]] = i;
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
		for (int i = 0; i < n; ++i)
			P[0][i] = cnt[s[i]];
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
	
	string s;
	cin >> s;
	int N = s.length();
	
	SuffixArray sa(s);
	vi &inv = sa.get_array(), arr(N, 0), lcp(N, 0);
	for (int i = 0; i < N; ++i) {
		arr[inv[i]] = i;
	}
	
	vector<long long> prefix(N, 0);
	prefix[0] = N - arr[0];
	for (int i = 1; i < N; ++i) {
		lcp[i] = sa.lcp(arr[i], arr[i - 1]);
		prefix[i] = prefix[i - 1] + N - arr[i] - lcp[i];
	}
	
	int Q;
	cin >> Q;
	
	while (Q--) {
		int K;
		cin >> K;
		
		int l = 0, r = N - 1;
		while (l < r) {
			int m = (l + r) / 2;
			if (prefix[m] >= K) r = m;
			else l = m + 1;
		}
//		while (l > 0 && prefix[l - 1] > K) l--;
		
		int pos = arr[l];
		int cnt = (l > 0 ? K - prefix[l - 1] : K);
		cout << s.substr(pos, cnt + lcp[l]) << '\n';
	}
	cout << flush;
	
	return 0;
}
