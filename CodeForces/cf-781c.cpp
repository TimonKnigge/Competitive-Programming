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

void dfs(int u, int p, vvi &E, vi &res, vb &vis) {
	if (vis[u]) return;
	vis[u] = true;
	res.push_back(u);
	for (ll v : E[u]) {
		if (v == p) continue;
		if (vis[v]) continue;
		dfs(v, u, E, res, vis);
		res.push_back(u);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, m, k;
	cin >> n >> m >> k;
	
	vvi E(n, vi());
	set<ii> seen;
	while (m--) {
		int x, y;
		cin >> x >> y;
		--x; --y;
		if (x == y) continue;
		if (x > y) swap(x, y);
		if (seen.find({x, y}) != seen.end()) continue;
		seen.insert({x, y});
		E[x].push_back(y);
		E[y].push_back(x);
	}
	
	vi res;
	vb vis(n, false);
	dfs(0, -1, E, res, vis);
	
	int cur = 0;
	int mx = (n + n + k - 1) / k;
	cerr << "mx = " << mx << endl;
	
	for (int i = 0; i < k; ++i) {
		if (cur == res.size())
			cout << "1 1" << endl;
		else {
			int c = min(mx, int(res.size() - cur));
			cout << c;
			for (int j = 0; j < c; ++j)
				cout << ' ' << res[cur++]+1;
			cout << '\n';
		}
	}
	
	return 0;
}
