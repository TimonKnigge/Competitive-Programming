#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int lis(vector<int> &a) {
	set<int> st;
	typename set<int>::iterator it;
	for (int i = 0; i < a.size(); ++i) {
		it = st.lower_bound(a[i]);
		if (it != st.end()) st.erase(it);
		st.insert(a[i]);
	}
	return st.size();
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int T;
	cin >> T;
	for (int t = 1; t <= T; ++t) {
		cout <<  "Case " << t << ": ";
		
		int n, p, q;
		cin >> n >> p >> q;
		vector<vector<int> > board(n, vector<int>(n, -1));
		for (int i = 0; i < p + 1; ++i) {
			int x;
			cin >> x;
			x--;
			board[x / n][x % n] = i;
		}

		vector<int> pseq;
		for (int i = 0; i < q + 1; ++i) {
			int x;
			cin >> x;
			x--;
			if (board[x / n][x % n] != -1)
				pseq.push_back(board[x / n][x % n]);
		}

		cout << lis(pseq) << '\n';
	}
	cout << flush;
	return 0;
}
