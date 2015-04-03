#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <bitset>
#include <stack>

using namespace std;

typedef long long ll;
typedef vector<int> vi;

bitset<500003> bs, vis;
int lc[500003], rc[500003], topo[500003];
int topo_ix;

void dfs(int v) {
	if (vis.test(v)) return;
	vis.set(v, true);
	if (v != 0){
		dfs(lc[v]);
		dfs(rc[v]);
	}
	topo[topo_ix] = v;
	topo_ix--;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	ll n; int m;
	cin >> n >> m;
	m++;
	bs.reset();

	for (int i = 1; i < m; ++i) {
		char c; int l, r;
		cin >> c >> l >> r;
		lc[i] = l; rc[i] = r;
		if (c == 'R') bs.set(i, true);
	}

	// Toposort
	vis.reset();
	topo_ix = m - 1;
	dfs(1);

	// balls
	vector<ll> balls(m, 0);
	balls[1] = n;
	for (int i = 0; i < m; ++i) {
		int u = topo[i];
		ll b = balls[u];
		ll lesser = b / 2, more = b - lesser;
		if (bs.test(u)) swap(more, lesser);
		if (u != 0) {
			balls[lc[u]] += more;
			balls[rc[u]] += lesser;
		}
		if (b % 2 == 1) bs.set(u, !bs.test(u));
	}

	for (int i = 1; i < m; ++i) {
		cout << (bs.test(i) ? 'R' : 'L');
	}
	cout << endl;

	return 0;
}