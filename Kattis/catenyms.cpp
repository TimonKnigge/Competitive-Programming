#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>

using namespace std;

void solve() {
	int n;
	cin >> n;

	vector<vector<string> > adjs(26, vector<string>());
	vector<int> adj(26, 0);
	vector<int> indeg(26, 0), outdeg(26, 0);
	for (int i = 0; i < n; ++i) {
		string inp;
		cin >> inp;
		adjs[inp[0] - 'a'].push_back(inp);
		adj[inp[0] - 'a']++;
		outdeg[inp[0] - 'a']++;
		indeg[inp[inp.length() - 1] - 'a']++;
	}
	
	int start = 0; bool fi = false, fo = false, pos = true;
	for (int i = 0; i < 26; ++i) {
		if (indeg[i] == outdeg[i]) continue;
		else if (indeg[i] == outdeg[i] + 1) {
			if (fo) pos = false;
			fo = true;
		}
		else if (indeg[i] == outdeg[i] - 1) {
			if (fi) pos = false;
			fi = true;
			start = i;
		} else pos = false;
	}
	if (!fi && !fo)
		while (indeg[start] + outdeg[start] == 0) 
			start++;

	if (!pos) {
		cout << "***" << endl;
		return;
	}

	for (int i = 0; i < 26; ++i)
		sort(adjs[i].begin(), adjs[i].end());
	
	vector<string> ans;
	vector<bool> vis(26, false);
	stack< pair<int, string> > st;
	st.push({start, ""});
	while (!st.empty()) {
		int u = st.top().first, j;
		vis[u] = true;
		if (adj[u] == 0) {
			if (st.top().second != "")
				ans.push_back(st.top().second);
			st.pop();
		} else {
			string s = adjs[u][adjs[u].size() - adj[u]];
			int j = int(s.back() - 'a');
			adj[u]--;
			st.push({j, s});
		}
	}
	
//	cerr << "Done eulering." << endl;

	for (int i = 0; i < 26; ++i) {
		if ((indeg[i] > 0 || outdeg[i] > 0) && !vis[i]) {
			cout << "***" << endl;
			return;
		}
	}
	if (ans.size() != n) {
		cout << "***" << endl;
		return;
	}

	for (int i = 0; i < ans.size() / 2; ++i)
		swap(ans[i], ans[ans.size() - i - 1]);
	for (int i = 0; i < ans.size(); ++i) {
		if (i > 0) cout << '.';
		cout << ans[i];
	}
	cout << endl;
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int T; cin >> T;
	for (int t = 1; t <= T; ++t) {
		solve();
	}
	
	return 0;
}
