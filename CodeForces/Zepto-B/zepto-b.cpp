#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

typedef long long ll;

vector<ll> a, lop, madd;
int n, ttm;

ll find(int v) {
	int lc = 2 * v + 1, rc = 2 * v + 2;
	if (lc >= ttm - 1) return 0;

	find(lc);
	find(rc);

	ll lop_lc = lop[lc] + a[lc],
		lop_rc = lop[rc] + a[rc];
	ll diff = abs(lop_lc - lop_rc);
	lop[v] = max(lop_lc, lop_rc);
	madd[v] = diff + madd[lc] + madd[rc];
}

int main() {
	cin >> n;
	ttm = (1 << (n + 1));
	a.assign(ttm - 1, 0);
	for (int i = 1; i < ttm - 1; ++i) {
		cin >> a[i];
	}

	lop.assign(ttm - 1, 0);
	madd.assign(ttm - 1, 0);

	find(0);
	cout << madd[0] << endl;
	return 0;
}