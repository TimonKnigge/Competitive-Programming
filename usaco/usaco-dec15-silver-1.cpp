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


struct UnionFind {
	vi par, rank, size; int c;
	UnionFind(int n) : par(n), rank(n,0), size(n,1), c(n) {
		for (int i = 0; i < n; ++i) par[i] = i;
	}

	int find(int i) { return (par[i] == i ? i : (par[i] = find(par[i]))); }
	bool same(int i, int j) { return find(i) == find(j); }
	int get_size(int i) { return size[find(i)]; }
	int count() { return c; }

	void merge(int i, int j) {
		if ((i = find(i)) == (j = find(j))) return;
		c--;
		if (rank[i] > rank[j]) swap(i, j);
		par[i] = j; size[j] += size[i];
		if (rank[i] == rank[j]) rank[j]++;
	}
};

int main() {
	
	freopen("lightson.in", "r", stdin);
	freopen("lightson.out", "w", stdout);
	
	int N, M;
	scanf("%d %d", &N, &M);
	
	vector<vb> on(N, vb(N, false));
	vector<vb> re(N, vb(N, false));
	vvii sw(N * N, vii());
	
	while (M--) {
		int x, y, a, b;
		scanf("%d %d %d %d", &x, &y, &a, &b);
		x--; y--; a--; b--;
		sw[x + N * y].push_back({a, b});
	}
	
	on[0][0] = true;
	queue<pair<int, int> > q;
	q.push({0, 0});
	int mov[8] = {0,-1,0,1,1,0,-1,0};
	while (!q.empty()) {
		int x = q.front().first, y = q.front().second;
		q.pop();
		re[x][y] = true;
		for (auto xy : sw[x + N * y]) {
			on[xy.first][xy.second] = true;
			int xx = xy.first, yy = xy.second;
			if (re[xx][yy]) continue;
			if((xx>0&&re[xx-1][yy])
			||(xx<N-1&&re[xx+1][yy])
			||(yy>0&&re[xx][yy-1])
			||(yy<N-1&&re[xx][yy+1])) {
				q.push({xx, yy});
				re[xx][yy] = true;
			} 
		}
		
		for (int i = 0; i < 4; ++i) {
			int xx = x + mov[2*i], yy = y + mov[2*i+1];
			if (xx<0||yy<0||xx>=N||yy>=N) continue;
			if (re[xx][yy]) continue;
			if (!on[xx][yy]) continue;
			q.push({xx,yy});
			re[xx][yy] = true;
		}
	}
	
	int ans = 0;
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			if (on[i][j]) ans++;
	
	cout << ans << endl;

	return 0;
}
