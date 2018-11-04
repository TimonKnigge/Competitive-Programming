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

ll mhd(ll x1, ll y1, ll x2, ll y2) {
	return abs(x1-x2) + abs(y1-y2);
}
ll mhdt(int i, int j, int k, const vi &x, const vi &y) {
	return mhd(x[i], y[i], x[j], y[j]) + mhd(x[j], y[j], x[k], y[k])
			+ mhd(x[k], y[k], x[i], y[i]);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	vi x(n), y(n);
	for (int i = 0; i < n; ++i)
		cin >> x[i] >> y[i];

	int l = 0, r = 0, u = 0, b = 0;
	for (int i = 1; i < n; ++i) {
		if (x[i] < x[l]) l = i;
		if (x[i] > x[r]) r = i;
		if (y[i] < y[b]) b = i;
		if (y[i] > y[u]) u = i;
	}

	ll d3 = 0LL;
	for (int i = 0; i < n; ++i)
		d3 = max(d3,
			max(mhdt(i, l, r, x, y),
			max(mhdt(i, l, u, x, y),
			max(mhdt(i, l, b, x, y),
			max(mhdt(i, r, u, x, y),
			max(mhdt(i, r, b, x, y),
				mhdt(i, u, b, x, y)))))));

	ll d4 = mhd(x[l], y[l], x[u], y[u]) + mhd(x[u], y[u], x[r], y[r])
			+ mhd(x[r], y[r], x[b], y[b]) + mhd(x[b], y[b], x[l], y[l]);
	cout << d3;
	for (int i = 4; i <= n; ++i)
		cout << ' ' << d4;
	cout << endl;
	
	return 0;
}
