#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int n;
	cin >> n;
	vector<pair<pair<int, int>, int>> sr;
	for (int i = 0; i < n; ++i) {
		int s, r;
		cin >> s >> r;
		sr.push_back({{s, r}, i});
	}
	sort (sr.begin(), sr.end());
	int M = -1, Mf = -1;
	vector<int> ans;
	for (int j = n - 1; j >= 0; --j) {
		if (M < sr[j].first.second || (Mf == sr[j].first.first && M == sr[j].first.second))
			ans.push_back(sr[j].second + 1);
		if (M < sr[j].first.second) {
			M = sr[j].first.second;
			Mf = sr[j].first.first;
		}
	}

	sort(ans.begin(), ans.end());
	for (int i = 0; i < ans.size(); ++i) {
		cout << ans[i] << " \n"[i == ans.size() - 1];
	}

	return 0;
}
