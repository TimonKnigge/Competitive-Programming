#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
using ll = __int128; //long long;
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

ll pw(ll n, int k) {
	if (!k) return 1;
	ll r = pw(n*n, k/2);
	if (k&1) r *= n;
	return r;
}

void solve() {
	long long N;
	cin >> N;

	set<long long> s{1};
	for (int k = 2; k <= 42; ++k)
		for (ll n = 2; (pw(n, k+1) - 1) / (n - 1) <= N; ++n)
			s.insert((pw(n, k+1) - 1) / (n - 1));
	cout << accumulate(s.begin(), s.end(), 0LL) << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout << fixed << setprecision(12);
	
	solve();
	
	return 0;
}
