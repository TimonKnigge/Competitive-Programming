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
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

int gcd(int a, int b) {
	return (b == 0 ? a : gcd(b, a % b));
}

ll dot(int x1, int y1, int x2, int y2) {
	return ll(x1) * ll(x2) + ll(y1) * ll(y2);
}

int main() {
	
	int N;
	scanf("%d", &N);
	vi X1(N, 0), Y1(N, 0), X2(N, 0), Y2(N, 0);
	
	for (int i = 0; i < N; ++i) {
		scanf("%d %d %d %d", &X1[i], &Y1[i], &X2[i], &Y2[i]);
		if (X1[i] > X2[i] || (X1[i] == X2[i] && Y1[i] > Y2[i])) {
			swap(X1[i], X2[i]);
			swap(Y1[i], Y2[i]);
		}
	}
	
	map<ii, vi> by_slope;
	set<ii> pos_slopes;
	for (int i = 0; i < N; ++i) {
		int dx = X2[i] - X1[i];
		int dy = abs(Y2[i] - Y1[i]);
		int nx = X2[i] - X1[i];
		int ny = Y2[i] - Y1[i];
		if (dx == 0 || dy == 0) {
			ny /= max(dx, dy);
			nx /= max(dx, dy);
		} else {
			int g = gcd(dx, dy);
			nx /= g;
			ny /= g;
		}
		by_slope[{nx, ny}].push_back(i);
		if (ny > 0)
			pos_slopes.insert({nx, ny});
	}
	
	ll ans = 0LL;
	for (ii ps : pos_slopes) {
		int dx1 = ps.first;
		int dy1 = ps.second;
		int dx2 = dy1;
		int dy2 = -dx1;
		
		vi &s1 = by_slope[{dx1, dy1}];
		vi &s2 = by_slope[{dx2, dy2}];
		
		vector<long double> ds1, ds2;
		for (int i = 0; i < int(s1.size()); ++i)
			for (int j = i + 1; j < int(s1.size()); ++j) {
				int x1 = X1[s1[i]];
				int y1 = Y1[s1[i]];
				int x2 = X2[s1[i]];
				int y2 = Y2[s1[i]];
				int x3 = X1[s1[j]];
				int y3 = Y1[s1[j]];
				
				ld f = ld(dot(x3-x1,y3-y1,x2-x1,y2-y1)) / ld(dot(x2-x1,y2-y1,x2-x1,y2-y1));

				ld sqx = ld(x1) + f * ld(x2 - x1) - ld(x3);
				ld sqy = ld(y1) + f * ld(y2 - y1) - ld(y3);
				ds1.push_back(sqx * sqx + sqy * sqy);
			}
		for (int i = 0; i < int(s2.size()); ++i)
			for (int j = i + 1; j < int(s2.size()); ++j) {
				int x1 = X1[s2[i]];
				int y1 = Y1[s2[i]];
				int x2 = X2[s2[i]];
				int y2 = Y2[s2[i]];
				int x3 = X1[s2[j]];
				int y3 = Y1[s2[j]];
				
				ld f = dot(x3-x1,y3-y1,x2-x1,y2-y1) / ld(dot(x2-x1,y2-y1,x2-x1,y2-y1));
				ld sqx = ld(x1) + f * ld(x2 - x1) - ld(x3);
				ld sqy = ld(y1) + f * ld(y2 - y1) - ld(y3);
				ds2.push_back(sqx * sqx + sqy * sqy);
			}
		
		sort(ds1.begin(), ds1.end());
		sort(ds2.begin(), ds2.end());
		
		ld EPSILON = 1e-7;
		int l1 = 0, r1 = 0;
		for (int i = 0; i < int(ds2.size()); ++i) {
			
			while (l1 < int(ds1.size())
				&& ds1[l1] + EPSILON < ds2[i]) ++l1;
			if (l1 > r1) r1 = l1;
			while (r1 < int(ds1.size())
				&& ds1[r1] < ds2[i] + EPSILON) ++r1;
			
			if (l1 < int(ds1.size())
				&& abs(ds1[l1] - ds2[i]) < 2 * EPSILON)
				ans += r1 - l1;
		}
	}
	
	cout << ans << endl;
	
	return 0;
}
