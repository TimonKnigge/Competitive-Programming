#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
using ll = long long;
using ld = long double;
using ii = pair<ll, ll>;
using vi = vector<ll>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

template<class T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<class TIn, class TOut = null_type>
using order_tree = tree<TIn, TOut, less<TIn>, rb_tree_tag,
	tree_order_statistics_node_update>;

constexpr int INF = 2000000010;
constexpr ll LLINF = 9000000000000000010LL;

int closest(int u, int p, const vvi &E, vi &mine) {
	if (mine[u]) return u;
	int ret = -1;
	for (int v : E[u])
		if (v != p)
			ret = max(ret, closest(v, u, E, mine));
	return ret;
}

void solve() {
	int n;
	cin >> n;

	vvi E(n);
	for (int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		--a; --b;
		E[a].push_back(b);
		E[b].push_back(a);
	}

	int k, u;
	vi mine(n, 0);
	cin >> k;
	while (k--) cin >> u, --u, mine[u] = 1;

	vi your(n, 0);
	cin >> k;
	while (k--) cin >> u, --u, your[u] = 1;

	cout << "B " << u+1 << endl;
	cin >> u, --u;

	u = closest(u, -1, E, mine);
	cout << "A " << u+1 << endl;
	int y;
	cin >> y, --y;

	if (your[y])
		cout << "C " << u+1 << endl;
	else
		cout << "C -1" << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int t;
	cin >> t;
	while (t--) solve();
	
	return 0;
}
