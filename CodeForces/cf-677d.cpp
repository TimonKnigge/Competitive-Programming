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
const ll LLINF = 90000000000000000;

template <class T>
struct FenwickTree2D {
	vector< vector<T> > tree;
	int n;
	FenwickTree2D(int n) : n(n) { tree.assign(n + 1, vector<T>(n + 1, LLINF)); }
	T query(int x, int y) {
		T s = LLINF;
		for (int i = x; i > 0; i -= (i & (-i)))
			for (int j = y; j > 0; j -= (j & (-j)))
				s = min(s, tree[i][j]);
		return s;
	}
	void update(int x, int y, T v) {
		for (int i = x; i <= n; i += (i & (-i)))
			for (int j = y; j <= n; j += (j & (-j)))
				tree[i][j] = min(tree[i][j], v);
	}
	void reset_around(int x, int y) {
		for (int i = x; i <= n; i += (i & (-i)))
			for (int j = y; j <= n; j += (j & (-j)))
				tree[i][j] = LLINF;
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N, M, P;
	cin >> N >> M >> P;
	
	vvi key(N, vi(M, 0LL));
	vvii byp(P, vii());
	for (int r = 0; r < N; ++r) {
		for (int c = 0; c < M; ++c) {
			cin >> key[r][c];
			byp[--key[r][c]].push_back({r, c});
		}
	}
	
//	cerr << "Read input"<<endl;
	
	int NM = max(N, M);
	FenwickTree2D<ll> ft0(NM), ft1(NM), ft2(NM), ft3(NM);
	for (ii v : byp[0]) {
		ft0.update(v.first+1, v.second+1, v.first+v.second-v.first-v.second);
		ft1.update(NM-v.first, v.second+1, v.first+v.second+v.first-v.second);
		ft2.update(v.first+1, NM-v.second, v.first+v.second-v.first+v.second);
		ft3.update(NM-v.first, NM-v.second, v.first+v.second+v.first+v.second);
	}
	
//	cerr << "Initialized tree" << endl;
	
	for (int p = 1; p < P; ++p) {
//		cerr << "Starting round " << p << endl;
		
		vi cost(byp[p].size(), 0LL);
		for (size_t i = 0; i < byp[p].size(); ++i) {
			int x = byp[p][i].first, y = byp[p][i].second;
//			cerr << "Querying for " << x << ' ' << y << endl;
			ll v0 = ft0.query(x+1, y+1) + x + y;
			ll v1 = ft1.query(NM-x, y+1) - x + y;
			ll v2 = ft2.query(x+1, NM-y) + x - y;
			ll v3 = ft3.query(NM-x, NM-y) - x - y;
			cost[i] = min(min(v0, v1), min(v2, v3));
//			cerr << "Queried, got " << cost[i] << endl;
		}
		
//		cerr << "Calculated costs" << endl;
		
		for (ii v : byp[p-1])
			ft0.reset_around(v.first+1, v.second+1),
			ft1.reset_around(NM-v.first, v.second+1),
			ft2.reset_around(v.first+1, NM-v.second),
			ft3.reset_around(NM-v.first, NM-v.second);
		
		for (size_t i = 0; i < byp[p].size(); ++i) {
			int x = byp[p][i].first, y = byp[p][i].second;
			ft0.update(x+1, y+1, cost[i]-x-y);
			ft1.update(NM-x, y+1, cost[i]+x-y);
			ft2.update(x+1, NM-y, cost[i]-x+y);
			ft3.update(NM-x, NM-y, cost[i]+x+y);
		}
		
//		cerr << "Ending round " << p << endl;
	}
	
	ii v = *byp[P - 1].begin();
	cout << (v.first + v.second + ft0.query(NM, NM)) << endl;
	
	return 0;
}
