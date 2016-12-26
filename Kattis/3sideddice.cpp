#include <iostream> 
#include <cstdio>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <bitset>
#include <numeric>
#include <iterator>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <cassert>

using namespace std;
using ll = long long;
using ld = long double;
using ii = pair<ll, ll>;
using vi = vector<ll>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

constexpr ll M = 10000;
#define third(x) (M - x.first - x.second)

// signed(!) determinants
ll sgn(ll v) { return (v == 0 ? 0 : (v > 0 ? 1 : -1)); }
ll det(ii p1, ii p2, ii p3) {
	ll r = 0LL;
	r += p1.first * p2.second * third(p3);
	r += p2.first * p3.second * third(p1);
	r += p3.first * p1.second * third(p2);
	r -= p1.first * p3.second * third(p2);
	r -= p3.first * p2.second * third(p1);
	r -= p2.first * p1.second * third(p3);
	return sgn(r);
}
ll det(ii p1, ii p2) {
	return sgn(p1.first*p2.second - p1.second*p2.first);
}
bool cont(ii p1, ii p2, ii p) {
	return min(p1.first, p2.first) <= p.first &&
		p.first <= max(p1.first, p2.first) &&
		min(p1.second, p2.second) <= p.second &&
		p.second <= max(p1.second, p2.second);
}
ii sub(ii p1, ii p2) {
	return {p1.first-p2.first, p1.second-p2.second};
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int x, y, z;
	while (cin >> x >> y >> z) {
		if (x + y + z == 0) break;
		
		vii pts(1, {x, y});
		for (int i = 0; i < 2; ++i) {
			cin >> x >> y >> z;
			pts.push_back({x, y});
		}
		sort(pts.begin(), pts.end());
		pts.erase(unique(pts.begin(), pts.end()), pts.end());
		
		cin >> x >> y >> z;
		ii p = {x, y};
		
		if (det(pts[0], pts[1], pts[2]) == 0LL) {
			// Remove one point
			pts.erase(pts.begin() + 1);
		}
		
		switch (pts.size()) {
			case 1:
			{
				cout << (p == pts[0] ? "YES" : "NO") << endl;
				break;
			}
			case 2:
			{
				ll d = det(pts[0], pts[1], p);
				cout << (d == 0LL && cont(pts[0], pts[1], p)
						&& p != pts[0] && p != pts[1]
						? "YES" : "NO") << endl;
				break;
			}
			case 3:
			{
				bool y = true;
				y = y && det(sub(pts[1], pts[0]), sub(p, pts[0])) * det(sub(pts[2], pts[0]), sub(p, pts[0])) < 0LL;
				y = y && det(sub(pts[2], pts[1]), sub(p, pts[1])) * det(sub(pts[0], pts[1]), sub(p, pts[1])) < 0LL;
				y = y && det(sub(pts[0], pts[2]), sub(p, pts[2])) * det(sub(pts[1], pts[2]), sub(p, pts[2])) < 0LL;
				cout << (y ? "YES" : "NO") << endl;
				break;
			}
		}
	}
	
	return 0;
}
