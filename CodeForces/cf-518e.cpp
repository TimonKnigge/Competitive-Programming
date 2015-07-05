#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

typedef long long ll;

using namespace std;

int main() {

	ios::sync_with_stdio(false);

	// Read input
	int n, k; cin >> n >> k;
	vector<ll> a(n, 0);
	vector<bool> known(n, true);
	string inp;
	for (int i = 0; i < n; ++i) {
		cin >> inp;
		if (inp[0] == '?') known[i] = false;
		else {
			a[i] = atoi(inp.c_str());
		}
	}

	bool possible = true;
	for (int i = 0; i < k; ++i) {
		int lb = i - k; bool passedunknown = false; ll ukbt = 0;
		for (int j = i; j < n; j += k) {
			if (known[j]) {
				if (passedunknown) {
					// fix between lb and j
					ll MINV = (lb < 0) ? (-1e11 - 1) : a[lb];
					ll MAXV = a[j];

					// Find an appropriate range
					ll vsibt = ukbt;
					ll start = -(vsibt - 1) / 2;
					start = max(start, MINV + 1);
					start = min(start, MAXV - vsibt);
					if (start <= MINV) {
						possible = false;
						break;
					}

					// Fill
					for (int s = lb + k; s < j; s += k) {
						a[s] = start;
						known[s] = true;
						start++;
					}
				}
				passedunknown = false;
				ukbt = 0;
				lb = j;
				if (j >= k) {
					// Verify the given sequence
					if (a[j] <= a[j - k]) {
						possible = false;
						break;
					}
				}
			}
			else {
				passedunknown = true;
				ukbt++;
			}
		}
		if (!possible) break;
		if (passedunknown) {
			// Clean up a trailing sequence
			ll MINV = (lb < 0) ? (-1e11 - 1) : a[lb];
			ll MAXV = 1e11 + 1;
			ll vsibt = ukbt;
			ll start = -(vsibt - 1) / 2;
			start = max(start, MINV + 1);
			start = min(start, MAXV - vsibt);
			if (start <= MINV) {
				possible = false;
				break;
			}

			// Fill
			for (int s = lb + k; s < n; s += k) {
				a[s] = start;
				known[s] = true;
				start++;
			}
		}
	}

	// Do output
	if (possible) {
		cout << a[0];
		for (int i = 1; i < n; ++i) cout << ' ' << a[i];
		cout << endl;
	}
	else cout << "Incorrect sequence" << endl;
	return 0;
}