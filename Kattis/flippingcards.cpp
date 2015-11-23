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

int main() {
	
	int T;
	scanf("%d", &T);
	while (T--) {
		int n;
		scanf("%d", &n);
		
		vvi e(2 * n, vi());
		for (int i = 0; i < n; ++i) {
			int u, v;
			scanf("%d %d", &u, &v);
			u--; v--;
			e[u].push_back(v);
			e[v].push_back(u);
		}
		
		vb vis(2 * n, false);
		bool possible = true;
		for (int i = 0; i < 2 * n && possible; ++i) {
			if (vis[i]) continue;
			int edges = 0, component = 0;
			queue<int> q;
			q.push(i);
			while (!q.empty()) {
				int u = q.front(); q.pop();
				if (vis[u]) continue;
				vis[u] = true;
				component++;
				edges += e[u].size();
				for (int v : e[u]) {
					if (vis[v]) continue;
					q.push(v);
				}
			}
			possible = possible && (2 * component >= edges);
		}
		
		cout << (possible ? "possible\n" : "impossible\n");
	}
	
	return 0;
}
