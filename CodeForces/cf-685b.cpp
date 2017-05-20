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

void dfs(int u, vi &p, vvi &c, vi &centroid, vi &size) {
	size[u] = 1;
	int lsub = -1;
	for (ll v : c[u]) {
		dfs(v, p, c, centroid, size);
		size[u] += size[v];
		if (lsub == -1 || size[lsub] < size[v])
			lsub = v;
	}
	
	if (lsub == -1 || size[lsub] <= size[u] / 2) {
		centroid[u] = u;
	} else {
		centroid[u] = centroid[lsub];
		while (size[u] - size[centroid[u]] > size[u] / 2)
			centroid[u] = p[centroid[u]];
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, q;
	cin >> n >> q;
	
	vi p(n, -1);
	vvi c(n, vi());
	for (int i = 1; i < n; ++i) {
		cin >> p[i];
		--p[i];
		c[p[i]].push_back(i);
	}
	
	vi centroid(n, -1), size(n, 0);
	dfs(0, p, c, centroid, size);
	
	while (q--) {
		int v;
		cin >> v;
		cout << centroid[v-1]+1 << '\n';
	}
	
	return 0;
}
