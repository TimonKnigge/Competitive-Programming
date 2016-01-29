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
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

int dir[16] = {-1, 0, -1, 1, 0, 1, 1, 1, 1, 0, 1, -1, 0, -1, -1, -1};

int main() {
	
	int R, C;
	scanf("%d %d", &R, &C);
	
	vvi grid(R, vi(C, 0));
	for (int r = 0; r < R; ++r)
		for (int c = 0; c < C; ++c) {
			char cc;
			scanf(" %c", &cc);
			grid[r][c] = cc - '0';
		}
	
	int N;
	scanf("%d", &N);
	while (N--) {
		vvi cost(R, vi(C, INF));
		
		int xs, ys, xt, yt;
		scanf("%d %d %d %d", &xs, &ys, &xt, &yt);
		--xs; --ys; --xt; --yt;
		
		priority_queue<
			pair<int, ii>,
			vector<pair<int, ii> >,
			greater<pair<int, ii> > > pq;
		
		cost[xs][ys] = 0;
		pq.push({0, {xs, ys}});
		while (!pq.empty()) {
			int d = pq.top().first;
			int x = pq.top().second.first;
			int y = pq.top().second.second;
			pq.pop();
			if (d > cost[x][y]) continue;
			
			if (x == xt && y == yt) break;
			for (int j = 0; j < 8; ++j) {
				int nx = x + dir[2*j];
				int ny = y + dir[2*j+1];
				int c = d + (j != grid[x][y]);
				if (nx < 0 || nx >= R || ny < 0 || ny >= C
					|| cost[nx][ny] <= c) continue;
				pq.push({c, {nx, ny}});
				cost[nx][ny] = c;
			}
		}
		
		cout << cost[xt][yt] << endl;
	}
	
	return 0;
}
