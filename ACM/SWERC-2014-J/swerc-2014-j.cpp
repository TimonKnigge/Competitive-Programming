#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <string>

using namespace std;

#ifdef _MSC_VER
#define scanf scanf_s
#endif

typedef long long ll;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef vector<ll> vll;
typedef vector<vll> vvll;

ll alpha = 71, beta = 79, Q = 1000000007;
ll _X = 2, _O = 3;

ll nMod(int a, int b) {
	while (a < 0) a += b;
	return a % b;
}

int main() {

	int hp, wp, hm, wm;
	while (scanf("%d %d %d %d", &hp, &wp, &hm, &wm)) {

		// Hash the pattern
		vvb pattern(wp, vb(hp, false));
		ll patternhash = 0, a = 1, b = 1, ab = 0;
		for (int y = 0; y < hp; ++y) {
			a = 1;
			for (int x = 0; x < wp; ++x) {
				char c; scanf(" %c", &c);
				pattern[x][y] = (c == 'x');
				ab = (a * b) % Q;
				patternhash = (patternhash + ab * (pattern[x][y] ? _X : _O)) % Q;
				a = (a * alpha) % Q;
			}
			b = (b * beta) % Q;
		}
		
		// Hash all subrectangles of the painting
		vvb painting(wm, vb(hm, false));
		a = 1; b = 1;
		vvll squarehash(wm, vll(hm, 0));
		for (int y = 0; y < hm; ++y) {
			a = 1;
			for (int x = 0; x < wm; ++x) {
				char c; scanf(" %c", &c);
				painting[x][y] = (c == 'x');
				
				ab = (a * b) % Q;
				ll phash = (ab * (painting[x][y] ? _X : _O)) % Q;
				if (x > 0)
					phash = (phash + squarehash[x - 1][y]) % Q;
				if (y > 0)
					phash = (phash + squarehash[x][y - 1]) % Q;
				if (x > 0 && y > 0)
					phash = nMod(phash - squarehash[x - 1][y - 1], Q);
				squarehash[x][y] = phash;

				a = (a * alpha) % Q;
			}
			b = (b * beta) % Q;
		}

		// Search for the pattern
		a = 1; b = 1;
		ll count = 0;
		for (int x = 0; x <= wm - wp; ++x) {
			b = 1;
			for (int y = 0; y <= hm - hp; ++y) {

				// Calculate the positional hash
				ll phash = squarehash[x + wp - 1][y + hp - 1];
				if (x > 0)
					phash = nMod(phash - squarehash[x - 1][y + hp - 1], Q);
				if (y > 0)
					phash = nMod(phash - squarehash[x + wp - 1][y - 1], Q);
				if (x > 0 && y > 0)
					phash = (phash + squarehash[x - 1][y - 1]) % Q;
				
				ab = (a * b) % Q;
				ll movedpatternhash = (patternhash * ab) % Q;

				// Check for a match
				if (movedpatternhash == phash) {
					bool m = true;
					for (int i = 0; i < wp; ++i) {
						for (int j = 0; j < hp; ++j) {
							if (pattern[i][j] != painting[x + i][y + j]) {
								m = false;
								break;
							}
						}
						if (!m) break;
					}
					if (m) count++;
				}

				b = (b * beta) % Q;
			}
			a = (a * alpha) % Q;
		}

		cout << count << endl;
	}

	return 0;
}