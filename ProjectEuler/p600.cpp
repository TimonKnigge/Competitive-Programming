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

	int N;
	cin >> N;

	vi P(N + 1, 0LL);
	for (int n = 1; n <= N; ++n)
		for (int a = 1; a <= n && (n - a) / 2 - a + 1 > 0; ++a)
			P[n] += (n - a) / 2 - a + 1;

	vi G(3 * N, 0LL);
	for (int k = 3; k <= N; ++k) {
//		cerr << k << endl;
		for (int abc = 3; abc <= k; ++abc) {
			G[3 * k - abc] += P[abc];
		}
//		for (int a = 1; a < k; ++a)
//			for (int b = a; a + b < k; ++b)
//				for (int c = b; a + b + c <= k; ++c)
//						G[3 * k - a - b - c]++;
	}

	partial_sum(G.begin(), G.end(), G.begin());
	cout << G[N] << endl;
	
	return 0;
}
