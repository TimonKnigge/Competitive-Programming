#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void Z_algorithm(string &s, int offset, vector<int> &Z) {
	Z.assign(s.length() - offset, -1);
	int L = 0, R = 0, n = s.length() - offset;
	for (int i = 1; i < n; ++i) {
		if (i > R) {
			L = R = i;
			while (R < n && s[R - L+offset] == s[R+offset]) R++;
			Z[i] = R - L; R--;
		} else if (Z[i - L] >= R - i + 1) {
			L = i;
			while (R < n && s[R - L+offset] == s[R+offset]) R++;
			Z[i] = R - L; R--;
		} else Z[i] = Z[i - L];
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	string s;
	cin >> s;
	int n = s.length();
	
	vector<vector<int> > fact(n, vector<int>(n, 1e6));
	for (int i = n - 1; i >= 0; --i) {
		vector<int> Z;
		Z_algorithm(s, i, Z);
		for (int j = i; j < n; ++j) {
			bool m = false;
			int cn = j - i + 1;
			for (int L = 1; L <= cn; ++L) {
				if (cn % L != 0) continue;
				m = true;
				for (int cL = L; m && cL < cn; cL *= 2) {
					m = m && (cL + Z[cL] >= min(2*cL, cn));
				}
				if (m) { 
					fact[i][j] = min(fact[i][j], fact[i][i + L - 1]);				
				}
			}
			for (int k = i + 1; k <= j; ++k)
				if (fact[i][j] > fact[i][k-1] + fact[k][j])
					fact[i][j] = fact[i][k-1] + fact[k][j];
			if (fact[i][j] > 1e5) fact[i][j] = j - i + 1;
		}
	}

//	for (int i = 0; i < n; ++i) {
//		for (int j = 0; j < n; ++j) {
//			if (j < i) cout << ' ';
//			else cout << fact[i][j];
//			cout << ' ';
//		}
//		cout << endl;
//	}
	
	cout << fact[0][n - 1] << endl;
	
	return 0;
}
