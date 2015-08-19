#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int T;
	cin >> T;
	for (int t = 1; t <= T; ++t) {
		int n;
		cin >> n;
		vector<vector<ll> > d(n, vector<ll>(n, 0));
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				cin >> d[i][j];
		
		vector<vector<bool> > rb(n, vector<bool>(1 << n, false));
		queue<pair<int, int> > q;
		for (int i = 0; i < n; ++i) {
			ll o = 0;
			for (int j = 0; j < n; ++j)
				o += d[i][j];
			if (o > 0) {
				rb[i][0] = true;
				q.push({i, 0});
//				cout << "rb[" << i << "][" << 0 << "] is reachable: owes " << o << endl;
			}
		}

		vector<bool> can_be_last(n, false);
		if (n == 1) can_be_last[0] = true;
		
//		for (int m = 0; m < (1 << n); ++m) {
		while (!q.empty()) {
			int m = q.front().second, i = q.front().first;
			q.pop();
			vector<ll> owe(n, 0);
			for (int ii = 0, x = 1; ii < n; ++ii, x *= 2) {
				if ((x & m) != 0) continue;
				for (int j = 0, y = 1; j < n; ++j, y *= 2) {
					if ((y & m) != 0) continue;
					owe[ii] += d[ii][j];
				}
			}
//			cout << "Owe: "; for(int i =0;i < n; ++i) cout << owe[i]<<' ';	cout<<endl;
//			for (int i = 0, x = 1; i < n; ++i, x *= 2) {
//				if (!rb[i][m]) continue;
//				if ((x & m) != 0) continue;
			int x = (1 << i);

				for (int j = 0, y = 1; j < n; ++j, y *= 2) {
					if (j == i) continue;
					if ((y & m) != 0) continue;
					if (owe[j] - d[j][i] > 0
						&& !rb[j][m|x]
						) {
						rb[j][m | x] = true;
						q.push({j, m|x});
//						cout << "rb[" << j << "][" << (m|x) << "] is reachable." << endl;
					} else if (owe[j] - d[j][i] == 0) {
						if (__builtin_popcount(m) == n-2)
							can_be_last[j] = true;
					}
				}
//			}
		}
		
		bool pzero = true;
		for (int i = 0; i < n; ++i) {
			if (can_be_last[i]) cout << (i + 1) << ' ';
			pzero = pzero && !can_be_last[i];
		}
		if (pzero) cout << 0;
		cout << endl;
	}
	
	return 0;
}

