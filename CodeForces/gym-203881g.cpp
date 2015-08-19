#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;
typedef long double ld;

const ld pi = 3.14159265358979;

int main() {
	ld a, r;
	cin >> a >> r;
	ld sinx = a / (2 * r), cosx = sqrt(1.0 - sinx * sinx);
	ld ans = r * r * (pi / 2.0 - sinx * cosx - asin(cosx));
	printf("%.9lf\n", double(ans));
	return 0;
}
