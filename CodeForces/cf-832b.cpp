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

constexpr int INF = 2000000000;
constexpr ll LLINF = 9000000000000000000;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	vb g(26, false);
	{
		string S;
		cin >> S;
		for (char c : S) g[c-'a'] = true;
	}
	
	string P;
	cin >> P;
	
	int Q;
	cin >> Q;
	while (Q--) {
		string S;
		cin >> S;
		bool success = true;
		size_t j = 0;
		for (size_t i = 0; success && i < S.length(); ++i) {
			if (j == P.length()) {
				success = false;
			} else if (P[j] == '?') {
				if (g[S[i]-'a']) ++j;
				else success = false;
			} else if (P[j] == '*') {
				++j;
				while (S.length() - i > P.length() - j) {
					success = success && !g[S[i]-'a'];
					++i;
				}
				--i;
			} else {
				success = success && P[j] == S[i];
				++j;
			}
		}
		if (j < P.length() && P[j] == '*') ++j;
		success = success && j == P.length();
		cout << (success ? "YES" : "NO") << endl;
	}
	
	return 0;
}
