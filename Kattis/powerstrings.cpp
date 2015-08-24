#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void Z_algorithm(string &s, vector<int> &Z) {
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
	
	while (true) {
		string s;
		cin >> s;
		if (s == ".") break;
		int n = s.length();

		vector<int> Z;
		Z_algorithm(s, Z);
		
		bool m = false;
		for (int L = 1; L <= n; ++L) {
			if (n % L != 0) continue;
			m = true;
			for (int cL = L; m && cL < n; cL *= 2) {
				m = m && (cL + Z[cL] >= min(2 * cL, n));
			}
			if (m) {
				cout << (n / L) << endl;
				break;
			}
		}
		if (!m) cout << 1 << endl;
	}
	
	return 0;
}
