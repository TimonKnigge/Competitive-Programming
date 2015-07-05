#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <random>

using namespace std;

#define TRIALS 400

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

bool colinear(ii p1, ii p2, ii p3) {
	return ((p2.first - p1.first) * (p3.second - p1.second) == (p3.first - p1.first) * (p2.second - p1.second));
}

int main() {
	ios::sync_with_stdio(false);

	// Read input
	int n, p;
	cin >> n >> p;
	vii point(n);
	for (int i = 0; i < n; ++i) {
		cin >> point[i].first >> point[i].second;
	}

	// Minimum percentage
	int minper = (int)ceil(n * p / 100.0);

	if (n <= 2) cout << "possible" << endl;
	else {
		// Perform probabilistic trials
		bool found = false;

		for (int k = 0; k < TRIALS && !found; ++k) {
			int p1 = rand() % n,
				p2 = rand() % n;
			if (p1 == p2) continue;

			int c = 0;
			for (int i = 0; i < n; ++i) {
				if (colinear(point[p1], point[p2], point[i]))
					c++;
			}
			
			found = found || (c >= minper);
		}

		cout << (found ? "possible" : "impossible") << endl;
	}

	return 0;
}