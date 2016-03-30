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

inline int setof(int r, int c, int N) {
	return r + c * N;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N, M;
	ll K;
	cin >> N >> M >> K;
	
	vvi A(N, vi(M, 0LL));
	vector<pair<ll, ii> > byvalue;
	for (int r = 0; r < N; ++r)
		for (int c = 0; c < M; ++c)
			cin >> A[r][c],
			byvalue.push_back({A[r][c], {r, c}});
	
	sort(byvalue.rbegin(), byvalue.rend());
	
	UnionFind uf(N * M);
	vector<vb> decreasing(N, vb(M, false));
	
	int sset = -1, sr = 0, sc = 0;
	ll  svalue = 0LL;
	for (size_t i = 0; i < byvalue.size(); ++i) {
		
		int r = byvalue[i].second.first;
		int c = byvalue[i].second.second;
		
		decreasing[r][c] = true;
		if (r > 0 && decreasing[r - 1][c])
			uf.merge(setof(r, c, N), setof(r - 1, c, N));
		if (r + 1 < N && decreasing[r + 1][c])
			uf.merge(setof(r, c, N), setof(r + 1, c, N));
		if (c > 0 && decreasing[r][c - 1])
			uf.merge(setof(r, c, N), setof(r, c - 1, N));
		if (c + 1 < M && decreasing[r][c + 1])
			uf.merge(setof(r, c, N), setof(r, c + 1, N));
		
		ll sz = uf.get_size(setof(r, c, N));
		if (K % A[r][c] == 0LL && K / A[r][c] <= sz) {
			sset = setof(r, c, N);
			sr = r;
			sc = c;
			svalue = A[r][c];
			break;
		}
	}
	
	if (sset == -1) {
		cout << "NO" << endl;
	} else {
		vvi ans(N, vi(M, 0LL));
		vvi vis(N, vi(M, false));
		
		queue<ii> q;
		q.push({sr, sc});
		int elems = int(K / svalue);
		while (!q.empty() && elems > 0) {
			sr = q.front().first;
			sc = q.front().second;
			q.pop();
			
			if (vis[sr][sc]) continue;
			vis[sr][sc] = true;
			ans[sr][sc] = svalue;
			--elems;
			if (sr > 0 && decreasing[sr - 1][sc])
				q.push({sr - 1, sc});
			if (sr + 1 < N && decreasing[sr + 1][sc])
				q.push({sr + 1, sc});
			if (sc > 0 && decreasing[sr][sc - 1])
				q.push({sr, sc - 1});
			if (sc + 1 < M && decreasing[sr][sc + 1])
				q.push({sr, sc + 1});
		}
		
		cout << "YES" << endl;
		for (int r = 0; r < N; ++r)
			for (int c = 0; c < M; ++c)
				cout << ans[r][c] << " \n"[c + 1 == M];
	}
		
	return 0;
}
