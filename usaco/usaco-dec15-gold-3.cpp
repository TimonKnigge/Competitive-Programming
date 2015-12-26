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

int dis[1000][1000][4][2];

int main() {
	
	freopen("dream.in", "r", stdin);
	freopen("dream.out", "w", stdout);
	
	int N, M;
	scanf("%d %d", &N, &M);
	vvi tile(N, vi(M, -1));
	for (int r = 0; r < N; ++r)
		for (int c = 0; c < M; ++c) {
			scanf("%d", &tile[r][c]);
		}
	
	for (int i = 0; i < N; ++i)
	for (int j = 0; j < M; ++j)
	for (int d = 0; d < 4; ++d)
	dis[i][j][d][0] = dis[i][j][d][1] = INF;
	
	dis[0][0][0][0] = 0;
	int UP = 0, LEFT = 1, DOWN = 2, RIGHT = 3;
	int mov[8] = {0, -1, -1, 0, 0, 1, 1, 0};
	queue<pair<pair<int, int>, pair<int, int> > > q;
	q.push({{0, 0}, {0, 0}});
	while (!q.empty()) {
		int x = q.front().first.first;
		int y = q.front().first.second;
		int dir = q.front().second.first;
		int ora = q.front().second.second;
		q.pop();
		
		int d = dis[x][y][dir][ora];
		if (d == INF) continue;
		
		bool imp = (tile[x][y] != 4);
		int xxx=x+mov[2*dir];
		int yyy=y+mov[2*dir+1];
		if (xxx<0||yyy<0||xxx>=N||yyy>=M) imp = true;
		else if(tile[xxx][yyy]==3) imp=true;
		else if(tile[xxx][yyy]==0) imp=true;
		
		for (int i = 0; i < 4; ++i) {
			int xx = x + mov[2*i];
			int yy = y + mov[2*i+1];
			if (xx<0||yy<0||xx>=N||yy>=M) continue;
			if (tile[xx][yy] == 0) continue;
			if (ora == 0 && tile[xx][yy] == 3) continue;
			if (tile[x][y] == 4 && dir != i && !imp) continue;
			int col = min(int(tile[xx][yy]!=4), max(ora,int(tile[xx][yy]==2)));
			if (dis[xx][yy][i][col] == INF) {
				dis[xx][yy][i][col] = d + 1;
				q.push({{xx,yy},{i,col}});
			}
		}
	}
	
	int m = INF;
	for (int i = 0; i <4; ++i)
		m = min(m, min(dis[N-1][M-1][i][0],dis[N-1][M-1][i][1]));
	cout << (m < INF ? m : -1) << endl;
	
	return 0;
}
