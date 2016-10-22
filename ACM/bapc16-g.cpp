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

ll mn(ii f, ii s) {
	return abs(f.first-s.first)+abs(f.second-s.second);
}

ll det(ll x1, ll y1, ll x2, ll y2) {
	return x1*y2-x2*y1;
}
ll det(ll cx, ll cy, ll x1, ll y1, ll x2, ll y2) {
	return det(x1-cx, y1-cy, x2-cx, y2-cy);
}

bool contained(ii p1, ii p2, ii c) {
	return (min(p1.first, p2.first) <= c.first)
		&& (min(p1.second, p2.second) <= c.second)
		&& (max(p1.first, p2.first) >= c.first)
		&& (max(p1.second, p2.second) >= c.second);
}

// l1,l2 is guaranteed a line
bool find_overlap(ii l1, ii l2, ii p1, ii p2, pair<ii, ii> &res) {
	if (p1 == p2) {
		if (det(p1.first, p1.second, l1.first, l1.second, l2.first, l2.second) != 0) return false;
		if (!contained(l1, l2, p1)) return false;
		res = {p1, p2};
		return true;
	}
	// p1,p2 is guaranteed a line
	if (p1 > p2) swap(p1, p2);
	if (l1 > l2) swap(l1, l2);
	
//		cerr << "Trying to intersect " << p1.first << ',' << p1.second << "->" << p2.first << ',' << p2.second << " with ";
//		cerr << l1.first << ',' << l1.second << "->" << l2.first << ',' << l2.second << endl;

	if ((l1.second-l2.second)*(p1.second-p2.second) > 0) {
		// lines are parallel, find overlap
		ll coeff = l1.second < l2.second ? 1 : -1;
		ll ly = l1.second + l1.first * -coeff;
		ll py = p1.second + p1.first * -coeff;
		if (ly != py) return false;
		
		// lines have same y intercept
		if (max(p1.first, l1.first) > min(p2.first, l2.first)) return false;
		res.first.first = max(p1.first, l1.first);
		res.second.first = min(p2.first, l2.first);
		res.first.second = ly + coeff * res.first.first;
		res.second.second = ly + coeff * res.second.first;
		return true;
	} else {
		// lines are not parallel, find intersection point
		if ((((p1.first+p1.second) - (l1.first+l1.second))%2+2)%2 != 0) return false;
		
		ll lc = l1.second < l2.second ? 1 : -1;
		ll pc = p1.second < p2.second ? 1 : -1;
		ll ly = l1.second + l1.first * -lc;
		ll py = p1.second + p1.first * -pc;
		
		ll nx = -(ly - py) / (lc - pc);
		ll ny = ly + lc * nx;
		
		if (!contained(l1, l2, {nx, ny})) return false;
		if (!contained(p1, p2, {nx, ny})) return false;
		res = {{nx, ny}, {nx, ny}};
		return true;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N;
	cin >> N;
	vi X(N, 0LL), Y(N, 0LL), D(N, 0LL);
	for (int i = 0; i < N; ++i)
		cin >> X[i] >> Y[i] >> D[i];
	
	set<pair<ii, ii>> pos[2];
	pos[0].insert({{X[0] - D[0], Y[0]}, {X[0], Y[0] - D[0]}});
	pos[0].insert({{X[0] - D[0], Y[0]}, {X[0], Y[0] + D[0]}});
	pos[0].insert({{X[0] + D[0], Y[0]}, {X[0], Y[0] - D[0]}});
	pos[0].insert({{X[0] + D[0], Y[0]}, {X[0], Y[0] + D[0]}});
	
	for (int i = 1; i < N; ++i) {
		pos[i&1].clear();
		for (pair<ii, ii> ln : pos[1^i&1]) {
			ii lx = ln.first, rx = ln.second;
			if (lx > rx) swap(lx, rx);
			
			// if it is a point, just shortcut
			if (lx == rx) {
				if (mn(lx, {X[i], Y[i]}) == D[i])
					pos[i&1].insert({lx, rx});
			} else {
				pair<ii, ii> res;
				if (find_overlap(lx, rx, {X[i] - D[i], Y[i]}, {X[i], Y[i] - D[i]}, res)) pos[i&1].insert(res);
				if (find_overlap(lx, rx, {X[i] - D[i], Y[i]}, {X[i], Y[i] + D[i]}, res)) pos[i&1].insert(res);
				if (find_overlap(lx, rx, {X[i] + D[i], Y[i]}, {X[i], Y[i] - D[i]}, res)) pos[i&1].insert(res);
				if (find_overlap(lx, rx, {X[i] + D[i], Y[i]}, {X[i], Y[i] + D[i]}, res)) pos[i&1].insert(res);
			}
		}
//		cout << i << ' ' << pos[1^i&1].size() << " to " << pos[i&1].size() << endl;
	}
	
	set<pair<ii, ii>> &res = pos[(N-1)&1];
	ii ans = {-1, -1};
	bool f = false, p = true;
	for (pair<ii, ii> v : res) {
		if (v.first != v.second) p = false;
		if (f && v.first != ans) p = false;
		if (!f) { f = true; ans = v.first; }
	}
	
	if (!f) cout << "impossible" << endl;
	else if (!p) cout << "uncertain" << endl;
	else cout << ans.first << ' ' << ans.second << endl;
	
	return 0;
}
