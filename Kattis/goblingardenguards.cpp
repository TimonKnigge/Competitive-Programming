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
#include <cstdio>

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

const int LIM = 10001;

int main() {
	int g;
	scanf("%d", &g);
	
	vector<vb> vis(LIM, vb(LIM, false));
	
	vi gx(g, 0), gy(g, 0);
	for (int i = 0; i < g; ++i) scanf("%d %d", &gx[i], &gy[i]);
	
	int m;
	scanf("%d", &m);
	while (m--) {
		int _xs, _ys, _r;
		scanf("%d %d %d", &_xs, &_ys, &_r);
		ll xs = _xs, ys = _ys, r = _r;
		ll rr = r * r;
		for (int x = -r; x <= r; ++x)
			for (int y = -r; y <= r; ++y) {
				if (x*x + y*y > rr) continue;
				if (x + xs < 0 || y + ys < 0 ||
					x + xs >= LIM || y + ys >= LIM)
					continue;
				else vis[x + xs][y + ys] = true;
			}
	}
	
	int ans = g;
	for (int i = 0; i < g; ++i)
		if (vis[gx[i]][gy[i]]) ans--;
	printf("%d\n", ans);
	
	return 0;
}
