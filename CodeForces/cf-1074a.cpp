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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int  n, m;
	cin >> n >> m;

	vector<int> v;
	for (int i = 0, x; i < n; ++i)
		cin >> x, v.push_back(x);
	sort(v.begin(), v.end());

	order_tree<ii> ot;
	int add = 0;
	for (int i = 0; i < m; ++i) {
		int x1, x2, y;
		cin >> x1 >> x2 >> y;
		if (x1 == 1) {
			if (x2 == 1e9) {
				++add;
			} else
			ot.insert({x2, i});
		}
	}

	int tot = (int)ot.size();
	int ans = tot;
	for (int i = 0; i < n; ++i) {
		if (i+1<n && v[i+1] == v[i]) continue;

		int c = i;
		c += tot - ot.order_of_key({v[i]-1, INF});
		ans = min(ans, c);
	}
	ans = min(ans,(int)v.size());
	cout << add+ans << endl;
	
	return 0;
}
