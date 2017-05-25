#include <bits/stdc++.h>

using namespace std;
using namespace chrono;
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

ll arr(vii &lb, vii &ub, int i, int j) {
	ll x = ub[j].first-lb[i].first;
	ll y = ub[j].second-lb[i].second;
	if (x < 0LL || y < 0LL) return 0LL;
	return x*y;
}

ll dfs(int l, int r, int il, int ir, vii &lb, vii &ub) {
	if (l > r) return 0LL;
	int m = (l + r) / 2;
	
	ll opt = 0LL; int iopt = -1;
	for (int i = il; i <= ir; ++i) {
		ll val = arr(lb, ub, m, i);
		if (val > opt || (val == 0LL && lb[m].first >= ub[i].first)) {
			opt = val;
			iopt = i;
		}
	}
	
	opt = max(opt, dfs(l, m - 1, il, iopt, lb, ub));
	opt = max(opt, dfs(m + 1, r, iopt, ir, lb, ub));
	return opt;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, m;
	cin >> m >> n;
	vii lb(m, {0, 0}), ub(n, {0, 0});
	for (int i = 0; i < m; ++i) cin >> lb[i].first >> lb[i].second;
	for (int i = 0; i < n; ++i) cin >> ub[i].first >> ub[i].second;
	
	vii nlb;
	sort(lb.begin(), lb.end());
	ll least = LLINF;
	for (int i = 0; i < m; ++i)
		if (lb[i].second < least) {
			least = lb[i].second;
			nlb.push_back(lb[i]);
		}
	vii nub;
	sort(ub.rbegin(), ub.rend());
	least = -LLINF;
	for (int i = 0; i < n; ++i)
		if (ub[i].second > least) {
			least = ub[i].second;
			nub.push_back(ub[i]);
		}
	reverse(nub.begin(), nub.end());

	ll best = dfs(0, (int)nlb.size() - 1, 0, (int)nub.size() - 1, nlb, nub);
	cout << best << endl;
	
	return 0;
}
