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
	
	int n, m;
	cin >> n >> m;

	vector<string> B(n);
	for (string &b : B) cin >> b;

	bool y = true;
	for (int i = 0; y && i < n; ++i) {
		for (int j = i + 1; y && j < n; ++j) {
			bool same = false, diff = false;
			for (int k = 0; k < m; ++k) {
				same = same || (B[i][k] == '#' && B[j][k] == '#');
				diff = diff || (B[i][k] == '#' && B[j][k] != '#');
				diff = diff || (B[i][k] != '#' && B[j][k] == '#');
			}
			if (same && diff) y = false;
		}
	}

	cout << (y ? "Yes" : "No") << endl;
	
	return 0;
}
