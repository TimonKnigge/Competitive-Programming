#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pl;
typedef pair<int, pl> ipl;
typedef vector<pl> vpl;
typedef vector<ipl> vipl;

bool colinear(pl p1, pl p2) {
	return ((p1.first * p2.second - p2.first * p1.second) == 0);
}

ll dsq(pl p1) {
	return p1.first * p1.first + p1.second * p1.second;
}

bool angle_cmp(ipl l, ipl r) {
	if (colinear(l.second, r.second)) {
		ll d1 = dsq(l.second), d2 = dsq(r.second);
		if (d1 != d2)
			return d1 < d2;
		else
			return l.first < r.first;
	}
	else{
		return (atan2((double)l.second.second, (double)l.second.first)
			- atan2((double)r.second.second, (double)r.second.first)) < 0;
	}
}

int main() {
	int n;
	ll x0, y0;
	cin >> n >> x0 >> y0;

	vipl pts(n);
	for (int i = 0; i < n; ++i) {
		ll x, y;
		cin >> x >> y;
		x -= x0; y -= y0;
		if (x < 0) {
			x = -x;
			y = -y;
		}
		if (x == 0)
			y = abs(y);
		pts[i] = ipl(i, pl(x, y));
	}

	sort(pts.begin(), pts.end(), angle_cmp);

	ll shots = 0;
	for (int i = 0; i < n; ++i) {
		shots++;
		pl c = pts[i].second;
		while (i < n - 1 && colinear(c, pts[i + 1].second))
			i++;
	}

	cout << shots << endl;

	return 0;
}