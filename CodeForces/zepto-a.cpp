#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

int main() {
	int n;
	cin >> n;
	vector<bool> p(n, false);
	for (int i = 0; i < n; ++i) {
		char c;
		cin >> c;
		if (c == '*')
			p[i] = true;
	}

	bool good = false;
	for (int i = 0; i < n; ++i) {
		for (int k = 1; k < 100; ++k) {
			bool v = true;
			for (int m = 0; m < 5; ++m) {
				v = v && ((i + k * m < n) && p[i + k * m]);
			}
			good = v || good;
			if (good) break;
		}
		if (good) break;
	}

	cout << (good ? "yes" : "no") << endl;

	return 0;
}