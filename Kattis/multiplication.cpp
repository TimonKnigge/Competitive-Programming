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

int main() {
	
	while (true) {
		int A, B;
		scanf("%d %d", &A, &B);
		if (A == 0) break;
		
		int AB = A * B;
		vi dA, dB, dAB;
		int _A = A, _B = B, _AB = AB;
		while (_A  > 0) dA .push_back(_A  % 10), _A  /= 10;
		while (_B  > 0) dB .push_back(_B  % 10), _B  /= 10;
		while (_AB > 0) dAB.push_back(_AB % 10), _AB /= 10;
		
		int w = 2 + dA.size() * 4 + 1 + 2;
		int h = 2 + dB.size() * 4 + 1 + 2;
		vector<string> out(h, string(w, ' '));
		for (int x = 0; x < w; ++x)
			out[0][x] = out[h - 1][x] = '-';
		for (int y = 2; y < h; y += 4)
			for (int x = 2; x < w - 2; ++x)
				out[y][x] = '-';
		for (int y = 0; y < h; ++y) {
			if (out[y][0] == ' ') out[y][0] = '|';
			else out[y][0] = '+';
			if (out[y][w - 1] == ' ') out[y][w - 1] = '|';
			else out[y][w - 1] = '+';
		}
		for (int x = 2; x < w; x += 4)
			for (int y = 2; y < h - 2; ++y) {
				if (out[y][x] == ' ') out[y][x] = '|';
				else out[y][x] = '+';
			}
		
		for (int x = 2; x < w - 3; x += 4)
			for (int y = 2; y < h - 3; y += 4) {
				out[y + 1][x + 3] =
				out[y + 2][x + 2] =
				out[y + 3][x + 1] = '/';
			}
		
		// PRINT A B
		
		for (int i = int(dA.size()) - 1, sx = 4; i >= 0; --i) {
			out[1][sx] = '0' + dA[i];
			sx += 4;
		}
		for (int i = int(dB.size()) - 1, sy = 4; i >= 0; --i) {
			out[sy][w - 2] = '0' + dB[i];
			sy += 4;
		}
		
		// PRINT AB IN CELLS
		for (int i = 0; i < dA.size(); ++i)
			for (int j = 0; j < dB.size(); ++j) {
				int prod = dA[int(dA.size()) - 1 - i] * dB[int(dB.size()) - 1 - j];
				int top = prod / 10, bot = prod % 10;
				out[3 + 4 * j][3 + 4 * i] = '0' + top;
				out[5 + 4 * j][5 + 4 * i] = '0' + bot;
			}
		int x = w - 6, y = h - 2, dx = -4, dy = 0;
		bool place = false;
		int rx = 2, ry = 0;
		int i = 0;
		while (i < dAB.size()) {
			out[y][x] = dAB[i] + '0';
//			cerr << x << ' '<<y<<endl;
			if (!place) place = true;
			else out[y + ry][x + rx] = '/';
			x += dx;
			y += dy;
			if (x < 1) {
				x -= dx;
				y -= dy;
				x -= 2;
				y -= 2;
				dx = 0;
				dy = -4;
				rx = 0;
				ry = 2;
			}
			i++;
		}
		
		for (int j = 0; j < h; ++j)
			cout << out[j] << '\n';
		fflush(stdin);
	}
	
	return 0;
}
