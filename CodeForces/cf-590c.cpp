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
	
	int n, m;
	scanf("%d %d", &n, &m);
	vector<vector<char> > board(n, vector<char>(m, ' '));
	
	vector<pair<int, int> > land[3];
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j) {
			char c;
			scanf(" %c", &c);
			board[i][j] = c;
			if (c == '1' || c == '2' || c == '3')
				land[c - '1'].push_back({i, j});
		}
	
	int ldist[3][3];
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			ldist[i][j] = INF;
	
	int dir[8] = {-1, 0, 1, 0, 0, -1, 0, 1};
	
	vvi dist[3];
	dist[0].assign(n, vector<int>(m, INF));
	dist[1].assign(n, vector<int>(m, INF));
	dist[2].assign(n, vector<int>(m, INF));
	for (int l = 0; l < 3; ++l) {
		queue<pair<int, int> > q;
		for (pair<int, int> p : land[l]) {
			dist[l][p.first][p.second] = 0;
			q.push(p);
		}
		while (!q.empty()) {
			int i = q.front().first, j = q.front().second;
			q.pop();
			for (int x = 0; x < 4; ++x) {
				int ni = i + dir[2*x];
				int nj = j + dir[2*x+1];
				if (ni < 0 || ni >= n || nj < 0 || nj >= m)
					continue;
				if (dist[l][ni][nj] != INF) continue;
				if (board[ni][nj] == '#') continue;
				dist[l][ni][nj] = 1 + dist[l][i][j];
				q.push({ni, nj});
				if (board[ni][nj] != '.')
					ldist[l][board[ni][nj] - '1']
				= min(ldist[l][board[ni][nj] - '1'], dist[l][ni][nj]);
			}
		}
	}
	
	int mindist = INF;
	if (ldist[0][1] == INF || ldist[0][2] == INF || ldist[1][2] == INF) {
		printf("%d\n", -1);
	} else {
		// Try each hub
		for (int l = 0; l < 3; ++l) {
			int cost = 0;
			for (int r = 0; r < 3; ++r) {
				if (l == r) continue;
				cost += ldist[l][r];
			}
			cost -= 2;
			if (mindist > cost) mindist = cost;
//			cerr << "Sourcing from " << l << " gives " << cost << endl;
		}
		// Try all midpoints
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < m; ++j) {
				if (board[i][j] != '.') continue;
				int cost = 0;
				bool pos = true;
				for (int k = 0; k < 3; ++k) {
					if (dist[k][i][j] == INF)
						pos = false;
					else cost += dist[k][i][j];
				}
				if (!pos) continue;
				cost -= 2;
				if (mindist > cost) mindist = cost;
//				cerr << "(" << i << ", "<<j<<") gives " << cost << endl;
			}
		
		printf("%d\n", mindist);
	}
	
	return 0;
}
