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

void compute_prefix_function(string &w, vi &pi) {
	pi.assign(w.length(), 0);
	int k = pi[0] = -1;

	for (int i = 1; i < w.length(); ++i) {
		while (k >= 0 && w[k + 1] != w[i])
			k = pi[k];
		if (w[k + 1] == w[i]) k++;
		pi[i] = k;
	}
}

void knuth_morris_pratt(string &s, string &w, vi &m) {
	int q = -1; vi pi;
	compute_prefix_function(w, pi);
	for (int i = 0; i < s.length(); ++i) {
		while (q >= 0 && w[q + 1] != s[i]) q = pi[q];
		if (w[q + 1] == s[i]) q++;
		if (q + 1 == w.length()) {
			m.push_back(i - int(w.length()) + 1);
			// Match at position (i - w.length() + 1)
			q = pi[q];
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	string S, P;
	cin >> S >> P;
	
	vi matches;
	knuth_morris_pratt(S, P, matches);
	int L = int(P.length());
	
	int ans = 0;
	if (matches.size() > 0) {
		int last = -1;
		for (size_t i = 0; i < matches.size(); ++i) {
			if (last < matches[i]) {
				last = matches[i] + L - 1;
				++ans;
			}
		}
	}
	
	cout << ans << endl;
	
	return 0;
}
