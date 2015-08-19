#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

pair<int, int> dfsmax(int u, int p, vector< vector<int> > &ch) {
	if (ch[u].size() == 0) return {1, 1};
	int L = 1e7, L2 = 0, R = 0;
	for (int v : ch[u]) {
		pair<int, int> lr = dfsmax(v, 1 - p, ch);
		R += lr.second;
		L = min(L, lr.second - lr.first);
		L2 += lr.first - 1;
	}
	if (p == 0)
		return {R - L, R};
	else
		return {L2 + 1, R};
}
pair<int, int> dfsmin(int u, int p, vector< vector<int> > &ch) {
	if (ch[u].size() == 0) return {1, 1};
	int L = 0, L2 = 1e7, R = 0;
	for (int v : ch[u]) {
		pair<int, int> lr = dfsmin(v, 1 - p, ch);
		R += lr.second;
		L += lr.first;
		L2 = min(L2, lr.first);
	}
	if (p == 0)
		return {L, R};
	else
		return {L2, R};
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	vector< vector<int> > ch(n, vector<int>());
	for (int i = 0; i < n - 1; ++i) {
		int u, v;
		cin >> u >> v;
		u--; v--;
		ch[u].push_back(v);
	}

	cout << dfsmax(0, 0, ch).first << ' ';
	
	cout << dfsmin(0, 0, ch).first << endl;
	
	
	return 0;
}

