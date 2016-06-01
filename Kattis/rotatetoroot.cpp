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

void dfs(int u, vi &l, vi &r, vi &down) {
	down[u] = 1;
	if (l[u] >= 0) 
		dfs(l[u], l, r, down),
		down[u] = max(down[u], down[l[u]] + 1);
	if (r[u] >= 0) 
		dfs(r[u], l, r, down),
		down[u] = max(down[u], down[r[u]] + 1);
}

void dfs2(int u, vi &p, vi &l, vi &r, vi &down, vi &ans,
	ll lm, ll la, ll rm, ll ra) {
	
	ll lsz = l[u] >= 0LL ? down[l[u]] : 0LL;
	ll rsz = r[u] >= 0LL ? down[r[u]] : 0LL;
	
	ans[u] = 1LL + max(max(lm, lsz + la), max(rm, rsz + ra));
	
	if (l[u] >= 0LL)
		dfs2(l[u], p, l, r, down, ans,
			lm, la, max(rm, rsz + ra + 1), ra + 1);
	if (r[u] >= 0LL)
		dfs2(r[u], p, l, r, down, ans,
			max(lm, lsz + la + 1), la + 1, rm, ra);
}

int main() {
	
	while (true) {
		int N;
		scanf("%d", &N);
		if (N == 0) break;
		
		vi p(N, -1LL), l(N, -1LL), r(N, -1LL);
		for (int i = 0; i < N; ++i) {
			int li, ri;
			scanf("%d %d", &li, &ri);
			--li; --ri;
			if (li >= 0) p[li] = i;
			if (ri >= 0) p[ri] = i;
			l[i] = li;
			r[i] = ri;
		}
		
		int root = 0;
		while (p[root] >= 0 && root + 1 < N) ++root;
		
		vi down(N, 0LL);
		dfs(root, l, r, down);
		
		vi ans(N, 0LL);
		dfs2(root, p, l, r, down, ans, 0LL, 0LL, 0LL, 0LL);
		
		for (int i = 0; i < N; ++i)
			cout << ans[i] << '\n';
	}
	
	return 0;
}
