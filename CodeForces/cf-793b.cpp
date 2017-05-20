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
using ld = long double;
using ii = pair<ll, ll>;
using vi = vector<ll>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, m;
	cin >> n >> m;
	
	vector<string> board(n, "");
	for (string &row : board) cin >> row;
	
	vector<vb> reachable(n, vb(m, false));
	int sx = 0, sy = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (board[i][j] == 'S') { sx = i; sy = j; }
			if (board[i][j] != 'T') continue;
			for (int x = i; x >= 0 && board[x][j] != '*'; --x)
				reachable[x][j] = true;
			for (int x = i; x  < n && board[x][j] != '*'; ++x)
				reachable[x][j] = true;
			for (int y = j; y >= 0 && board[i][y] != '*'; --y)
				reachable[i][y] = true;
			for (int y = j; y  < m && board[i][y] != '*'; ++y)
				reachable[i][y] = true;
		}
	}
	
	bool pos = false;
	
	for (int x = sx; x >= 0 && board[x][sy] != '*'; --x) {
		pos = pos || reachable[x][sy];
		for (int y = sy; y >= 0 && board[x][y] != '*'; --y)
			pos = pos || reachable[x][y];
		for (int y = sy; y  < m && board[x][y] != '*'; ++y)
			pos = pos || reachable[x][y];
	}
	for (int x = sx; x  < n && board[x][sy] != '*'; ++x) {
		pos = pos || reachable[x][sy];
		for (int y = sy; y >= 0 && board[x][y] != '*'; --y)
			pos = pos || reachable[x][y];
		for (int y = sy; y  < m && board[x][y] != '*'; ++y)
			pos = pos || reachable[x][y];
	}
	for (int y = sy; y >= 0 && board[sx][y] != '*'; --y) {
		pos = pos || reachable[sx][y];
		for (int x = sx; x >= 0 && board[x][y] != '*'; --x)
			pos = pos || reachable[x][y];
		for (int x = sx; x  < n && board[x][y] != '*'; ++x)
			pos = pos || reachable[x][y];
	}
	for (int y = sy; y  < m && board[sx][y] != '*'; ++y) {
		pos = pos || reachable[sx][y];
		for (int x = sx; x >= 0 && board[x][y] != '*'; --x)
			pos = pos || reachable[x][y];
		for (int x = sx; x  < n && board[x][y] != '*'; ++x)
			pos = pos || reachable[x][y];
	}
	
	cout << (pos ? "YES" : "NO") << endl;
	
	return 0;
}
