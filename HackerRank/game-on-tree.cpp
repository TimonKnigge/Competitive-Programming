#include <iostream> // strings/streams
#include <string>
#include <sstream>
#include <vector> // datastructures
#include <list>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <bitset>
#include <tuple> // quick compare
#include <cstdio> // utils
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

constexpr int  INF = 1e9+1; // < 1e9 - -1e9
constexpr ll LLINF = 1e18+1;

void dfs_root(int u, vvi &e, vi &par, vector<ll> &subsum, vector<ll> &a) {
	subsum[u] = a[u];
	for (int v : e[u]) {
		if (v == par[u]) continue;
		par[v] = u;
		dfs_root(v, e, par, subsum, a);
		subsum[u] += subsum[v];
	}
}

int main() {
	int n;
	scanf("%d", &n);
	
	vector<ll> a(n, 0);
	ll sum = 0LL;
	for (int i = 0; i < n; ++i) {
		scanf("%lld", &a[i]);
		sum += a[i];
	}
	
	vvi e(n, vi());
	for (int i = 0; i < n - 1; ++i) {
		int u, v;
		scanf("%d %d", &u, &v);
		u--; v--;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	
	vi par(n, -1);
	vector<ll> subsum(n, 0LL);
	dfs_root(0, e, par, subsum, a);

	ll worst = 0;
	for (int v : e[0]) if (worst < subsum[v]) worst = subsum[v];
	for (int u = 1; u < n; ++u) {
		ll thisworst = 0;
		for (int v : e[u])
			if (v == par[u]) continue;
			else if (thisworst < subsum[v])
				thisworst = subsum[v];
		if (thisworst < sum - subsum[u])
			thisworst = sum - subsum[u];
		if (thisworst < worst)
			worst = thisworst;
	}
	
	cout << (sum - worst) << endl;
	
	return 0;
}
