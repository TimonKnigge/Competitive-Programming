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

int main() {
	
	int t;
	scanf("%d", &t);
	while (t--) {
		int w, h, n;
		scanf("%d %d %d", &w, &h, &n);
		
		char board[2][30][30];
		int ships[2];
		ships[0] = ships[1] = 0;
		for (int s = 0; s < 2; ++s) {
			for (int y = h - 1; y >= 0; --y) {
				for (int x = 0; x < w; ++x) {
					char ch;
					scanf(" %c", &ch);
					board[s][x][y] = ch;
					if (ch == '#') ships[s]++;
				}
			}
		}
		
		bool end = false;
		int turn = 0;
		while (n--) {
			int x, y;
			scanf("%d %d", &x, &y);
			if (end) continue;
			if (board[1 - turn][x][y] == '#') {
				board[1-turn][x][y] = ' ';
				ships[1-turn]--;
				if (ships[1-turn]==0) {
					turn = 1 - turn;
					if (turn == 0) end = true;
				}
			} else {
				turn = 1 - turn;
				if (turn == 0 && ships[0]*ships[1] == 0)
					end = true;
			}
		}
		
		if (ships[0] == 0 && ships[1] > 0)
			printf("player two wins\n");
		else if (ships[0] > 0  && ships[1] == 0)
			printf("player one wins\n");
		else	printf("draw\n");

	}
	
	return 0;
}
