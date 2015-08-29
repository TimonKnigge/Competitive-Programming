#include <iostream>
#include <vector>
#include <bitset>
#include <queue>

using namespace std;

vector<bool> bs(1e9+2, false);

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
//	vector<bool> bs(1e9+2, false);
	
	int T;
	cin >> T;
	for (int t = 1; t <= T; ++t) {
		int n;
		cin >> n;
		if (n == 0) { cout << 0 << '\n'; continue; }
		
		int L = 0;
		queue<int> q;

		for (int r = 0; r < n; ++r) {
			int a;
			cin >> a;
			
			// Adding a might require removing elements:
			if (bs[a]) {
				while (q.front() != a) {
					bs[q.front()] = false;
					q.pop();
				}
				q.pop();
			} else bs[a] = true;
			q.push(a);
			L = max(L, int(q.size()));
		}
		
		while (!q.empty()) { bs[q.front()] = false; q.pop(); }
		
		cout << L << '\n';
	}
	cout << flush;
	
	return 0;
}
