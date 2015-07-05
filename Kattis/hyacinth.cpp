#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
#include <bitset>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

bitset<10010> vis;
vi f1, f2;
vvi edge;
int c;

void dfs(int u, int v) {
	if (vis.test(u)) return;
	vis.set(u, true);
	f1[u] = v;
	f2[u] = c;
	c++;
	for (int p : edge[u]) {
		dfs(p, f2[u]);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n;
	cin >> n;
	edge.assign(n, vi());
	for (int C = 0; C < n - 1; ++C) {
		int i, j;
		cin >> i >> j;
		i--; j--;
		edge[i].push_back(j);
		edge[j].push_back(i);
	}

	f1.assign(n, -1);
	f2.assign(n, -1);

	if (n == 2) {
		cout << "1 2\n1 2" << endl;
	}
	else {
		int u = 0;
		for (int i = 0; i < n; ++i) if (edge[i].size() == 1) u = i;

		c = 2;
		dfs(u, 1);

		for (int i = 0; i < n; ++i) {
			cout << f1[i] << ' ' << f2[i] << '\n';
		}
		cout << endl;
	}

	return 0;
}