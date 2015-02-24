#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <bitset>
#include <algorithm>
#include <functional>
#include <string>
#include <math.h>

using namespace std;

#ifdef _MSC_VER
#define scanf scanf_s
#endif

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef long long ll;

int main(){
	int n;
	while (scanf("%d", &n) == 1) {

		// Read input
		vii polygon(n);
		int leftbound = 2000, rightbound = -2000;
		for (int i = 0; i < n; ++i) {
			int x, y;
			cin >> x >> y;
			if (y == 0) {
				leftbound = min(leftbound, x);
				rightbound = max(rightbound, x);
			}
			polygon[i] = ii(x, y);
		}

		// Calculate the area, centroid of the polygon:
		double A = 0.0, Cx = 0.0;
		for (int i = 0; i < n; ++i) {
			int x1 = polygon[i].first, y1 = polygon[i].second,
				x2 = polygon[(i + 1) % n].first, y2 = polygon[(i + 1) % n].second;
			int det = x1 * y2 - x2 * y1;
			A += det;
			Cx += (x1 + x2) * det;
		}
		A *= 0.5;
		Cx /= (6 * A);
		A = abs(A);

		// The x of the COG for a weight W is now given by:
		// p0.x * W / (W + A) + Cx * A / (W + A).
		// Solve == lb, == rb for W.
		double wx = polygon[0].first;
		if (Cx > wx) {
			Cx *= -1.0;
			wx *= -1.0;
			swap(leftbound, rightbound);
			leftbound *= -1;
			rightbound *= -1;
		} // Now Cx <= wx holds

		double lb = 0.0, rb = 1e100;
		bool unstable = false, extendsToInfinity = false;
		// Determine the lower bound:
		if (wx <= leftbound)
			unstable = true;
		else
			lb = max(0.0, A * (Cx - leftbound) / (leftbound - wx));

		// Determine the upperbound
		if (wx <= rightbound)
			extendsToInfinity = true;
		else {
			if (Cx > rightbound)
				unstable = true;
			else
				rb = A * (Cx - rightbound) / (rightbound - wx);
		}
		if (rb < lb && !extendsToInfinity) unstable = true;
		
		// Output
		if (unstable) cout << "unstable";
		else {
			cout << ((int)floor(lb)) << " .. ";
			if (!extendsToInfinity)
				cout << ((int)ceil(rb));
			else cout << "inf";
		}
		cout << endl;

	}

	return 0;
}