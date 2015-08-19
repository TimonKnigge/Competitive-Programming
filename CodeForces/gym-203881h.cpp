#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;
typedef long double ld;

const ld pi = 3.14159265358979;

int main() {
	ld a, r1, r2;
	cin >> a >> r1 >> r2;
	ld sinx = a / (2 * r1), cosx = sqrt(1.0 - sinx * sinx);
	ld ans = r1 * r1 * (pi / 2.0 - sinx * cosx - asin(cosx));
	sinx = a / (2 * r2), cosx = sqrt(1.0 - sinx * sinx);
	ans += r2 * r2 * (pi / 2.0 - sinx * cosx - asin(cosx));
	printf("%.9lf\n", double(ans));
	return 0;
}
