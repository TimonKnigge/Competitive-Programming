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
		vector<int> rmax(N), cmax(M);
		fill(rmax.begin(), rmax.end(), -1);
		fill(cmax.begin(), cmax.end(), -1);

		int val;
		for (int i = 0; i < N; i++){
			board[i] = vector<int>(M);
			for (int j = 0; j < M; j++){
				cin >> val;
				board[i][j] = val;

				rmax[i] = max(rmax[i], val);
				cmax[j] = max(cmax[j], val);
			}
		}

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