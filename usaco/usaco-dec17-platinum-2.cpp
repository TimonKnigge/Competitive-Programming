#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
using ll = long long;
using ld = long double;
using ii = pair<ll, ll>;
using vi = vector<ll>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

template<class T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<class TIn, class TOut = null_type>
using order_tree = tree<TIn, TOut, less<TIn>, rb_tree_tag,
	tree_order_statistics_node_update>;

constexpr int INF = 2000000010;
constexpr ll LLINF = 9000000000000000010LL;

int N, M, Q;
int freef[1500][1500];
int dx[4] = { 0, 0, 1,-1};
int dy[4] = { 1,-1, 0, 0};
int comp[4][1500][1500], nf[1500][1500];
int cnt = 0, ncomp = 0, st = 0;
int s1[1500*1501], s2[1500*1501], s3[1500*1501], s4[1500*1501];
bool vis[1500][1500];
int d[1500][1500], l[1500][1500];
int parx[1500][1500], pary[1500][1500];
bool vis2[4][1500][1500];
bool sol[1500][1500];
int q[1500*1500*4*3+100];

void visit(int x, int y) {
	vis[x][y] = 1;
	l[x][y] = d[x][y] = ++cnt;
	for (int i = 0; i < 4; ++i) {
		int nx = x+dx[i], ny = y+dy[i];
		if (nx<0||ny<0||nx>=N||ny>=M||!freef[nx][ny]) continue;
		if (!vis[nx][ny]) {
			s1[st] = x;
			s2[st] = y;
			s3[st] = nx;
			s4[st] = ny;
			++st;
			parx[nx][ny] = x;
			pary[nx][ny] = y;
			visit(nx, ny);
			if (l[nx][ny] >= d[x][y]) {
				while (true) {
					--st;
					int x1 = s1[st], y1 = s2[st], x2 = s3[st], y2 = s4[st];
					comp[nf[x1][y1]++][x1][y1] = ncomp;
					comp[nf[x2][y2]++][x2][y2] = ncomp;
					if (x1 == x && y1 == y && x2 == nx && y2 == ny) break;
					if (x1 == nx && y1 == ny && x2 == x && y2 == y) break;
				}
				++ncomp;
			}
			l[x][y] = min(l[x][y], l[nx][ny]);
		} else if ((parx[x][y] != nx || pary[x][y] != ny)
					&& d[nx][ny] < d[x][y]) {
			s1[st] = x; s2[st] = y; s3[st] = nx; s4[st] = ny; ++st;
			l[x][y] = min(l[x][y], d[nx][ny]);
		}
	}
}

void find_bccs() {
	for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
		comp[0][i][j] = comp[1][i][j] = comp[2][i][j] = comp[3][i][j] = -1;
		vis[i][j] = false;
		d[i][j] = l[i][j] = nf[i][j] = 0;
		parx[i][j] = pary[i][j] = -1;
	}
	for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
		if (!vis[i][j] && freef[i][j]) visit(i, j);
	}
}

int main() {
	ifstream fin("pushabox.in");
	ofstream fout("pushabox.out");
	fin >> N >> M >> Q;

	int ax = 0, ay = 0, bx = -2, by = -2;
	for (int i = 0; i < N; ++i) {
		string S;
		fin >> S;
		for (int j = 0; j < M; ++j) {
			if (S[j] == '#') {
				freef[i][j] = 0;
			} else {
				freef[i][j] = 1;
				if (S[j] == 'A') ax = i, ay = j;
				if (S[j] == 'B') bx = i, by = j;
			}
		}
	}

	// Find all connected components.
	find_bccs();
/*
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			cout << "[";
			for (int k = 0; k < nf[i][j]; ++k)
				cout << ' ' << comp[k][i][j];
			cout <<"]\t";
		}
		cout << endl;
	}
// */
	// Find which components by b are reachable from a.
	set<int> stc;
	{
		queue<ii> q;
		q.push({ax, ay});
		while (!q.empty()) {
			int x, y;
			tie(x, y) = q.front(); q.pop();
			if (x == bx && y == by) continue;
			if (freef[x][y] != 1) continue;
			freef[x][y]++;
			for (int i = 0; i < 4; ++i) {
				int nx = x+dx[i], ny = y+dy[i];
				if (nx<0||ny<0||nx>=N||ny>=M||freef[nx][ny]!=1) continue;
				q.push({nx, ny});
			}
		}
		for (int i = 0; i < 4; ++i) {
			int nx = bx+dx[i], ny = by+dy[i];
			if (nx<0||ny<0||nx>=N||ny>=M||freef[nx][ny]!=2) continue;
			for (int l = 0; l < nf[bx][by]; ++l)
				for (int r = 0; r < nf[nx][ny]; ++r)
					if (comp[l][bx][by] == comp[r][nx][ny])
						stc.insert(l);
		}
	}

	// BFS over states
	for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j)
		sol[i][j] = vis2[0][i][j] = vis2[1][i][j] = vis2[2][i][j]
			= vis2[3][i][j] = false;
	int qfront = 0, qfree = 0;
	for (int i : stc) {
		q[qfree++] = i;
		q[qfree++] = bx;
		q[qfree++] = by;
		vis2[i][bx][by] = true;
	}
	while (qfront < qfree) {
		int id = q[qfront++], x = q[qfront++], y = q[qfront++];

		sol[x][y] = true;

		for (int i = 0; i < 4; ++i) {
			int fx = x-dx[i], fy = y-dy[i];
			int nx = x+dx[i], ny = y+dy[i];
			if (nx<0||ny<0||nx>=N||ny>=M||freef[nx][ny]==0) continue;
			if (fx<0||fy<0||fx>=N||fy>=M||freef[fx][fy]==0) continue;
			bool cok = false;
			for (int j = 0; !cok && j < nf[fx][fy]; ++j)
				cok = cok || comp[j][fx][fy] == comp[id][x][y];
			if (!cok) continue;
			int concom = -1;
			for (int c = 0; concom < 0 && c < nf[nx][ny]; ++c)
				for (int j = 0; concom < 0 && j < nf[x][y]; ++j)
					if (comp[c][nx][ny] == comp[j][x][y])
						concom = c;
			if (vis2[concom][nx][ny]) continue;
			vis2[concom][nx][ny] = true;
			q[qfree++] = concom;
			q[qfree++] = nx;
			q[qfree++] = ny;
		}
	}

	while (Q--) {
		int x, y;
		fin >> x >> y;
		fout << ((sol[x-1][y-1] || (bx == x-1 && by == y-1)) ? "YES\n" : "NO\n");
	}
	fout << flush;
}

