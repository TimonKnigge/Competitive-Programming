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

constexpr ll MOD = 987654321LL;
vi product(const vi &l, const vi &r, int m) {
	assert(l.size() == (1<<m));
	assert(r.size() == (1<<m));
	vi x(1<<m);
	for (int i = 0; i < (1<<m); ++i)
		for (int j = 0; j < (1<<m); ++j)
			x[i^j] = (x[i^j] + l[i]*r[j]) % MOD;
	return x;
}
vi sq(const vi &s, ll k, int m) {
	if (k == 1) return s;
	vi p = product(s, s, m);
	p = sq(p, k/2, m);
	if (k&1)
		p = product(p, s, m);
	return p;
}

void solve() {
	ll N, K;
	cin >> N >> K;

	vector<vector<int>> D(N+1);
	for (int n = 2; n <= N; ++n)
		for (int m = 2*n; m <= N; m += n)
			D[m].push_back(n);
	cerr << "Got divisors." << endl;

	vi G(N+1, 0LL);
	for (int n = 3; n <= N; ++n) {
		if (n%100000 == 0) cerr << n << endl;
		unordered_set<int> GS;
		for (size_t i = 0; i < D[n].size(); ++i)
			for (size_t j = 0; j <= i; ++j)
				GS.insert(G[D[n][i]]^G[D[n][j]]);
		while (GS.find(G[n]) != GS.end()) ++G[n];
	}
	cerr << "max: " << *max_element(G.begin(), G.end()) << endl;

	vi cnt(64);
	for (int n = 2; n <= N; ++n) cnt[G[n]]++;
	vi p = sq(cnt, K, 6);
	cout << std::accumulate(p.begin()+1, p.end(), 0LL)%MOD << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout << fixed << setprecision(12);
	
	solve();
	
	return 0;
}
