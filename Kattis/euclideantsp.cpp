#include <iostream>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <cmath>

using namespace std;

typedef long double ld;

#define RES_PHI (2 - ((1.0 + sqrt(5)) / 2.0))
#define EPSILON 1e-7

ld gss(function<ld(ld)> f, ld leftbound, ld rightbound) {
	ld lb = leftbound, rb = rightbound, mlb = lb + RES_PHI * (rb - lb), mrb = rb + RES_PHI * (lb - rb);
	ld lbv = f(lb), rbv = f(rb), mlbv = f(mlb), mrbv = f(mrb);

	while (rb - lb >= EPSILON || abs(rbv - lbv) >= EPSILON) {
		if (mlbv < mrbv) { // > to maximize
			rb = mrb;  rbv = mrbv;
			mrb = mlb;  mrbv = mlbv;
			mlb = lb + RES_PHI * (rb - lb);
			mlbv = f(mlb);
		}
		else {
			lb = mlb;  lbv = mlbv;
			mlb = mrb;  mlbv = mrbv;
			mrb = rb + RES_PHI * (lb - rb);
			mrbv = f(mrb);
		}
	}

	if (lbv < mlbv && lbv < mrbv && lbv < rbv) return lb;
	if (mlbv < mrbv && mlbv < rbv) return mlb;
	if (mrbv < rbv) return mrb;
	return rb;
}


int main() {

	int n;
	ld p, s, v;
	cin >> n >> p >> s >> v;

	auto f = [=](ld c){return (s * (1 + 1 / c) / v) + (n * pow((log(n) / log(2)), c*sqrt(2)) / (p * 1e9)); };
	ld f1 = f(0), f2 = f(1), va = 1;
	while (f1 > f2) {
		va *= 2;
		f1 = f2;
		f2 = f(va);
	}
	
	double c = (double)gss(f, 0, va);
	double t = (double)f(c);
	printf("%.7f %.7f \n", t, c);

	return 0;
}