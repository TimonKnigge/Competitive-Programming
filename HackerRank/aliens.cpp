#include <iostream> // strings/streams
#include <string>
#include <sstream>
#include <vector> // datastructures
#include <list>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <bitset>
#include <tuple> // quick compare
#include <cstdio> // utils
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

constexpr int  INF = 1e9+1; // < 1e9 - -1e9
constexpr ll LLINF = 1e18+1;

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	vector<vector<bool> > status(n, vector<bool>(m, false));
	vector<vvi> largest(4, vvi(n, vi(m, 0)));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			char c;
			scanf(" %c", &c);
			status[i][j] = (c == '#');
			largest[0][i][j] = largest[1][n - 1 - i][j]
			= largest[2][i][m - 1 - j] =
			largest[3][n - 1 - i][m - 1 - j] =(status[i][j] ? 1 : -1);
		}
	}
	
	// For every direction: find the largest triangle rooted at this pos.
	int l = 1, r = 1;
	for (int id = 0; id < 4; ++id) {
		for (int i = n - 2; i >= 0; --i) {
			for (int j = m - 2; j >= 0; --j) {
				if (largest[id][i][j] == -1) continue;
				if (largest[id][i + 1][j] == -1) continue;
				if (largest[id][i][j + 1] == -1) continue;
				largest[id][i][j] = 1 + min(largest[id][i + 1][j], largest[id][i][j + 1]);
				r = max(r, largest[id][i][j]);
			}
		}
	}
	
	vector<vvi> propagate(4, vvi(n, vi(m, 0)));
	vector<vvi> timestamp(4, vvi(n, vi(m, 0)));
	int TS = 0;
	
	r++;
	
	// Binary search the size
	while (l < r) {
//		cout << "binsearch round: " << l << ", " << r << endl;
		TS++;
		int mid = (l + r) / 2;
		
		// Check if it's possible to fill using size m triangles
		bool possible = true;
		for (int id = 3; id >= 0; --id) {
		for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (largest[id][i][j] == -1) continue;
			if (largest[id][i][j] >= mid) {
				propagate[id][i][j] = mid;
				timestamp[id][i][j] = TS;
			}
			if (timestamp[id][i][j] == TS && propagate[id][i][j] > 1) {
				if (i < n - 1) {
					if (timestamp[id][i + 1][j] == TS) {
						if (propagate[id][i+1][j] < propagate[id][i][j] - 1)
						propagate[id][i+1][j] = propagate[id][i][j] - 1;
					} else {
						propagate[id][i + 1][j]
						 = propagate[id][i][j] - 1;
						timestamp[id][i + 1][j] = TS;
					}
				}
				if (j < m - 1) {
					if (timestamp[id][i][j+1] == TS) {
						if (propagate[id][i][j+1] < propagate[id][i][j] - 1)
						propagate[id][i][j+1] = propagate[id][i][j] - 1;
					} else {
						propagate[id][i][j + 1]
						 = propagate[id][i][j] - 1;
						timestamp[id][i][j + 1] = TS;
					}
				}
			}
			
			if (id == 0) {
				possible = possible && (timestamp[0][i][j] == TS || timestamp[1][n - 1 - i][j] == TS || timestamp[2][i][m - 1 - j] == TS || timestamp[3][n - 1 - i][m - 1 - j] == TS);
			}
		}
		}
		}
//		cout << "checking size " << mid << ": " << possible << endl;
		if (possible) l = mid + 1;
		else r = mid;
	}
	
	cout << (l - 1) << endl;
	
	return 0;
}
