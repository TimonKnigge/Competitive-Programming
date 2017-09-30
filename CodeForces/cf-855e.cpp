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

constexpr int INF = 1000000010;
constexpr ll LLINF = 1000000000000000010LL;

ll fac[11];
ll nCk[70][70];
ll prec[11][70][11];
void precompute() {
	fac[0] = 1LL;
	for (int n = 1; n <= 10; ++n) fac[n] = fac[n-1] * ll(n);
	for (int i = 0; i < 70; ++i) nCk[0][i] = 0, nCk[i][0] = 1;
	for (int n = 1; n < 70; ++n)
		for (int k = 1; k < 70; ++k)
			nCk[n][k] = nCk[n-1][k-1] + nCk[n-1][k];

	for (int c = 0; c < 70; ++c)
		for (int e = 0; e < 11; ++e)
			prec[0][c][e] = 0;
	prec[0][0][0] = 1;

	for (int t = 1; t <= 10; ++t)
		for (int c = t; c < 70; ++c)
			for (int e = 0; e <= t; ++e)
				for (int tc = 1; tc <= c; ++tc)
					if (e - (tc % 2 == 0 ? 0 : 1) >= 0)
						prec[t][c][e] += nCk[c-1][tc-1]
							* prec[t-1][c-tc][e - (tc % 2 == 0 ? 0 : 1)];
}

ll count(ll u, ll b) {
	vi U;
	while (u > 0) U.push_back(u % b), u /= b;
	if (U.empty()) U.push_back(0);
	reverse(U.begin(), U.end());

	int mask = 0;
	ll ans = 0LL;
	for (size_t i = 0; i < U.size(); ++i) {
		for (int d = (i > 0 ? 0 : 1); d < U[i]; ++d) {
			int odds = __builtin_popcount(mask^(1<<d));
			for (int evens = 0; evens + odds <= b; ++evens)
				ans += prec[evens+odds][int(U.size()-i-1)][odds]
					* fac[evens] * fac[odds] * nCk[b - odds][evens];
		}
		mask ^= (1 << U[i]);
	}
	if (mask == 0) ++ans;

	for (int dgs = 1; dgs < (int)U.size(); ++dgs) {
		for (int evens = 0; evens + 1 <= b; ++evens)
			ans += (b - 1) * prec[evens+1][dgs-1][1] * fac[evens]
				* nCk[b - 1][evens];
	}

	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	precompute();

//	for (int i = 1; i < 10; ++i)
//		cerr << i << " ! " << count(i, 2) << endl << endl << endl;
	
	int q;
	cin >> q;
	while (q--) {
		ll b, l, r;
		cin >> b >> l >> r;
		cout << (count(r, b) - count(l-1, b)) << endl; 
	}
	
	return 0;
}
