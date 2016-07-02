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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, m;
	cin >> n >> m;
	
	vvi E(n, vi());
	while (m--) {
		int u, v;
		cin >> u >> v;
		--u; --v;
		E[u].push_back(v);
		E[v].push_back(u);
	}
	
	vi dis(n, -1);
	bool y = true;
	for (int i = 0; y && i < n; ++i) {
		if (dis[i] >= 0) continue;
		queue<ll> q;
		q.push(i);
		dis[i] = 0;
		while (!q.empty() && y) {
			ll u = q.front(); q.pop();
			for (ll v : E[u]) {
				if (dis[v] < 0) {
					dis[v] = dis[u] + 1;
					q.push(v);
				} else if ((dis[u] - dis[v]) % 2 == 0) {
					y = false;
					break;
				}
			}
		}
	}
	
	if (!y) cout << -1 << endl;
	else {
		vi res[2];
		for (int i = 0; i < n; ++i)
			res[dis[i]%2].push_back(i);
		for (int j = 0; j < 2; ++j) {
			cout << res[j].size() << endl;
			for (size_t i = 0; i < res[j].size(); ++i)
				cout << res[j][i]+1 << " \n"[i + 1 == res[j].size()];
		}
	}
	
	return 0;
}
