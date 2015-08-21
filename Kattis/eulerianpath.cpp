#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

void euler_circuit(vector< vector<int> > &e, int start, vector<int> &o) {
	stack<int> st;
	st.push(start);
	while (!st.empty()) {
		int u = st.top();
		if (e[u].empty()) {
			o.push_back(u);
			st.pop();
		} else {
			st.push(e[u].back());
			e[u].pop_back();
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	while (true) {
		int n, m;
		cin >> n >> m;
		if (n == 0 && m == 0) break;
		
		vector<vector<int> > e(n, vector<int>());
		vector<int> indeg(n, 0), outdeg(n, 0);
		for (int i = 0; i < m; ++i) {
			int u, v;
			cin >> u >> v;
			e[u].push_back(v);
			outdeg[u]++;
			indeg[v]++;
		}

		bool exists = true, om = false, im = false;
		int start = 0;
		for (int i = 0; i < n; ++i) {
			if (indeg[i] == outdeg[i]) continue;
			else if (indeg[i] + 1 == outdeg[i]) {
				if (om) exists = false;
				om = true;
				start = i;
			} else if (indeg[i] == outdeg[i] + 1) {
				if (im) exists = false;
				im = true;
			} else exists = false;
		}
		if (!om)
			while (outdeg[start] == 0)
				start++;

		vector<int> o;
		euler_circuit(e, start, o);
		if (o.size() != m + 1 || !exists)
			cout << "Impossible\n";
		else {
			for (int i = o.size() - 1; i >= 0; --i)
				cout << o[i] << " \n"[i == 0];
		}
	}
	cout << flush;
	
	return 0;
}
