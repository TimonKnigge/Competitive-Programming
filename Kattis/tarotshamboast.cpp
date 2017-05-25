#include <bits/stdc++.h>

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

void Z_algorithm(string &s, vi &Z) {
	Z.assign(s.length(), -1);
	int L = 0, R = 0, n = s.length();
	for (int i = 1; i < n; ++i) {
		if (i > R) {
			L = R = i;
			while (R < n && s[R - L] == s[R]) R++;
			Z[i] = R - L; R--;
		} else if (Z[i - L] >= R - i + 1) {
			L = i;
			while (R < n && s[R - L] == s[R]) R++;
			Z[i] = R - L; R--;
		} else Z[i] = Z[i - L];
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, s;
	cin >> n >> s;
	
	vector<string> S(s, "");
	vvi seq(s, vi());
	for (int i = 0; i < s; ++i) {
		cin >> S[i];
		vi Z;
		Z_algorithm(S[i], Z);
		for (size_t j = 1; j < Z.size(); ++j)
			if ((j + (size_t)Z[j]) == Z.size()
				&& j + Z.size() <= (size_t)n)
				seq[i].push_back(j);
		seq[i].resize(S[i].length(), INF);
	}
	
	vi v(s, 0);
	iota(v.begin(), v.end(), 0LL);
	for (int i = (int)S[0].length() - 1; i >= 0; --i) {
		for (int j = 1; j < s; ++j)
			for (int k = j - 1; k >= 0; --k)
				if (seq[v[k + 1]][i] > seq[v[k]][i])
					swap(v[k + 1], v[k]);
				else	break;
	}
	
	for (int i : v) cout << S[i] << endl;
	
	return 0;
}
