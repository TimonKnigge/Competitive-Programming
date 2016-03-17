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

int main() {
	
	int N, M;
	scanf("%d %d", &N, &M);
	
	vector<pair<ll, ii> > V;
	vector<vector<int> > B(N, vector<int>(M, 0LL));
	for (int r = 0; r < N; ++r) {
		for (int c = 0; c < M; ++c) {
			scanf("%d", &B[r][c]);
			V.push_back({B[r][c], {r, c}});
		}
	}
	
	sort(V.begin(), V.end());
	vi rmax(N, 0LL), cmax(M, 0LL);
	
	vi rgroup_marker(N, -1LL), rgroup_timestamp(N, V.size());
	vi cgroup_marker(M, -1LL), cgroup_timestamp(M, V.size());
	
	size_t l = 0;
	while (l < V.size()) {
		size_t r = l + 1;
		while (r < V.size() && V[r].first == V[l].first) ++r;
		
		UnionFind uf(r - l);
		vi mx(r - l, 0LL);
		for (size_t i = l; i < r; ++i) {
			int R = V[i].second.first, C = V[i].second.second;
			mx[i - l] = max(rmax[R], cmax[C]);
			
			if (rgroup_timestamp[R] == l) {
				mx[i - l] = mx[uf.find(rgroup_marker[R])]
					= max(mx[i - l], mx[uf.find(rgroup_marker[R])]);
				uf.merge(i - l, rgroup_marker[R]);
				rgroup_marker[R] = uf.find(i - l);
			} else {
				rgroup_timestamp[R] = l;
				rgroup_marker[R] = i - l;
			}
			
			if (cgroup_timestamp[C] == l) {
				mx[uf.find(i - l)] = mx[uf.find(cgroup_marker[C])]
					= max(mx[uf.find(i - l)], mx[uf.find(cgroup_marker[C])]);
				uf.merge(i - l, cgroup_marker[C]);
				cgroup_marker[C] = uf.find(i - l);
			} else {
				cgroup_timestamp[C] = l;
				cgroup_marker[C] = uf.find(i - l);
			}
		}
		
		for (size_t i = l; i < r; ++i) {
			int R = V[i].second.first, C = V[i].second.second;
			ll val = mx[uf.find(i - l)] + 1;
			B[R][C] = val;
			rmax[R] = max(rmax[R], val);
			cmax[C] = max(cmax[C], val);
		}
		
		l = r;
	}
	
	for (int r = 0; r < N; ++r)
		for (int c = 0; c < M; ++c)
			cout << B[r][c] << " \n"[c + 1 == M];
	cout << flush;
	
	return 0;
}
