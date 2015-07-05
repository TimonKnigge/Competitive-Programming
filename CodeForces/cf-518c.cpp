#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {

	ios::sync_with_stdio(false);

	int n, m, k;
	cin >> n >> m >> k;

	// Take input
	vector<int> pos(n), rank(n);
	for (int i = 0; i < n; ++i) {
		int v; cin >> v; v--;
		pos[i] = v;
		rank[v] = i;
	}

	// Process queries
	long long swps = 0;
	for (int i = 0; i < m; ++i) {
		int lnch; cin >> lnch; lnch--;
		int ps = rank[lnch];
		swps += 1LL + ps / k;

		// Move the switched app forward
		if (ps > 0) {
			swap(pos[ps - 1], pos[ps]);
			rank[pos[ps - 1]] = ps - 1;
			rank[pos[ps]] = ps;
		}
	}

	cout << swps << endl;
	return 0;
}