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
	
	constexpr ll UB = 1e8+10;
	vector<int> p(UB, 1);
	p[0] = p[1] = 0;
	for (int i = 2; i * i < UB; ++i)
		if (p[i])
			for (int j = i * i; j < UB; j += i)
				p[j] = 0;
	partial_sum(p.begin(), p.end(), p.begin());

	int N;
	cin >> N;
	vi ansp(N + 1, 0LL);
	for (int f = 2; f <= N; ++f) {
		int np = 1 - p[f] + p[f - 1], tf = f;
		do {
			tf = p[tf];
			np += 1 - p[tf] + p[tf - 1];
			ansp[np]++;
		} while (tf > 1);
	}

	ll ans = 1LL;
	for (ll fac : ansp)
		if (fac != 0LL)
			ans = (ans * fac) % ll(1e9+7);
	cout << ans << endl;
	
	return 0;
}
