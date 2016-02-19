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

int L[3000][3000], R[3000][3000];
int C[6020];

template <class T>
struct FenwickTree {		// use 1 based indices!!!
	int n; vector<T> tree;
	FenwickTree(int n) : n(n) { tree.assign(n + 1, 0); }
	T query(int l, int r) { return query(r) - query(l - 1); }
	T query(int r) {
		T s = 0;
		for(; r > 0; r -= (r & (-r))) s += tree[r];
		return s;
	}
	void update(int i, T v) {
		for(; i <= n; i += (i & (-i))) tree[i] += v;
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, m;
	cin >> n >> m;
	
	vector<string> B(n, "");
	for (int i = 0; i < n; ++i)
		cin >> B[i];
	
	for (int r = 0; r < n; ++r) {
		L[r][0] = (B[r][0] == 'z' ? 1 : 0);
		R[r][m-1] = (B[r][m-1] == 'z' ? 1 : 0);
		for (int l = 1; l < m; ++l) {
			L[r][l] = (B[r][l] == 'z' ? 1 + L[r][l-1] : 0);
			R[r][m-l-1] = (B[r][m-l-1] == 'z' ? 1 + R[r][m-l] : 0);
		}
	}
	
//	cerr << "L: "<<endl;
//	for (int r = 0; r < n; ++r) {
//		for (int c = 0; c < m; ++c)
//			cerr << L[r][c];
//		cerr << endl;
//	}
//	cerr << "R: "<<endl;
//	for (int r = 0; r < n; ++r) {
//		for (int c = 0; c < m; ++c)
//			cerr << R[r][c];
//		cerr << endl;
//	}
	
	FenwickTree<ll> ft(n + m + 5);
	vector<vector<int> > schedule(m + n + 5, vector<int>());
	
	int c = 0;
	int l = 0;
	ll ans = 0LL;
	for (int i = 0; i < n + m - 1; ++i) {
		int x = min(n - 1, i);
		int y = max(0, i - n + 1);
//		cerr <<endl;
		while (x >= 0 && y < m) {
			
			if (B[x][y] == 'z') {
				schedule[c + R[x][y] - 1].push_back(c);
				ft.update(c + 1, 1);
				int mx = max(l, c - L[x][y] + 1);
				ll add = ft.query(mx + 1, c + 1);
//				cerr << add << " for " << x << ',' << y << endl;
//				cerr << "Queried " << (mx+1) << ',' << c+1 << endl;
				ans += add;
			} else {
				l = c + 1;
			}
			while (schedule[c].size() > 0) {
				ft.update(schedule[c].back() + 1, -1);
				schedule[c].pop_back();
			}

			--x;
			++y;
			++c;
		}
		for (int j = c; j < n + m + 5; ++j) {
			while (schedule[j].size() > 0) {
				ft.update(schedule[j].back() + 1, -1);
				schedule[j].pop_back();
			}
		}
		c = 0;
		l = 0;
	}
	
	cout << ans << endl;
	
	return 0;
}
