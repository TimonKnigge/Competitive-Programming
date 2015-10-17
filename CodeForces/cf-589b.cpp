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

int tree[8001][8001];
int T = 8000;
void init() {
	for (int i = 0; i <= T; ++i)
	for (int j = 0; j <= T; ++j)
		tree[i][j] = 0;
}

int query(int x, int y) {
	int ans = 0;
	for (int i = x; i > 0; i -= (i & (-i)))
		for (int j = y; j > 0; j -= (j & (-j)))
			ans += tree[i][j];
	return ans;
}

int query(int x1, int y1, int x2, int y2) {
	return query(x2, y2) + query(x1 - 1, y1 - 1)
		- query(x2, y1 - 1) - query(x1 - 1, y2);
}

void update(int x, int y, int v) {
	for (int i = x; i <= T; i += (i & (-i)))
		for (int j = y; j <= T; j += (j & (-j)))
			tree[i][j] += v;
}

int main() {
	init();
	int N;
	scanf("%d", &N);
	set<ll> valset;
	vector<ll> vals;
	vector<int> x(N), y(N);
	for (int i = 0; i < N; ++i) {
		scanf("%d %d", &x[i], &y[i]);
		if (x[i] > y[i]) swap(x[i], y[i]);
		if (valset.find(x[i]) == valset.end()) {
			vals.push_back(x[i]);
			valset.insert(x[i]);
		}
		if (valset.find(y[i]) == valset.end()) {
			vals.push_back(y[i]);
			valset.insert(y[i]);
		}
	}
	
	sort(vals.begin(), vals.end());
	for (int i = 0; i < N; ++i) {
		int l = 0, r = vals.size() - 1;
		while (l < r) {
			int m = (l + r) / 2;
			if (vals[m] < x[i]) l = m + 1;
			else r = m;
		}
		int c1 = l;
		l = 0; r = vals.size() - 1;
		while (l < r) {
			int m = (l + r) / 2;
			if (vals[m] < y[i]) l = m + 1;
			else r = m;
		}
		int c2 = l;
		
		c1++; c2++;
		update(c1, c2, 1);
	}
	
	ll m = 0;
	ll bestx = 0, besty = 0;
	for (int i = 0; i < vals.size(); ++i) {
		for (int j = i; j < vals.size(); ++j) {
			// Width and height?
			ll w = vals[i], h = vals[j];
			
			// Count?
			ll c = query(i + 1, j + 1, T, T);
//			cerr << w << '.' << h << " gives " << c << endl;
			
			if (w * h * c > m) {
				m = w * h * c;
				bestx = vals[i];
				besty = vals[j];
			}
		}
	}
	
	cout << m << "\n" << bestx << " " << besty << "\n";
	cout << flush;

	return 0;
}
