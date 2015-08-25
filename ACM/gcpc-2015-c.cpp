#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

typedef long double ld;

template <class T>
T det(T x1, T y1, T x2, T y2) {
	return x1 * y2 - x2 * y1;
}
template <class T>
T det(T x1, T y1, T x2, T y2, T x3, T y3) {
	return det(x2 - x1, y2 - y1, x3 - x1, y3 - y1);
}
long long det(vector<long long> &x, vector<long long> &y) {
	long long sum = 0.0;
	for (int i = 0; i < int(x.size()); ++i) {
		sum += det(x[i], y[i], x[(i+1)%x.size()], y[(i+1)%x.size()]);
	}
	return sum;
}

int main() {
	ld a; int N;
	cin >> a >> N;
	vector<long long> x(N, 0), y(N, 0);
	for (int i = 0; i < N; ++i)
		cin >> x[i] >> y[i];
	
	ld area = abs(det(x, y)) / 2.0;
	area *= (1 - a); // target surface area of cutoff
	
	ld l = 2, r = 1000, s = 2.0;
	while (true) {
		s = (l + r) / 2;
		ld v = 0.0;
		
		for (int i = 0; i < N; ++i) {
			int il = (N + i - 1) % N, ir = (N + i + 1) % N;
			ld p1x = x[i] + (x[il] - x[i]) / s;
			ld p1y = y[i] + (y[il] - y[i]) / s;
			ld p2x = x[i] + (x[ir] - x[i]) / s;
			ld p2y = y[i] + (y[ir] - y[i]) / s;
			v += abs(det(p1x, p1y, p2x, p2y, ld(x[i]), ld(y[i]))) / 2.0;
		}
		
		if (r - l < 1e-8 && abs(v - area) < 1e-8) break;
		else if (v < area) r = s;
		else l = s;
	}

	printf("%.6lf\n", double(s));
	
	return 0;
}

