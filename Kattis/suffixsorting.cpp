#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

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
			for (int i = 0; i <= n; ++i) occ[i] = 0;
			for (int i = 0; i < n; ++i)
				occ[i+cnt<n?P[k-1][i+cnt]+1:0]++;
			for (int i = 0, sum = 0, t; i <= n; ++i) {
				t = occ[i];
				occ[i] = sum;
				sum += t;
			}
			for (int i = 0; i < n; ++i)
				s1[occ[i+cnt<n?P[k-1][i+cnt]+1:0]++] = i;
			for (int i = 0; i <= n; ++i) occ[i] = 0;
			for (int i = 0; i < n; ++i)
				occ[P[k-1][s1[i]]]++;
			for (int i = 0, sum = 0, t; i <= n; ++i) {
				t = occ[i];
				occ[i] = sum;
				sum += t;
			}
			for (int i = 0; i < n; ++i)
				s2[occ[P[k-1][s1[i]]]++] = s1[i];
			for (int i = 0, p1 = -3, p2 = -3; i < n; ++i) {
				P[k][s2[i]] = (P[k-1][s2[i]] != p1 || (s2[i]+cnt<n?P[k-1][s2[i]+cnt]:-1) != p2) ? i : P[k][s2[i - 1]];
				p1 = P[k-1][s2[i]];
				p2 = s2[i]+cnt<n?P[k-1][s2[i]+cnt]:-1;
			}
		}
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
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	string s;
	while (getline(cin, s)) {
		SuffixArray sa(s);
		vector<int> inv(s.length(), -1), &arr = sa.get_array();
		for (int i = 0; i < s.length(); ++i)
			inv[arr[i]] = i;
		int q;
		cin >> q;
		for (int c = 0; c < q; ++c) {
			int x;
			cin >> x;
			cout << inv[x] << ' ';
		}
		cout << endl;
		getline(cin, s);
	}
	
	return 0;
}

