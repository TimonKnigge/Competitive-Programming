#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

typedef vector<int> vi;
typedef long long ll;

ll L, d[14][14];
vi leftroute, rightroute;

inline bool bit_is_set(int v, int p) {
	return ((v >> p) & 1) == 1;
}

int main() {
	ios::sync_with_stdio(false);

	// Read input
	int n;
	cin >> n >> L;
	for (int j = 0; j < n; ++j) {
		for (int i = 0; i < n; ++i) {
			cin >> d[i][j];
		}
	}

	int half = (n - 1) / 2, otherhalf = n - 2 - half;
	leftroute.assign(half, 0);
	rightroute.assign(otherhalf, 0);
	unordered_set<ll> found_routes;
	
	// Iterate over midpoints
	bool found = false;
	for (int m = 1; m < n; ++m) {
		if (found) break;

		// Iterate over all distributions of subsets
		int mask = (1 << half) - 1;
		while (!(mask & 1 << (n - 2))) {
			
			// Distribute the subsets over the vectors
			int l = 0, r = 0, p = 0;
			for (int v = 1; v < n; ++v) {
				if (v == m) continue;
				if (bit_is_set(mask, p++))
					leftroute[l++] = v;
				else
					rightroute[r++] = v;
			}

			// Test both routes
			found_routes.clear();

			// left route
			do {
				// Compute length
				ll routelength = d[0][leftroute.empty() ? m : leftroute[0]];
				for (int i = 1; i < half; ++i)
					routelength += d[leftroute[i - 1]][leftroute[i]];
				if (!leftroute.empty())
					routelength += d[leftroute[half - 1]][m];

				// Store
				found_routes.insert(routelength);
			} while (next_permutation(leftroute.begin(), leftroute.end()));

			// right route
			do {
				// Compute length
				ll routelength = d[m][rightroute.empty() ? 0 : rightroute[0]];
				for (int i = 1; i < otherhalf; ++i)
					routelength += d[rightroute[i - 1]][rightroute[i]];
				if (!rightroute.empty())
					routelength += d[rightroute[otherhalf - 1]][0];

				// Is it in the hashmap?
				if (found_routes.count(L - routelength)) {
					// found!
					found = true;
					break;
				}
			} while (next_permutation(rightroute.begin(), rightroute.end()));

			// Next mask:
			if ((mask != 0) && !found) {
				int lo = mask & ~(mask - 1);
				int lz = (mask + lo) & ~mask;
				mask |= lz;
				mask &= ~(lz - 1);
				mask |= (lz / lo / 2) - 1;
			}
			else break;
		}
	}

	cout << (found ? "possible" : "impossible") << endl;
	
	return 0;
}
