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
using vd = vector<ld>;

template<class T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<class TIn, class TOut = null_type>
using order_tree = tree<TIn, TOut, less<TIn>, rb_tree_tag,
	tree_order_statistics_node_update>;
// .find_by_order(int r) and .order_of_key(TIn v)

constexpr int INF = 2000000010;
constexpr ll LLINF = 9000000000000000010LL;
constexpr ld PI = acos(-1);

void solve() {
	int n, s;
	cin >> n >> s;
	if (n == 2) {
		cout << s << endl;
		return;
	}
	vi d(n);
	for (int i = 1, u, v; i < n; ++i)
		cin >> u >> v, --u, --v,
		d[u]++, d[v]++;

	int md = *max_element(d.begin(), d.end());
	int leafs = 0;
	for (int v : d) if (v == 1) ++leafs;

	printf("%.10lf\n", double(s)*2.0/double(leafs));
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout << fixed << setprecision(12);
	
	solve();
	
	return 0;
}
