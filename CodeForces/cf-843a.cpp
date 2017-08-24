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

constexpr int INF = 1000000010;
constexpr ll LLINF = 1000000000000000010LL;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n;
	cin >> n;
	vii a(n, {0, 0});
	for (int i = 0; i < n; ++i) {
		a[i].second = i;
		cin >> a[i].first;
	}
	vi p(n, 0);
	sort(a.begin(), a.end());
	for (int i = 0; i < n; ++i) p[a[i].second] = i;

	vvi ans;
	for (int i = 0; i < n; ++i) {
		if (p[i] < 0) continue;
		ans.push_back(vi());
		int j = i;
		while (p[j] >= 0) {
			ans.back().push_back(j);
			int oj = j;
			j = p[j];
			p[oj] = -1;
		}
	}

	cout << ans.size() << endl;
	for (vi &an : ans) {
		cout << an.size();
		for (int i : an) cout << ' ' << i+1;
		cout << '\n';
	}

	return 0;
}
