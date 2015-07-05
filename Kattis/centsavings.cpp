#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

typedef long long ll;

ll dp1[2000][21],
   dp2[2000][21];

ll fr(ll v) {
	ll d;
	d = v % 10;
	return (v - d + (d >= 5 ? 10 : 0));
}

int main() {

	int n, d;
	cin >> n >> d;

	vector<int> p(n);
	for (int i = 0; i < n; ++i) cin >> p[i];

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j <= d; ++j) {
			if (i == 0) {
				dp2[i][j] = 0;
				if (j == 0)
					dp1[i][j] = p[0];
				else
					dp1[i][j] = 2000000000;
				continue;
			}
			else if (j == 0) {
				dp1[i][j] = p[i] + dp1[i - 1][j];
				dp2[i][j] = dp2[i - 1][j];
			}
			else {
				ll b = 2000000000000,
					b1 = 0, b2 = 0, s = p[i];

				for (int k = i - 1; k >= 0; --k) {
					ll t2 = dp2[k][j - 1] + fr(dp1[k][j - 1]);
					ll t1 = s;
					if (fr(t1) + t2 < b) {
						b = fr(t1) + t2;
						b1 = t1;
						b2 = t2;
					}
					s += p[k];
				}

				dp1[i][j] = b1;
				dp2[i][j] = b2;
			}
		}
	}

	ll m = 100000000;
	for (int i = 0; i <= d; ++i) {
		m = min(m, dp2[n - 1][i] + fr(dp1[n - 1][i]));
	}

	cout << m << endl;
	return 0;
}