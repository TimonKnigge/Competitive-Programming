#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <functional>
#include <cmath>

using namespace std;

typedef long double ld;
typedef pair<ld, ld> pp;
typedef vector<pp> vii;

#define RES_PHI (2 - ((1.0 + sqrt(5)) / 2.0))
#define EPSILON 1e-8

ld x1, Y1, x2, y2, xg, yg, xd, yd;
ld vwalk, vbike;

ld euclid(ld p1x, ld p1y, ld p2x, ld p2y) {
	return sqrt((p2x - p1x) * (p2x - p1x) + (p2y - p1y) * (p2y - p1y));
}

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
	return min(lbv, min(rbv, min(mlbv, mrbv))); // any bound should do
}

ld dgss(function<ld(ld)> gx1, function<ld(ld)> gy1, 
			function<ld(ld)> gx2, function<ld(ld)> gy2, 
			ld leftbound, ld rightbound,
			ld leftbound2, ld rightbound2) {
	ld lb = leftbound, rb = rightbound, mlb = lb + RES_PHI * (rb - lb), mrb = rb + RES_PHI * (lb - rb);
	function<ld(ld)> f = [=](ld d){ return euclid(xg, yg, gx1(d), gy1(d)) / vwalk
		+ gss([=](ld e){return euclid(gx1(d), gy1(d), gx2(e), gy2(e)) / vbike 
							 + euclid(gx2(e), gy2(e), xd, yd) / vwalk; }, leftbound2, rightbound2); };
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
	return min(lbv, min(rbv, min(mlbv, mrbv))); // any bound should do
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// Take input
	cin >> vwalk >> vbike;
	cin >> x1 >> Y1 >> x2 >> y2 >> xg >> yg >> xd >> yd;

	int n; cin >> n;
	vii station(n);
	for (int i = 0; i < n; ++i) {
		int xst, yst;
		cin >> xst >> yst;
		station[i] = make_pair(xst, yst);
	}

	//	-4	=>	TOP
	//	-3	=>	BOTTOM
	//	-2	=>	LEFT
	//	-1	=>	RIGHT
	ld best = 1e200;
	for (int i = -4; i < n; ++i) {
		for (int j = -4; j < n; ++j) {
			if (i >= 0 && j >= 0) {
				ld gtos = euclid(xg, yg, station[i].first, station[i].second),
					stos = euclid(station[i].first, station[i].second, station[j].first, station[j].second),
					stod = euclid(station[j].first, station[j].second, xd, yd);
				ld tm = gtos / vwalk + stos / vbike + stod / vwalk;
				best = min(best, tm);
			}
			else if (i >= 0){
				int ii = i, jj = j;
				ld gtos = euclid(xg, yg, station[ii].first, station[ii].second) / vwalk;

				ld l, r, v = 0.0;
				if (jj <= -3){
					l = x1; r = x2;
					if (jj == -4)
						v = gss([=](ld d){return euclid(station[ii].first, station[ii].second, d, Y1) / vbike + euclid(d, Y1, xd, yd) / vwalk; },
						l, r);
					else v = gss([=](ld d){return euclid(station[ii].first, station[ii].second, d, y2) / vbike + euclid(d, y2, xd, yd) / vwalk; },
						l, r);
				}
				else{
					l = Y1, r = y2;
					if (jj == -2)
						v = gss([=](ld d){return euclid(station[ii].first, station[ii].second, x1, d) / vbike + euclid(x1, d, xd, yd) / vwalk; },
						l, r);
					else v = gss([=](ld d){return euclid(station[ii].first, station[ii].second, x2, d) / vbike + euclid(x2, d, xd, yd) / vwalk; },
						l, r);
				}

				best = min(best, gtos + v);
			}
			else if (j >= 0){
				int ii = i, jj = j;
				ld stod = euclid(xd, yd, station[jj].first, station[jj].second) / vwalk;

				ld l, r, v = 0.0;
				if (ii <= -3){
					l = x1; r = x2;
					if (ii == -4)
						v = gss([=](ld d){return euclid(station[jj].first, station[jj].second, d, Y1) / vbike + euclid(d, Y1, xg, yg) / vwalk; },
						l, r);
					else v = gss([=](ld d){return euclid(station[jj].first, station[jj].second, d, y2) / vbike + euclid(d, y2, xg, yg) / vwalk; },
						l, r);
				}
				else{
					l = Y1, r = y2;
					if (ii == -2)
						v = gss([=](ld d){return euclid(station[jj].first, station[jj].second, x1, d) / vbike + euclid(x1, d, xg, yg) / vwalk; },
						l, r);
					else v = gss([=](ld d){return euclid(station[jj].first, station[jj].second, x2, d) / vbike + euclid(x2, d, xg, yg) / vwalk; },
						l, r);
				}

				best = min(best, stod + v);
			}
			else {
				function<ld(ld)> gx1, gy1, gx2, gy2;
				ld l1, r1, l2, r2;
				switch (i) {
				case -4:
					gx1 = [](ld d){return d; };
					gy1 = [=](ld d){return Y1; };
					l1 = x1; r1 = x2;
					break;
				case -3:
					gx1 = [](ld d){return d; };
					gy1 = [=](ld d){return y2; };
					l1 = x1; r1 = x2;
					break;
				case -2:
					gx1 = [=](ld d){return x1; };
					gy1 = [](ld d){return d; };
					l1 = Y1; r1 = y2;
					break;
				case -1:
					gx1 = [=](ld d){return x2; };
					gy1 = [](ld d){return d; };
					l1 = Y1; r1 = y2;
					break;
				}
				switch (j) {
				case -4:
					gx2 = [](ld d){return d; };
					gy2 = [=](ld d){return Y1; };
					l2 = x1; r2 = x2;
					break;
				case -3:
					gx2 = [](ld d){return d; };
					gy2 = [=](ld d){return y2; };
					l2 = x1; r2 = x2;
					break;
				case -2:
					gx2 = [=](ld d){return x1; };
					gy2 = [](ld d){return d; };
					l2 = Y1; r2 = y2;
					break;
				case -1:
					gx2 = [=](ld d){return x2; };
					gy2 = [](ld d){return d; };
					l2 = Y1; r2 = y2;
					break;
				}
				best = min(best, dgss(gx1, gy1, gx2, gy2, l1, r1, l2, r2));
			}
		}
	}

	best = min(best, euclid(xd, yd, xg, yg) / vwalk);
	
	printf("%.7f \n", (double)best);

	return 0;
}