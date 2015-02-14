#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <math.h>
#include <algorithm>

using namespace std;

typedef long double ld;

vector<ld> harmonic(500001, 0);
void precompute_harmonic() {
	for (int i = 1; i <= 500000; ++i) {
		harmonic[i] = harmonic[i - 1] + 1 / ((ld)i);
	}
}

bool is_vowel(char c) {
	return (c == 'I' || c == 'E' || c == 'A' || c == 'O'
		|| c == 'U' || c == 'Y');
}

int main() {

	string inp;
	cin >> inp;
	precompute_harmonic();

	ld sum = 0.0, add = 0.0;
	string::iterator it; int i = 1;
	for (it = inp.begin(); it < inp.end(); ++it, ++i) {
		if (is_vowel(*it)) {
			int dl = i, dr = inp.length() - i + 1;
			int m = min(dl, dr), M = max(dl, dr);
			add = 0.0;

			// Sum up all sizes where both borders are irrelevant
			add += (ld)m;

			// Sum up all sizes where one border is relevant
			if (m + 1 <= M)
				add += m * (harmonic[M] - harmonic[m]);

			// Sum up all sizes where both borders are relevant
			if (M + 1 <= inp.length())
				add += (inp.length() + 1) * (harmonic[inp.length()] - harmonic[M])
				- (inp.length() - M);

			sum += add;
		}
	}

	cout << setprecision(8) << sum << endl;
	return 0;
}