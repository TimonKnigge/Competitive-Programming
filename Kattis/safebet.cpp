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

// FENWICK TREE
template <class T>
struct FenwickTree {		// use 1 based indices!!!
	int n; vector<T> tree;
	FenwickTree(int n) : n(n) { tree.assign(n + 1, 0); }
	T query(int l, int r) { return query(r) - query(l - 1); }
	T query(int r) {
		T s = 0;
		for(; r > 0; r -= (r & (-r))) s += tree[r];
		return s;
	}
	void update(int i, T v) {
		for(; i <= n; i += (i & (-i))) tree[i] += v;
	}
};
// -FENWICK TREE

void ansy(int t) {
	cout << "Case " << t << ": 0\n";
}
void ansn(int t, ll k, int x, int y) {
	cout << "Case " << t << ": " << k << " " << x << " " << y << '\n';
}
void ansi(int t) {
	cout << "Case " << t << ": impossible\n";
}

constexpr bool FORWARD = false, BACKWARD = true;
constexpr int UP = 0, LEFT = 1, DOWN = 2, RIGHT = 3;

int nextdir(int dir, bool type) {
	if (dir ==   UP) return type ? LEFT : RIGHT;
	if (dir == DOWN) return type ? RIGHT : LEFT;
	if (dir == LEFT) return type ? UP : DOWN;
			 return type ? DOWN : UP;
}

// Run a ray starting at (_pr, _pc) in direction _dir
// resulting lines are stored in hlines and vlines.
ii run(int _pr, int _pc, int _dir,
	vvi &rowpos, vvi &colpos, map<ii, int> &pos,
	vvii &hlines, vvii &vlines) {
	
	int R = rowpos.size(), C = colpos.size();
	hlines.assign(R, vii());
	vlines.assign(C, vii());
	
	int pr = _pr, pc = _pc, dir = _dir;
	do {	
		int npr = pr, npc = pc, ndir = dir;
		switch (dir) {
		case UP:
		{
			int i = int(lower_bound(colpos[pc].begin(), colpos[pc].end(), pr) - colpos[pc].begin());
			while (i >= 0 && (i == int(colpos[pc].size()) || colpos[pc][i] >= pr)) --i;
			if (i >= 0) {
				npr = colpos[pc][i];
				ndir = nextdir(dir, pos[{npr, npc}]);
			} else npr = -1;
		}
			break;
		case DOWN:
		{
			int i = int(upper_bound(colpos[pc].begin(), colpos[pc].end(), pr) - colpos[pc].begin());
			if (i < int(colpos[pc].size())) {
				npr = colpos[pc][i];
				ndir = nextdir(dir, pos[{npr, npc}]);
			} else npr = R;
		}	
			break;
		case LEFT:
		{
			int i = int(lower_bound(rowpos[pr].begin(), rowpos[pr].end(), pc) - rowpos[pr].begin());
			while (i >= 0 && (i == int(rowpos[pr].size()) || rowpos[pr][i] >= pc)) --i;
			if (i >= 0) {
				npc = rowpos[pr][i];
				ndir = nextdir(dir, pos[{npr, npc}]);
			} else npc = -1;
		}
			break;
		default:
		{
			int i = int(upper_bound(rowpos[pr].begin(), rowpos[pr].end(), pc) - rowpos[pr].begin());
			if (i < int(rowpos[pr].size())) {
				npc = rowpos[pr][i];
				ndir = nextdir(dir, pos[{npr, npc}]);
			} else npc = C;
		}
			break;
		}
		
		// Only save non-trivial lines
		if (dir == UP || dir == DOWN) {
			if (min(pr, npr) + 1 < max(pr, npr))
				vlines[pc].push_back({1+min(pr, npr), -1+max(pr, npr)});
		} else {
			if (min(pc, npc) + 1 < max(pc, npc))
				hlines[pr].push_back({1+min(pc, npc), -1+max(pc, npc)});
		}
		pr = npr;
		pc = npc;
		dir = ndir;
	} while (pr >= 0 && pc >= 0 && pr < R && pc < C);
	
	return {pr, pc};
}

using iii = pair<ii, int>;
ll sweep(vvii &rowl, vvii &coll, vvi &rowpos, vvi &colpos, map<ii,int> &pos, ii &lexpos) {
	int R = rowpos.size(), C = colpos.size();
	
	FenwickTree<int> ft(C);
	
	vvi entries(R, vi()), exits(R, vi());
	
	for (int c = 0; c < C; ++c) {
		for (ii ln : coll[c]) {
			entries[ln.first].push_back(c);
			exits[ln.second] .push_back(c);
		}
	}
	
	ll ans = 0;
	lexpos = {INF, INF};
	for (int r = 0; r < R; ++r) {
		
		// handle entries
		for (int c : entries[r])
			ft.update(c + 1, 1);
		
		ii minins = {INF, INF};
		for (ii ln : rowl[r]) {
			ll inc = ft.query(1+ln.first, 1+ln.second);
			if (inc > 0 && ln.first < minins.first)
				minins = ln;
			ans += ll(inc);
		}
		
		if (lexpos.first == INF && minins.first != INF) {
			// There is an intersection in the interval [lv,rv]
			int lv = minins.first, rv = minins.second;
			while (lv < rv) {
				int m = (lv + rv) / 2;
				int c = ft.query(1+lv,1+m);
				if (c == 0)	lv = m + 1;
				else		rv = m;
			}
			lexpos = {r, lv};
		}
		
		// handle exists
		for (int c : exits[r])
			ft.update(c + 1, -1);
	}
	
	return ans;
}

// DEBUG
void printlines(string n, vvii &hlines) {
	cerr << n << endl;
	for (int i = 0; i < hlines.size(); ++i){

	bool b = false;
		cerr << i<<": ";
		for (ii v : hlines[i]) {b=true;cerr << v.first << ','<<v.second<<' ';
		}if(b)cerr << endl;
	}
}
//-DEBUG

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int R, C, M, N, tcase = 0;
	while (cin >> R) {
		++tcase;
		
		cin >> C >> M >> N;
		// M / N \
		
		map<ii, int> pos;
		vvi rowpos(R, vi()), colpos(C, vi());
		while (M--) {
			int ri, ci;
			cin >> ri >> ci;
			--ri;
			--ci;
			rowpos[ri].push_back(ci);
			colpos[ci].push_back(ri);
			pos[{ri, ci}] = FORWARD;
		}
		while (N--) {
			int ri, ci;
			cin >> ri >> ci;
			--ri;
			--ci;
			rowpos[ri].push_back(ci);
			colpos[ci].push_back(ri);
			pos[{ri, ci}] = BACKWARD;
		}
		
		
		for (int i = 0; i < R; ++i)
			sort(rowpos[i].begin(), rowpos[i].end());
		for (int i = 0; i < C; ++i)
			sort(colpos[i].begin(), colpos[i].end());
		
		// Is it always possible?
		vvii hlines, vlines;
		ii p = run(0, -1, RIGHT, rowpos, colpos, pos, hlines, vlines);
		int pr = p.first, pc = p.second;

		if (pr == R - 1 && pc == C) {
			ansy(tcase);
			cout << flush;
			continue;
		}
		// It's not always possible, so also send a ray
		// in reverse
		vvii rhlines, rvlines;
		run(R - 1, C, LEFT, rowpos, colpos, pos, rhlines, rvlines);
	
//		printlines("hlines", hlines);
//		printlines("vlines", vlines);
//		printlines("rhlines", rhlines);
//		printlines("rvlines", rvlines);
		
		ii s1, s2;
		ll ans = 0;
		ans += sweep(rhlines,  vlines, rowpos, colpos, pos, s1);
		ans += sweep( hlines, rvlines, rowpos, colpos, pos, s2);
		ii sf = min(s1, s2);
		if (ans == 0)	ansi(tcase);
		else 		ansn(tcase, ans, 1+sf.first, 1+sf.second);
		cout << flush;
	}
	
	return 0;
}
