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
	
	int n, m, c;
	cin >> n >> m >> c;

	vi a(n, -1);
	while (true) {
		bool done = a[0] != -1;
		for (int i = 1; i < n && done; ++i)
			done = done && a[i-1] <= a[i] && a[i] != -1;
		if (done) break;

		int p;
		cin >> p;
		if (p <= c / 2) {
			int i = 0;
			while (i+1 < n && a[i] != -1 && a[i] <= p) ++i;
			a[i] = p;
			cout << i+1 << endl;
		} else {
			int i = n-1;
			while (i > 0 && a[i] != -1 && a[i] >= p) --i;
			a[i] = p;
			cout << i+1 << endl;
		}
	}
	
	return 0;
}
