#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;
using vvvvi = vector<vvvi>;
using vii = vector<ii>;
using vvii = vector<vii>;
using mq = priority_queue<pair<int, ii>, vector<pair<int, ii>>,
				greater<pair<int, ii>>>;

constexpr int INF = 10000,
	dx[4] = {1, 0,-1, 0},
	dy[4] = {0, 1, 0,-1};


void solve(int x, int y, vvi &d, const vector<string> &B) {
	if (B[x][y] == '#') return;
	d[x][y] = (B[x][y] == 'o' ? 1 : 0);
	mq pq; pq.push({d[x][y], {x, y}});
	while (!pq.empty()) {
		int dist = pq.top().first;
		x = pq.top().second.first; y = pq.top().second.second;
		pq.pop();
		
		if (dist != d[x][y]) continue;
		
		for (int i = 0; i < 4; ++i) {
			int nx = x + dx[i], ny = y + dy[i];
			if (nx < 0 || ny < 0 || nx >= B.size()
				|| ny >= B.back().size()) continue;
			if (B[nx][ny] == '#') continue;
			int nd = dist + (B[nx][ny] == 'o' ? 1 : 0);
			if (nd < d[nx][ny])
				d[nx][ny] = nd, pq.push({nd, {nx, ny}});
		}
	}
}

void clearpath(vector<string> &board, int a, int b, int c, int d) {
	vvi dis(board.size(), vi(board.back().size(), INF));
	vvii p(board.size(), vii(board.back().size(), {-1, -1}));
	dis[a][b] = 0; mq pq; pq.push({0, {a, b}});
	while (!pq.empty()) {
		int dist = pq.top().first, x = pq.top().second.first,
			y = pq.top().second.second; pq.pop();
		if (dist != dis[x][y]) continue;
		for (int i = 0; i < 4; ++i) {
			int nx = x+dx[i], ny = y+dy[i];
			if (nx < 0 || ny < 0 || nx >= board.size()
				|| ny >= board.back().size()) continue;
			if (board[nx][ny] == '#') continue;
			int nd = dist + (board[nx][ny] == 'o' ? 1 : 0);
			if (nd < dis[nx][ny])
				dis[nx][ny] = nd, p[nx][ny] = {x, y},
				pq.push({nd, {nx, ny}});
		}
	}
	while (c != -1 && d != -1) {
		if (board[c][d] == 'o') board[c][d] = '.';
		tie(c, d) = p[c][d];
	}
}

#define attempt(c0, c1, c2, c3) {					\
	int v = ds[x[0]][y[0]][c0?a:c][c0?b:d] 				\
		+ ds[x[1]][y[1]][c1?a:c][c1?b:d]			\
		+ ds[x[2]][y[2]][c2?a:c][c2?b:d]			\
		+ ds[x[3]][y[3]][c3?a:c][c3?b:d]			\
		+ ds[a][b][c][d]					\
		+ (B[a][b]=='o'?-2:0) + (B[c][d]=='o'?-2:0);		\
	if (v < opt) {							\
		opt = v; mx[0] = c; my[0] = d; mx[1] = a; my[1] = b;	\
		con[0] = c0; con[1] = c1; con[2] = c2; con[3] = c3; } }	\

void solve(int n, int m) {
	vector<string> B(m, "");
	for (string &b : B) cin >> b;
	
	vvvvi ds(m, vvvi(n, vvi(m, vi(n, INF))));
	for (int i = 0; i < m; ++i)
		for (int j = 0; j < n; ++j)
			solve(i, j, ds[i][j], B);
	
	int x[4], y[4];
	for (int i = 0, c = 0; i < m; ++i)
		for (int j = 0; j < n; ++j)
			if (B[i][j] >= 'A' && B[i][j] <= 'D')
				x[c] = i, y[c++] = j;
	
	int opt = INF;
	int con[4], mx[2], my[2];
	for (int a = 0; a < m; ++a) for (int b = 0; b < n; ++b)
	for (int c = 0; c < m; ++c) for (int d = 0; d < n; ++d) {
		attempt(1, 1, 0, 0); attempt(1, 0, 1, 0); attempt(1, 0, 0, 1);
		attempt(0, 1, 1, 0); attempt(0, 1, 0, 1); attempt(0, 0, 1, 1);
	}
	
	for (int i = 0; i < 4; ++i)
		clearpath(B, x[i], y[i], mx[con[i]], my[con[i]]);
	clearpath(B, mx[0], my[0], mx[1], my[1]);
	cout << n << ' ' << m << endl;
	for (const string& b : B) cout << b << '\n';
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, m;
	while (cin >> n >> m) if (n || m) solve(n, m);
	cout << "0 0\n";
	
	return 0;
}
