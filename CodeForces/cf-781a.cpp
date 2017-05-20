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

void dfs(int u, int p, vvi &E, vi &col) {
	int nxt = 0;
	for (ll v : E[u]) {
		if (v == p) continue;
		while (nxt == col[u] || (p != -1 && nxt == col[p]))
			++nxt;
		col[v] = nxt;
		dfs(v, u, E, col);
		++nxt;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N;
	cin >> N;
	vvi E(N, vi());
	for (int i = 1; i < N; ++i) {
		int x, y;
		cin >> x >> y;
		--x; --y;
		E[x].push_back(y);
		E[y].push_back(x);
	}
	
	vi col(N, -1);
	col[0] = 0;
	dfs(0, -1, E, col);
	
	int k = 0;
	for (ll v : col) k = max(k, int(v) + 1);
	
	cout << k << endl;
	for (int i = 0; i < N; ++i)
		cout << col[i]+1 << " \n"[i + 1 == N];
	
	return 0;
}
