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

struct point { ll x, y; };
bool operator==(const point &l, const point &r) {
	return l.x == r.x && l.y == r.y; }

ll dsq(const point &p1, const point &p2) {
	return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y); }
ll det(ll x1, ll y1, ll x2, ll y2) {
	return x1 * y2 - x2 * y1; }
ll det(const point &p1, const point &p2, const point &d) {
	return det(p1.x - d.x, p1.y - d.y, p2.x - d.x, p2.y - d.y); }
bool comp_lexo(const point &l, const point &r) {
	return l.y != r.y ? l.y < r.y : l.x < r.x; }
bool comp_angl(const point &l, const point &r, const point &c) {
	ll d = det(l, r, c);
	if (d != 0) return d > 0;
	else return dsq(c, l) < dsq(c, r);
}
int mod(int a, int b) { return (((a%b)+b)%b); }


int main() {
	
	int N;
	scanf("%d", &N);
	
	vector<point> pts(N, {0, 0});
	for (int i = 0; i < N; ++i) {
		int x, y;
		scanf("%d %d", &x, &y);
		pts[i] = {x, y};
	}
	
	// Find the left most point
	int pivot = 0;
	vi ps(N, 0);
	for (int i = 0; i < N; ++i) {
		ps[i] = i;
		if (comp_lexo(pts[i], pts[pivot])) pivot = i;
	}
	ps[0] = pivot;
	ps[pivot] = 0;
	
	sort(ps.begin()+1, ps.end(), [&pts, &pivot](int l, int r) {
		return comp_angl(pts[l], pts[r], pts[pivot]); });
	
	// Fix final points
	int j = N - 1;
	while (j > 0 && det(pts[ps[j - 1]], pts[ps[N - 1]], pts[ps[0]]) == 0) --j;
	for (int l = j, r = N - 1; l < r; ++l, --r) swap(ps[l], ps[r]);

	int best = INF;
	
	for (int _j = 0; _j < 2; ++_j, reverse(ps.begin()+1, ps.end())) {
		vector<vector<ll> > dp[2];
		dp[0].assign(2, vector<ll>(N, INF));
		dp[1].assign(2, vector<ll>(N, INF));
		
		// dp[lastused][free][0..i]
		dp[0][0][0] = 0;
		dp[0][1][0] = 1;
		dp[1][1][0] = dp[1][0][0] = 1;
		
		int i = 0;
		while (i < N) {
			int r = i;
			while (r + 1 < N && det(
				pts[ps[i]],
				pts[ps[r]],
				pts[ps[r+1]]) == 0)
				++r;
			
			if (i == r) break;
			
			// [i, r] is maximal wrt colinearity
			int ibt = max(0, r - i - 1);
			dp[1][0][r] = 1 + min(dp[0][0][i], dp[1][0][i]);
			dp[1][1][r] = 1 + min(dp[0][1][i], dp[1][1][i]);
			if (ibt > 1) {
				dp[0][0][r] = dp[1][0][r];
				dp[0][1][r] = dp[1][1][r];
			} else if (ibt == 0) {
				dp[1][0][r] = min(dp[1][0][r], dp[1][1][i]);
				dp[1][1][r] = min(dp[1][1][r],1+dp[1][0][i]);
				dp[0][0][r] = min(dp[1][0][i], min(dp[1][1][i], dp[0][1][i]));
				dp[0][1][r] = min(dp[1][1][i], min(1+dp[1][0][i], 1+dp[0][0][i]));
			} else if (ibt == 1) {
				dp[0][0][r] = min(1 + dp[1][0][i], dp[1][1][i]);
				dp[0][1][r] = 1 + min(dp[0][1][i], dp[1][0][i]);
			}
			
			i = r;
		}
		best =  min(ll(best), 
			min(dp[0][1][N-1],
			min(dp[1][0][N-1], dp[1][1][N-1])));
	}
	
	cout << best << endl;
	
	return 0;
}
