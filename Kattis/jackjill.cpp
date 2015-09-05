#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>
#include <cassert>

using namespace std;

#define pos(i, j, n) ((i) * (n) + (j))
#define cpos(pos1, pos2, n) ((pos1) * ((n) * (n)) + (pos2))

inline long double euclid(int x1, int y1, int x2, int y2) {
	return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

bool jackpossible(int xo, int yo, int x, int y, vector<string> &board) {
	if (xo != x || yo != y)
		return x >= 0 && y >= 0 && x < int(board.size()) && y < int(board.size())
			&& board[x][y] != '*' && board[x][y] != 'h'
			&& board[x][y] != 's' && board[xo][yo] != 'S';
	else
		return board[x][y] == 'S';
}
bool jillpossible(int xo, int yo, int x, int y, vector<string> &board) {
	if (xo != x || yo != y)
		return x >= 0 && y >= 0 && x < int(board.size()) && y < int(board.size())
			&& board[x][y] != '*' && board[x][y] != 'H'
			&& board[x][y] != 'S' && board[xo][yo] != 's';
	else return board[x][y] == 's';
}

vector<pair<int, int> > moves = { {-1, 0}, {1, 0}, {0, 1}, {0, -1}, {0, 0} };

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	bool hadcase = false;
	while (true) {
		int n;
		cin >> n;
		if (n == 0) break;
		if (hadcase) cout << '\n';
		vector<string> board(n, "");
		int jackhouse = -1, jillhouse = -1, jackschool = -1, jillschool = -1;
		for (int i = 0; i < n; ++i) {
			cin >> board[i];
			for (int j = 0; j < n; ++j) {
				if (board[i][j] == 'H')
					jackhouse = pos(i, j, n);
				if (board[i][j] == 'h')
					jillhouse = pos(i, j, n);
				if (board[i][j] == 'S')
					jackschool = pos(i, j, n);
				if (board[i][j] == 's')
					jillschool = pos(i, j, n);
			}
		}
		int s = cpos(jackhouse, jillhouse, n),
		    t = cpos(jackschool, jillschool, n);
		
		vector<long double> dist(n * n * n * n, -1.0);
		vector<int> pmoves(n * n * n * n, 0);
		vector<int> par(n * n * n * n, -1);
		dist[s] = euclid(jackhouse/n, jackhouse%n, jillhouse/n, jillhouse%n);
		priority_queue<pair<long double, int> > pq;
		pq.push({dist[s], s});
		while (!pq.empty()) {
			long double dis = pq.top().first;
			int pos = pq.top().second;
			pq.pop();
			if (dis < dist[pos]) continue;
			if (pmoves[pos] > 10000) continue;
			if (pos == t) break;
//		if (dis < 6.5) continue;
			int pos1 = pos / (n * n), pos2 = pos % (n * n);
			int x1 = pos1 / n, y1 = pos1 % n;
			int x2 = pos2 / n, y2 = pos2 % n;
			for (auto m1 : moves) {
				int nx1 = x1 + m1.first;
				int ny1 = y1 + m1.second;
				if (!jackpossible(x1, y1, nx1, ny1, board))
					continue;
				for (auto m2 : moves) {
					int nx2 = x2 + m2.first;
					int ny2 = y2 + m2.second;
					if (!jillpossible(x2,y2,nx2,ny2,board)) continue;
					int npos = cpos(pos(nx1, ny1, n), pos(nx2, ny2, n), n);
					long double ndis = min(dis, euclid(nx1, ny1, nx2, ny2));
					if (ndis > dist[npos]/* || (ndis == dist[npos] && pmoves[npos] > pmoves[pos] + 5)*/) {
						dist[npos] = ndis;
						par[npos] = pos;
						pmoves[npos] = pmoves[pos] + 1;
						pq.push({dist[npos], npos});
					} 
				}
			}
		}
		vector<char> jackpath, jillpath;
		int cur = t;
		cout << fixed << setprecision(2) << dist[t] << '\n';
		while (par[cur] != -1) {
			int cpos1 = cur / (n*n), cpos2 = cur % (n*n);
			int cx1 = cpos1 / n, cy1 = cpos1 % n;
			int cx2 = cpos2 / n, cy2 = cpos2 % n;
			cur = par[cur];
			cpos1 = cur / (n*n); cpos2 = cur % (n*n);
			int nx1 = cpos1 / n, ny1 = cpos1 % n;
			int nx2 = cpos2 / n, ny2 = cpos2 % n;
			if (cx1 < nx1) jackpath.push_back('N');
			if (cx1 > nx1) jackpath.push_back('S');
			if (cy1 < ny1) jackpath.push_back('W');
			if (cy1 > ny1) jackpath.push_back('E');
			if (cx2 < nx2) jillpath.push_back('N');
			if (cx2 > nx2) jillpath.push_back('S');
			if (cy2 < ny2) jillpath.push_back('W');
			if (cy2 > ny2) jillpath.push_back('E');
		}
		for (int i = jackpath.size() - 1; i >= 0; --i)
			cout << jackpath[i]; cout << '\n';
		for (int i = jillpath.size() - 1; i >= 0; --i)
			cout << jillpath[i]; cout << '\n';
		hadcase = true;
	}
	cout << flush;
	
	return 0;
}
