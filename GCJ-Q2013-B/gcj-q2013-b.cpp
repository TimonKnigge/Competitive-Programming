#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main(){

	int T;
	cin >> T;
	for (int t = 1; t <= T; t++){

		int N, M;
		cin >> N >> M;

		vector<vector<int>> board(N);
		vector<int> rmax(N), cmax(M); // Highest value in row i / column j.
		fill(rmax.begin(), rmax.end(), -1);
		fill(cmax.begin(), cmax.end(), -1);

		int val;
		for (int i = 0; i < N; i++){
			board[i] = vector<int>(M);
			for (int j = 0; j < M; j++){
				// Add to board and update the maximum of the row, column.

				cin >> val;
				board[i][j] = val;

				rmax[i] = max(rmax[i], val);
				cmax[j] = max(cmax[j], val);
			}
		}

		// We can mow the lawn in the given pattern iff each number
		// is either the maximum of its row or the maximum of its column.
		bool canDo = true;
		for (int i = 0; i < N; i++){
			for (int j = 0; j < M; j++){
				canDo = canDo && ((board[i][j] == rmax[i])
					|| (board[i][j] == cmax[j]));

				if (!canDo)
					break;
			}
			if (!canDo)
				break;
		}

		cout << "Case #" << t << ": " << (canDo ? "YES" : "NO") << endl;
	}

	return 0;
}