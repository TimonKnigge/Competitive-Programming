#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <functional>
#include <math.h>

using namespace std;
  
#define INF 1e200;
#define LLINF 9000000000000000000
#define EPSILON 1e-6
#define DMUL 1000.0
#define LMUL 1000

#ifdef _MSC_VER
#define scanf scanf_s
#define printf printf_s
#endif

typedef long long ll;
typedef pair<ll, ll> point;
typedef vector<int> vi;
typedef vector<point> vp;

double ss(point p1, point p2) {
	return sqrt((p1.first - p2.first) * (p1.first - p2.first)
		+ (p1.second - p2.second) * (p1.second - p2.second));
}

vp pts;

bool on_x(int i, int j) {
	return (pts[i].first == pts[j].first 
		? pts[i].second < pts[j].second 
		: pts[i].first < pts[j].first);
}
bool on_y(int i, int j) {
	return (pts[i].second == pts[j].second
		? pts[i].first < pts[j].first
		: pts[i].second < pts[j].second);
}

pair<point, point> closest_point(vi& X, vi& Y) {
	// Base case: |P| <= 5
	int pcount = X.size();
	if (pcount <= 5) {
		pair<point, point> ret = { pts[X[0]], pts[X[1]] };
		double d = ss(ret.first, ret.second), dp;
		for (int i = 0; i < pcount; ++i) {
			for (int j = i + 1; j < pcount; ++j) {
				if ((dp = ss(pts[X[i]], pts[X[j]])) < d) {
					d = dp;
					ret = { pts[X[i]], pts[X[j]] };
				}
			}
		}
		return ret;
	}

	// Divide
	int m = pcount / 2, pivot = X[m];
	if (ss(pts[X[m]], pts[X[m + 1]]) < EPSILON)
		return{ pts[X[m]], pts[X[m + 1]] };
	vi Yl, Yr, Xl, Xr;
	Yl.reserve(pcount / 2); Xl.reserve(pcount / 2);
	Yr.reserve(pcount / 2); Xr.reserve(pcount / 2);
	for (int i = 0; i < Y.size(); ++i) {
		if (on_x(Y[i], pivot) || Y[i] == pivot) Yl.push_back(Y[i]);
		else Yr.push_back(Y[i]);
	}
	for (int i = 0; i < X.size(); ++i) {
		if (on_x(X[i], pivot) || X[i] == pivot) Xl.push_back(X[i]);
		else Xr.push_back(X[i]);
	}

	// Conquer
	pair<point, point> cl = closest_point(Xl, Yl),
		cr = closest_point(Xr, Yr);
	double delta = ss(cl.first, cl.second);
	if (ss(cr.first, cr.second) < delta) {
		delta = ss(cr.first, cr.second);
		cl = cr;
	}

	// Combine
	vi Yp;
	ll sepx = pts[pivot].first;
	for (int i = 0; i < Y.size(); ++i) {
		if (abs(pts[Y[i]].first - sepx) <= delta + EPSILON)
			Yp.push_back(Y[i]);
	}
	
	double dp = INF;
	for (int i = 0; i < Yp.size(); ++i) {
		int j = 1;
		while (i + j < Yp.size() &&
			abs(pts[Yp[i]].second - pts[Yp[i + j]].second) <= delta + EPSILON) {
			dp = ss(pts[Yp[i]], pts[Yp[i + j]]);
			if (dp < delta) {
				delta = dp;
				cl = { pts[Yp[i]], pts[Yp[i + j]] };
			}
			++j;
		}
	}

	return cl;
}

int main() {

	while (true) {
		int n;
		cin >> n;
		if (n == 0) break;

		pts.assign(n, { 0, 0 });
		vi X(n, 0), Y(n, 0);
		for (int i = 0; i < n; ++i) {
			double x, y;
			scanf("%lf %lf", &x, &y);
			pts[i] = { (ll)(y * LMUL), (ll)(x * LMUL) };
			X[i] = Y[i] = i;
		}

		sort(X.begin(), X.end(), on_x);
		sort(Y.begin(), Y.end(), on_y);

		pair<point, point> cl = closest_point(X, Y);
		printf("%.2f %.2f %.2f %.2f\n",
			cl.first.second / DMUL,
			cl.first.first / DMUL,
			cl.second.second / DMUL,
			cl.second.first / DMUL);
	}

	return 0;
}
