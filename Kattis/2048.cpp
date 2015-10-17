#include <iostream> 
#include <cstdio>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <bitset>
#include <numeric>
#include <iterator>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <cassert>

using namespace std;
using ll = long long;
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

int board[4][4];

void rotate_right() {
	int board2[4][4];
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			board2[i][j] = board[i][j];
	
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			board[j][3 - i] = board2[i][j];
}

void shift_left() {
	int board2[4][4];
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j) {
			board2[i][j] = board[i][j];
			board[i][j] = 0;
		}
	
	for (int i = 0; i < 4; ++i) {
		bool check = false;
		int pos = 0;
		for (int j = 0; j < 4; ++j) {
			if (board2[i][j] == 0) continue;
			if (check && board[i][pos - 1] == board2[i][j]) {
				board[i][pos - 1] *= 2;
				check = false;
			} else {
				check = true;
				board[i][pos] = board2[i][j];
				pos++;
			}
		}
	}
}

int main() {
	
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			cin >> board[i][j];
	
	int r;
	cin >> r;
	
	for (int i = 0; i < (4-r) % 4; ++i)
		rotate_right();
	shift_left();
	for (int i = 0; i < r; ++i)
		rotate_right();
	
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			cout << board[i][j] << " \n"[j == 3];
	cout << flush;
	
	return 0;
}
