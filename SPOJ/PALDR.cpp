#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void manacher(string &s, vector<int> &pal) {
	int n = s.length(), i = 1, l, r;
	pal.assign(2 * n + 1, 0);
	while (i < 2 * n + 1) {
		if (i & 1) {
			if (pal[i] == 0) pal[i] = 1;
		}
		l = i / 2 - pal[i] / 2; r = (i-1) / 2 + pal[i] / 2;
		
		while (l - 1 >= 0 && r + 1 < n && s[l - 1] == s[r + 1]) {
			l--; r++; pal[i] += 2;
		}

		for (l = i - 1, r = i + 1; l >= 0 && r < 2 * n + 1; --l, ++r) {
			if (l <= i - pal[i]) break;
			if (l / 2 - pal[l] / 2 > i / 2 - pal[i] / 2)
				pal[r] = pal[l];
			else {
				if (l >= 0)
					pal[r] = min(pal[l], 
					i + pal[i] - r);
				break;
			}
		}
		i = r;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	string s;
	int k;
	cin >> k >> s;
	
	vector<int> pal;
	manacher(s, pal);
	int M = 0;
	for (size_t i = 0; i < pal.size(); ++i) 
		if (pal[i] >= k && (pal[i] - k) % 2 == 0) M++;
	cout << M << endl;

	return 0;
}
