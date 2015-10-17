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
	int w, h;
	scanf("%d %d", &w, &h);
	
	vector<vector<char> > b(w, vector<char>(h, ' '));
	int sx = 0, sy = 0;
	for (int i = 0; i < w; ++i)
		for (int j = 0; j < h; ++j) {
			scanf(" %c", &b[i][j]);
			if (b[i][j] > 'A' && b[i][j] < 'Z') {
				sx = i; sy = j;
			}
		}
	
	vector<vector<bool> > c(w, vector<bool>(h, false));
	set<pair<pair<int, int>, int> > vis;
	
	int dir = 0, dx = 0, dy = 0;
	switch (b[sx][sy]) {
		case 'U':
			dir = 0;
			dx = -1;
			dy = 0;
			break;
		case 'R':
			dir = 1;
			dx = 0;
			dy = 1;
			break;
		case 'D':
			dir = 2;
			dx = 1;
			dy = 0;
			break;
		default:
			dir = 3;
			dx = 0;
			dy = -1;
			break;
	}
	
	while (vis.find({{sx, sy}, dir}) == vis.end()) {
		c[sx][sy] = true;
		vis.insert({{sx, sy}, dir});
		
		// Advance the state
		int nx = sx + dx, ny = sy + dy;
		if (nx >= 0 && ny >= 0 && nx < w && ny < h
			&& b[nx][ny] != '*') {
			sx = nx;
			sy = ny;
		} else {
			dir = (dir + 1) % 4;
			int tmp = dx;
			dx = dy;
			dy = -tmp;
		}
	}
	
	int ans = 0;
	for (int i = 0; i < w; ++i)
		for (int j = 0; j < h; ++j)
			if (c[i][j]) ans++;
	
	printf("%d\n", ans);
	
	return 0;
}
