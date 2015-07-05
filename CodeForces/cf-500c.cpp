#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {

	int n, m;
	cin >> n >> m;
	
	// Read input
	vector<int> w(n);
	for (int i = 0; i < n; ++i) cin >> w[i];

	vector< pair<int, int> > pos(n);
	for (int i = 0; i < n; ++i)
		pos[i] = pair<int, int>(max(m, n) + 1, i);

	vector<int> ra(m);
	for (int i = 0; i < m; ++i) {
		cin >> ra[i];
		ra[i]--;
		pos[ra[i]] = pair<int, int>(min(pos[ra[i]].first, i), ra[i]);
	}

	// Rearrange books to reflect the reading order
	sort(pos.begin(), pos.end());
	vector<int> fbooks(n);
	for (int i = 0; i < n; ++i) fbooks[i] = pos[i].second;
	
	long weight = 0;
	for (int i = 0; i < m; ++i) {
		// We will read book ra[i]
		auto it = fbooks.begin();
		for (it; it != fbooks.end(); ++it) {
			if (*it == ra[i]) break;
			weight += w[*it];
		}
		fbooks.erase(it);
		fbooks.insert(fbooks.begin(), ra[i]);
	}

	cout << weight << endl;

	return 0;
}