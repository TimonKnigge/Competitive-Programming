#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

typedef pair<int, int> ii;
typedef vector<char> vc;
typedef vector<vc> vvc;

int nbrs[4][2] = { { 0, -1 }, { 0, 1 }, { 1, 0 }, { -1, 0 } };

void printBoard(int n, int m, vvc& board) {
	for (int y = 0; y < m; ++y) {
		for (int x = 0; x < n; ++x)
			cout << board[x][y];
		cout << endl;
	}
}

int main() {

	ios::sync_with_stdio(false);

	// Read input
	int n, m, opencount = 0;
	cin >> m >> n;
	vvc board(n, vc(m));
	for (int y = 0; y < m; ++y){
		for (int x = 0; x < n; ++x) {
			cin >> board[x][y];
			if (board[x][y] == '.') opencount++;
		}
	}

	queue<pair<ii, ii>> process;
	// Enqueue all positions with 1 neighbour
	for (int x = 0; x < n; ++x) {
		for (int y = 0; y < m; ++y) {
			if (board[x][y] == '*') continue;

			// Detect neighbours
			int c = 0, dx = 0, dy = 0;
			for (int i = 0; i < 4; ++i) {
				int _x = x + nbrs[i][0], _y = y + nbrs[i][1];
				if (_x >= 0 && _x < n && _y >= 0 && _y < m) {
					if (board[_x][_y] == '.') {
						c++; dx = _x; dy = _y;
					}
				}
			}

			if (c == 0) {
				cout << "Not unique" << endl;
				return 0;
			}
			else if (c == 1) {
				process.push(make_pair(make_pair(x, y), make_pair(dx, dy)));
			}
		}
	}

	// Fill the board
	int filled = 0;
	while (!process.empty()) {
		auto p = process.front(); process.pop();
		ii f = p.first, s = p.second;

		// Check overlaps
		bool b1 = (board[f.first][f.second] != '.'),
			b2 = (board[s.first][s.second] != '.');
		if (b1 && b2) continue;
		if ((b1 && !b2) || (b2 && !b1)) {
			cout << "Not unique" << endl;
			return 0;
		}

		// Place tiles on the board
		if (f.first != s.first) {
			board[min(f.first, s.first)][f.second] = '<';
			board[max(f.first, s.first)][f.second] = '>';
		}
		else {
			board[f.first][min(f.second, s.second)] = '^';
			board[f.first][max(f.second, s.second)] = 'v';
		}
		filled += 2;

		// Detect neighbours
		int x = s.first, y = s.second;
		for (int i = 0; i < 4; ++i) {
			int nbx = x + nbrs[i][0], nby = y + nbrs[i][1], c = 0, dx = 0, dy = 0;
			if (nbx < 0 || nbx >= n || nby < 0 || nby >= m) continue;
			if (board[nbx][nby] != '.') continue;

			for (int j = 0; j < 4; ++j) {
				int _x = nbx + nbrs[j][0], _y = nby + nbrs[j][1];
				if (_x >= 0 && _x < n && _y >= 0 && _y < m) {
					if (board[_x][_y] == '.') {
						c++; dx = _x; dy = _y;
					}
				}
			}

			if (c == 0) {
				cout << "Not unique" << endl;
				return 0;
			}
			else if (c == 1) {
				process.push(make_pair(make_pair(nbx, nby), make_pair(dx, dy)));
			}
		}
	}

	if (opencount == filled) {
		printBoard(n, m, board);
	}
	else cout << "Not unique" << endl;

	return 0;
}
