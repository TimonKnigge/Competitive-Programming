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

void dfs(int u, vvi &E, vi &C, vi &edges, vi &size) {
	
	for (int v : E[u]) {
		++edges[C[u]];
		if (C[v] == -1) {
			++size[C[u]];
			C[v] = C[u];
			dfs(v, E, C, edges, size);
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N, M;
	cin >> N >> M;
	
	vvi E(N, vi());
	while (M--) {
		int x, y;
		cin >> x >> y;
		--x;
		--y;
		E[x].push_back(y);
		E[y].push_back(x);
	}
	
	vi C(N, -1LL);
	vi edges, size;
	
	for (int i = 0; i < N; ++i)
		if (C[i] == -1LL) {
			C[i] = edges.size();
			edges.push_back(0);
			size.push_back(1);
			dfs(i, E, C, edges, size);
		}
	
	int ans = 0;
	for (size_t i = 0; i < edges.size(); ++i) {
		edges[i] /= 2;
		if (edges[i] < size[i])
			++ans;
	}
	
	cout << ans << endl;
	
	return 0;
}
