#include <iostream>
#include <algorithm>

using namespace std;

#ifndef _MSC_VER
#define scanf_s scanf
#endif

#define CONV(x, y) ((x) + 1000 * (y))

int main() {

	int w, h, tw, th;
	while (scanf_s("%d %d %d %d", &h, &w, &th, &tw) != EOF) {

		bool *t = new bool[1000 * 1000];
		int *s = new int[1000 * 1000];
		for (int y = 0; y < h; ++y) {
			for (int x = 0; x < w; ++x) {
				char c;
				cin >> c;
				t[CONV(x, y)] = (c == 'X');

				// Compute area sum
				s[CONV(x, y)] = t[CONV(x, y)] ? 1 : 0;
				if (x > 0) s[CONV(x, y)] += s[CONV(x - 1, y)];
				if (y > 0) s[CONV(x, y)] += s[CONV(x, y - 1)];
				if (x > 0 && y > 0) s[CONV(x, y)] -= s[CONV(x - 1, y - 1)];
			}
		}

		// Consider all starting points
		int m = 2000000000;
		for (int sx = 0; sx > -tw; --sx) {
			for (int sy = 0; sy > -th; --sy) {
				int tc = 0;
				for (int tx = sx; tx < w; tx += tw) {
					for (int ty = sy; ty < h; ty += th) {
						// Calculate area covered by the
						// tile from (sx, sy).
						int ox = min(tx + tw - 1, w - 1),
							oy = min(ty + th - 1, h - 1);
						int asum = s[CONV(ox, oy)];
						if (tx > 0) asum -= s[CONV(tx - 1, oy)];
						if (ty > 0) asum -= s[CONV(ox, ty - 1)];
						if (tx > 0 && ty > 0) asum += s[CONV(tx - 1, ty - 1)];
						if (asum > 0) tc++;
					}
				}
				m = min(m, tc);
			}
		}

		delete[] t;
		delete[] s;

		cout << m << endl;
	}

	return 0;
}