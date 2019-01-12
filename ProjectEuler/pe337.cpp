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

constexpr ll M = 10000LL * 10000LL;

template <class T>
struct FenwickTree {		// use 1 based indices!!!
	int n; vector<T> tree;
	FenwickTree(int n) : n(n) { tree.assign(n + 1, 0); }
	T query(int l, int r) { if (l > r) return 0; else return (M+query(r)-query(l - 1))%M; }
	T query(int r) {
		T s = 0;
		for(; r > 0; r -= (r & (-r))) s += tree[r];
		return s%M;
	}
	void update(int i, T v) {
		for(; i <= n; i += (i & (-i))) tree[i] = (tree[i]+v)%M;
	}
};

vi calculate_phi(int n) {
	vi phi(n + 1, 0LL);
	iota(phi.begin(), phi.end(), 0LL);
	for (ll i = 2LL; i <= n; ++i)
		if (phi[i] == i)
			for (ll j = i; j <= n; j += i)
				phi[j] -= phi[j] / i;
	return phi;
}

void solve() {
	int N;
	cin >> N;
	vi phi = calculate_phi(N);

	FenwickTree<ll> ft(N+5);
	for (ll n = N; n >= 6; --n) {
		ll q = 1+ft.query(phi[n]+1, n-1);
		ft.update(phi[n], q);
		if (n == 6) cout << "Answer = " << q%M << endl;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout << fixed << setprecision(12);
	
	solve();
	
	return 0;
}
