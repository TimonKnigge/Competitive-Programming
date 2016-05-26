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

char succ(char c) {
	if (c == '*') return '*';
	if (c == '^') return '>';
	if (c == '>') return 'v';
	if (c == 'v') return '<';
	if (c == '<') return '^';
	if (c == 'L') return 'U';
	if (c == 'U') return 'R';
	if (c == 'R') return 'D';
	if (c == 'D') return 'L';
	if (c == '-') return '|';
	if (c == '|') return '-';
	return '+';
}

bool possible(char me, char other, int rot) {
	if (me == '*' || other == '*') return false;
	
	for (rot = (rot&3); rot > 0; --rot)
		me = succ(me),
		other = succ(other);
	
	return me != 'R'
		&& me != '<'
		&& me != 'v'
		&& me != '^'
		&& me != '|'
		&& other != 'L'
		&& other != '>'
		&& other != '^'
		&& other != 'v'
		&& other != '|';
}

void relax(int x, int y, int xn, int yn, vector<vvi> &dist, int ot, int nt, queue<pair<int, ii>> &q) {
	nt = (nt&3);
	if (dist[nt][xn][yn] < LLINF) return;
	dist[nt][xn][yn] = dist[ot][x][y] + 1LL;
	q.push({nt, {xn, yn}});
}

int main() {
	
	int N, M;
	scanf("%d %d", &N, &M);
	
	vector<vector<char>> board(N, vector<char>(M, ' '));
	for (int r = 0; r < N; ++r)
		for (int c = 0; c < M; ++c)
			scanf(" %c", &board[r][c]);
	
	int xt, yt, xm, ym;
	scanf("%d %d %d %d", &xt, &yt, &xm, &ym);
	--xt;
	--yt;
	--xm;
	--ym;
	
	vector<vvi> dist(4, vvi(N, vi(M, LLINF)));
	dist[0][xt][yt] = 0;
	queue<pair<int, ii>> q;
	q.push({0, {xt, yt}});
	
	while (!q.empty()) {
		int t = q.front().first;
		int x = q.front().second.first;
		int y = q.front().second.second;
		q.pop();
//		cerr << x << ' ' << y << ' ' << t << endl;
		
		if (x == xm && y == ym) break;
		
		relax(x, y, x, y, dist, t, t+1, q);
		
		if (x > 0 && possible(board[x][y], board[x-1][y], t + 1))
			relax(x, y, x-1, y, dist, t, t, q);
		if (x+1<N && possible(board[x][y], board[x+1][y], t + 3))
			relax(x, y, x+1, y, dist, t, t, q);
		if (y > 0 && possible(board[x][y], board[x][y-1], t + 2))
			relax(x, y, x, y-1, dist, t, t, q);
		if (y+1<M && possible(board[x][y], board[x][y+1], t))
			relax(x, y, x, y+1, dist, t, t, q);
	}
	
	ll mn = LLINF;
	for (int t = 0; t < 4; ++t)
		mn = min(mn, dist[t][xm][ym]);
	
	cout << (mn == LLINF ? -1LL : mn) << endl;
	
	return 0;
}
