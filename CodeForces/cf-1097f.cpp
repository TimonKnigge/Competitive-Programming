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

constexpr int M = 110*64; // >7000

void solve() {
	int n, q;
	cin >> n >> q;

	vector<vector<int>> divs(M);
	for (int d = 1; d < M; ++d)
		for (int k = d; k < M; k += d)
			divs[k].push_back(d);
	cerr << "Collected divisors." << endl;

	vector<bitset<M>> bs_gcd(M);
	for (int d = M-1; d >= 1; --d) {
		bs_gcd[d].set(d, true);
		for (int k = 2*d; k < M; k += d)
			bs_gcd[d] ^= bs_gcd[k];
	}
	cerr << "Created gcd masks." << endl;

	vector<bitset<M>> bs_n(n);
	while (q--) {
		int t;
		cin >> t;
		if (t == 1) {
			int x, v;
			cin >> x >> v;
			--x;

			bs_n[x].reset();
			for (int d : divs[v])
				bs_n[x].set(d, true);
		}
		if (t == 2) {
			int x, y, z;
			cin >> x >> y >> z;
			--x, --y, --z;

			bs_n[x] = (bs_n[y] ^ bs_n[z]);
		}
		if (t == 3) {
			int x, y, z;
			cin >> x >> y >> z;
			--x, --y, --z;

			bs_n[x] = (bs_n[y] & bs_n[z]);
		}
		if (t == 4) {
			int x, v;
			cin >> x >> v;
			--x;

			cout << ((bs_n[x] & bs_gcd[v]).count()&1);
		}
	}
	cout << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout << fixed << setprecision(12);
	
	solve();
	
	return 0;
}
