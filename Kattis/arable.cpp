#include <iostream>
#include <iomanip>
#include <vector>	       
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <bitset>
#include <algorithm>
#include <functional>
#include <string>
#include <string.h>  // Include for memset!
#include <complex>
#include <random>
#define _USE_MATH_DEFINES
#include <math.h>

const int INF = 2000000000;	                 // 9
const long long LLINF = 9000000000000000000LL;  // 18
const long double LDINF = 1e300;

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<bool> vb;
typedef long long ll;
typedef long double ld;

inline int idet(int x1, int y1, int x2, int y2) {
	return x1 * y2 - x2 * y1;
}
inline int idet(int x1, int y1, int x2, int y2, int x3, int y3) {
	return idet(x2 - x1, y2 - y1, x3 - x1, y3 - y1);
}
inline int winding_number(vii &p, int x, int y) {
	int wn = 0, s = p.size();
	for (int i = 0; i < s; ++i) {
		if (p[i].second - y < 0 && p[(i+1)%s].second - y >= 0) {
			if (idet(p[i].first - x, p[i].second - y,
				p[(i+1)%s].first - x, p[(i+1)%s].second - y,
				0, 0) > 0) wn++;
		} else
		if (p[i].second - y >= 0 && p[(i+1)%s].second - y < 0) {
			if (idet(p[i].first - x, p[i].second - y,
				p[(i+1)%s].first - x, p[(i+1)%s].second - y,
				0, 0) < 0) wn--;
		}
	}
	return wn;
}

inline ld ir(ld x) {
	if (x < 0.0) return 0.0;
	if (x > 1.0) return 1.0;
	return x;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	while (true) {
		int N; 
		cin >> N;
		if (N == 0) break;
		vii p;
		for (int i = 0; i < N; ++i) {
			int x, y;
			cin >> x >> y;
			x += 100; y += 100;
			x *= 2; y *= 2;
			p.push_back({x, y});
		}

		vector<vb> fr(200, vb(200, true));
		vvi wn(200, vi(200, 0));
		for (int i = 0, j = 1; i < N; ++i, j = (j+1)%N) {
			int x1 = p[i].first / 2, y1 = p[i].second / 2,
			x2 = p[j].first / 2, y2 = p[j].second / 2;
			if (x1 == x2 || y1 == y2) {
				for (int jj = min(y1, y2); jj < max(y1, y2); jj++) {
					if (x1 > 0)
						wn[x1 - 1][jj] += (y2 > y1 ? -1 : 1);
				}
				continue;
			}
			int cx = x1 + (x2 < x1 ? -1 : 0);
			int cy = y1 + (y2 < y1 ? -1 : 0);
			int dx = (x1 < x2 ? 1 : -1);
			int dy = (y1 < y2 ? 1 : -1);
			bool upd = true;
			while (true) {
				fr[cx][cy] = false;
				if (upd) {
					int u = cx;
					int de = idet(2*x1,2*y1,2*x2,2*y2,2*cx+1,2*cy+1) * dy;
					if (de > 0) u--;
					if (u >= 0) wn[u][cy] += -dy;
				}
				if ((cx == (x2 + (x2 < x1 ? 0 : -1))) && (cy == (y2 + (y2 < y1 ? 0 : -1)))) {
					break;
				}
				int d = idet(x1, y1, x2, y2, cx + (x1 < x2 ? 1 : 0), cy + (y1 < y2 ? 1 : 0));
				upd = true;
				if (d == 0) {
					cx += dx;
					cy += dy;
				}
				else if ((d < 0 && dx * dy > 0) || (d > 0 && dx * dy < 0))
					cy += dy;
				else { cx += dx; upd = false; }
			}
		}
		
//		cerr << "Done marking" << endl;

		int ans = 0;
		for (int x = 199; x >= 0; --x) {
			for (int y = 0; y < 200; ++y) {
				if (x > 0)
					wn[x - 1][y] += wn[x][y];
				if (wn[x][y] == 0) 
					continue;
				if (fr[x][y]) {
					ans++;
//					cout << ((x-1)/2) << ' ' << ((y-1)/2)<< ' ' <<wn[(x-1)/2][(y-1)/2] << endl;
				}
			}
		}
		cout << ans << endl;
	}
	
	return 0;
}
