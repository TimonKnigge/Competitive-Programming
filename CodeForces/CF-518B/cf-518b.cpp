#include <iostream>
#include <string>
#include <algorithm>
#include <string.h>

using namespace std;

// Map chars to their array index
inline int mp(char c) {
	if (c >= 'a' && c <= 'z')
		return c - 'a';
	else return 26 + (c - 'A');
}

int main() {

	ios::sync_with_stdio(false);

	string s, t;
	cin >> s >> t;

	// Preprocess the t array
	int c[26 * 2];
	memset(c, 0, 26 * 2 * sizeof(int));
	auto _t = t.c_str();
	for (int i = 0; i < t.length(); ++i) {
		c[mp(_t[i])]++;
	}

	// Preprocess the s array
	int r[26 * 2];
	memset(r, 0, 26 * 2 * sizeof(int));
	auto _s = s.c_str();
	for (int i = 0; i < s.length(); ++i) {
		r[mp(_s[i])]++;
	}

	// Match letters
	int yay = 0, whoops = 0;
	for (int i = 0; i < 26; ++i) {
		// Match lowercase with lowercase
		int m = min(c[i], r[i]);
		c[i] -= m; r[i] -= m; yay += m;
		// Match uppercase with uppercase
		m = min(c[i + 26], r[i + 26]);
		c[i + 26] -= m; r[i + 26] -= m; yay += m;
		// Match uppercase with lowercase
		m = min(c[i + 26], r[i]);
		c[i + 26] -= m; r[i] -= m; whoops += m;
		// Match lowercase with uppercase
		m = min(c[i], r[i + 26]);
		c[i] -= m; r[i + 26] -= m; whoops += m;
	}

	cout << yay << ' ' << whoops << endl;
	return 0;
}