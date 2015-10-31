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
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

ll dfs1(int u, vvi &e, vb &special, vb &hasspecial, vi &p) {
	ll ret = 0LL;
	if (special[u]) hasspecial[u] = true;
	for (int v : e[u]) {
		if (v == p[u]) continue;
		p[v] = u;
		ll add = dfs1(v, e, special, hasspecial, p);
		if (hasspecial[v]) {
			hasspecial[u] = true;
			ret += add + 2;
		}
	}
	return ret;
}

bool better(pair<ll, int> p1, pair<ll, int> p2) {
	if (p1.first != p2.first) return p1.first > p2.first;
	else return p1.second < p2.second;
}

// double, single
pair<pair<ll, int>, pair<ll, int> > dfs2(int u, vvi &e, vb &special, vb &hasspecial, vi &p) {
	pair<ll, int> bestpair = {0LL, INF};
	pair<ll, int> bestpath = {0LL, INF};
	pair<ll, int> secondbestpath = {0LL, INF};
	if (special[u]) {
		bestpair.second = bestpath.second = u;
	}
	for (int v : e[u]) {
		if (p[u] == v) continue;
		if (!hasspecial[v]) continue;
		auto ret = dfs2(v, e, special, hasspecial, p);
		ret.second.first++;
		if (better(ret.first, bestpair))
			bestpair = ret.first;
		if (better(ret.second, bestpath)) {
			secondbestpath = bestpath;
			bestpath = ret.second;
		} else if (better(ret.second, secondbestpath))
			secondbestpath = ret.second;
	}
	pair<ll, int> newpath = {bestpath.first + secondbestpath.first,
				min(bestpath.second, secondbestpath.second)};
	if (better(newpath, bestpair)) bestpair = newpath;
	return {bestpair, bestpath};
}

int main() {
	
	int n, m;
	scanf("%d %d", &n, &m);
	vvi e(n, vi());
	for (int i = 0; i < n - 1; ++i) {
		int u, v;
		scanf("%d %d", &u, &v);
		u--; v--;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	
	vb special(n, false);
	int sp = 0;
	while (m--) {
		int x;
		scanf("%d", &x);
		x--;
		special[x] = true;
		sp = x;
	}
	
	vi p(n, -1);
	vb hasspecial(n, false);
	ll wght = dfs1(sp, e, special, hasspecial, p);
	
	// Find the longest path between any two nodes
	pair<ll, int> pt= dfs2(sp, e, special, hasspecial, p).first;
	ll mnpath = pt.first;
	cout << (1 + pt.second) << endl << (wght - mnpath) << endl;
	
	return 0;
}
