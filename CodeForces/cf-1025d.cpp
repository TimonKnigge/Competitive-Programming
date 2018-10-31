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

ll gcd(ll a, ll b) { while (b) a %= b, swap(a, b); return a; }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	vi A(n);
	for (ll &a : A) cin >> a;

	vvi c(n, vi(n));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			c[i][j] = (i != j && gcd(A[i], A[j]) > 1);
		}
	}

	// [l, r] indexes as lr[r][l] and rr[l][r]
	vvi lr(n, vi(n, 0)), rr(n, vi(n, 0));
	for (int r = 0; r < n; ++r) {
		// Size 1 interval
		for (int l = r; l >= 0; --l) {
			// Find root.
			bool _lr = false, _rr = false;
			for (int i = l; i <= r; ++i) {
				// Can i be the root of [l, i-1]
				if (l < i && !rr[l][i-1]) continue;
				// Can i be the root of [i+1, r]
				if (i < r && !lr[r][i+1]) continue;
				// Can we attach to l-1
				if (l > 0 && c[l-1][i])
					_lr = true;
				// Can we attach to r+1
				if (r+1<n && c[r+1][i])
					_rr = true;
			}
			if (_lr) lr[r][l] = true;
			if (_rr) rr[l][r] = true;
		}
	}

	bool y = false;
	for (int i = 0; i < n; ++i)
		y = y || ((i == 0 || rr[0][i-1]) && (i+1==n || lr[n-1][i+1]));
	cout << (y?"Yes":"No") << endl;

	return 0;
}
