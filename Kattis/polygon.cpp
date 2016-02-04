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

auto now(){ return chrono::high_resolution_clock::now(); }
using TP = decltype(now());	// time point
auto duration(TP t1, TP t2){
	return chrono::duration_cast<chrono::milliseconds>(t2-t1).count();
}
auto since(TP t1) { return duration(t1, now()); }

ll det(int x1, int y1, int x2, int y2) {
	return ll(x1)*ll(y2) - ll(x2)*ll(y1);
}
ll det(int x1, int y1, int x2, int y2, int x3, int y3) {
	return det(x1 - x3, y1 - y3, x2 - x3, y2 - y3);
}
ll online(int x1, int y1, int x2, int y2, int px, int py) {
	if (det(x2, y2, px, py, x1, y1) != 0) return false;
	return (min(x1,x2) <= px && px <= max(x1,x2)
		&& min(y1,y2) <= py && py <= max(y1,y2));
}
ll intersect(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
	ll d1 = det(x2, y2, x3, y3, x1, y1);
	ll d2 = det(x2, y2, x4, y4, x1, y1);
	if (d1 * d2 > 0) return false;
	d1 = det(x4, y4, x1, y1, x3, y3);
	d2 = det(x4, y4, x2, y2, x3, y3);
	return (d1 * d2 <= 0);
}

int main() {
	
	auto start = now();
	
	vi N;
	vvi X, Y;
	while (true) {
		int n;
		scanf("%d", &n);
		if (n == 0) break;
		
		N.push_back(n);
		X.push_back(vi());
		Y.push_back(vi());
		X.back().assign(n, 0);
		Y.back().assign(n, 0);
		
		for (int i = 0; i < n; ++i) {
			scanf("%d %d", &X.back()[i], &Y.back()[i]);
		}
	}
	
	int T = N.size();
	int time_per_case = 3800 / T;
	for (int t = 1; t <= T; ++t) {
		int n = N[t-1];
		vi &x = X[t-1];
		vi &y = Y[t-1];
		
		bool simple = true;
		int rs = 0;
		if (n > 2) while (simple) {
			
			int i = rand()%n;
			int j = rand()%n;
			if (i == j) j = (j + 1) % n;
			
			if ((i+1)%n == j || (j+1)%n == i) {
				if ((j+1)%n == i) swap(i, j); // i in front
				if (det(x[i],y[i],x[j],y[j],x[(j+1)%n],y[(j+1)%n]) == 0) {
					simple = simple && !(
						online(x[i],y[i],x[j],y[j],x[(j+1)%n],y[(j+1)%n])
					||	online(x[j],y[j],x[(j+1)%n],y[(j+1)%n],x[i],y[i]));
				}
			} else {
				simple = simple && !intersect(
					x[i],		y[i],
					x[(i+1)%n],	y[(i+1)%n],
					x[j],		y[j],
					x[(j+1)%n],	y[(j+1)%n]);
			}
			
			++rs;
			if ((rs&15) == 15) {
				if (since(start) > t * time_per_case)
					break;
			}
		}
		printf(simple ? "YES\n" : "NO\n");
	}
	
	return 0;
}
