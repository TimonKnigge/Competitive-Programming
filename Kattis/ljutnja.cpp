#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef unsigned long long ull;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	ull M, s; int n;
	cin >> M >> n;
	vector<ull> v(n, 0);
	for (int i = 0; i < n; ++i) {
		cin >> v[i];
		s += v[i];
	}
	
	sort(v.begin(), v.end());
	
	ull l = 0, r = 2e9;
	while (l < r) {
		ull m = (l + r) / 2;
		// Can we leave each child with at most m candies missing?
		ull cost = 0;
		for (int i = 0; i < n; ++i) {
			if (v[i] > m) cost += v[i] - m;
			if (cost > M) break;
		}
		if (cost > M) l = m + 1;
		else r = m;
	}

	for (int i = 0; i < n; ++i) {
		if (v[i] > l) {
			M -= (v[i] - l);
			v[i] = l;
		}
	}

	ull ans = 0;
	for (int i = n - 1; i >= 0; --i) {
		if (M > 0) {
			M--;
			v[i]--;
		}
		ans += v[i] * v[i];
	}

	cout << ans << endl;
	
	return 0;
}
