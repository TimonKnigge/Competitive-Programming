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
	
	int n;
	scanf("%d", &n);
	vvi e(n, vi());
	vi deg(n, 0);
	for (int i = 0; i < n; ++i) {
		int a, b;
		scanf("%d %d", &a, &b);
		a--; b--;
		e[a].push_back(b);
		e[b].push_back(a);
		deg[a]++;
		deg[b]++;
	}
	
	queue<int> q;
	for (int i = 0; i < n; ++i) {
		if (deg[i] == 1) q.push(i);
	}
	
	vi con(n, -1);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int v : e[u]) {
			if (con[v] > -1) continue;
			con[u] = v;
			deg[v]--;
			if (deg[v] == 1) q.push(v);
			break;
		}
		deg[u]--;
	}
	
	// We are left with a cycle, find its start
	for (int ss = 0; ss < n; ++ss) {
		if (con[ss] > -1) continue;
		int s = ss;
		vi cyc;
		cyc.push_back(s);
		while (true) {
			bool f = false;
			for (int v : e[s]) {
				if (con[v] > -1) continue;
				con[s] = v;
				s = v;
				cyc.push_back(s);
				f = true;
				break;
			}
			if (!f) break;
		}
		for (int j = 0; j < cyc.size(); ++j) {
			con[cyc[j]] = cyc[(j+1)%cyc.size()];
		}
	}
	
	for (int i = 0; i < n; ++i) {
		cout << i+1 << ' ' << 1+con[i] << '\n';
	}
	
	return 0;
}
