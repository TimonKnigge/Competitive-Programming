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
using ii = pair<ll, ll>;
using vi = vector<ll>;
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
	
	int N;
	cin >> N;
	
	string S;
	cin >> S;

	SuffixArray sa(S);
	vi &arr = sa.get_array();
	vi inv(N, 0LL);
	for (int i = 0; i < N; ++i)
		inv[arr[i]] = i;
	
	vi match(N, -1LL), next(N, -1LL);
	stack<int> sta;
	for (int i = 0; i < N; ++i) {
		if (S[i] == '(')
			sta.push(i);
		else if (!sta.empty()) {
			match[sta.top()] = i;
			match[i] = sta.top();
			sta.pop();
		}
	}
	for (int j = N - 1; j >= 0; --j) {
		if (S[j] == ')') continue;
		if (match[j] == -1) {
			continue;
		}
		int n = match[j] + 1;
		if (S[n] == ')' || n >= N)
			next[j] = next[match[j]] = 0LL;
		else	next[j] = next[match[j]] = 1LL + next[n];
	}

	ll ans = 0LL;
//	cerr << "inv[i]\tlcp\tj\tnext[j]\n";
	for (int i = 0; i < N; ++i) {
		// Suffix starting at inv[i];
		int lcp = (i > 0 ? sa.lcp(inv[i-1], inv[i]) : 0);
		if (S[inv[i]] == ')') continue;
		if (match[inv[i]] == -1LL) continue;
		
		int j = inv[i];
		while (j < N && match[j] < inv[i] + lcp
			&& match[j] != -1LL
			&& match[j]+1 < N
			&& S[match[j]+1] == '(') {
			j = match[j]+1;
		}
//		cerr << inv[i] << '\t' << lcp << '\t' << j << '\t' << next[j] << endl;
		if (j < N && match[j] >= inv[i] + lcp) {
			ans += 1LL + next[j];
//			cerr << "Adding " << next[j] << " from " << inv[i] << endl;
		}
	}
	
	cout << ans << endl;
	
	return 0;
}

