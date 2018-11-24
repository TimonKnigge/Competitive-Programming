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

constexpr ll MOD = 20092010LL;

void solve() {
	vi g(1000*1000, 1);
	for (int i = 2000; i < 1000*1000; ++i)
		g[i] = (g[i-2000]+g[i-1999])%MOD;

	constexpr int M = 50+1;
	vi off(M); vvi dep(M);
	off[0] = -1999;
	dep[0] = {1, 1};
	for (int i = 1; i < M; ++i) {
		off[i] = 2*off[i-1];
		dep[i].resize(2*dep[i-1].size()-1);
		for (size_t a = 0; a < dep[i-1].size(); ++a)
			for (size_t b = 0; b < dep[i-1].size(); ++b)
				dep[i][a+b] = (dep[i][a+b] + dep[i-1][a]*dep[i-1][b]) % MOD;
		if (dep[i].size() > 2000) {
			for (size_t j = 0; j < dep[i].size()-2000; ++j)
				dep[i][j+1999] = (dep[i][j+1999]+dep[i][j]) % MOD,
				dep[i][j+2000] = (dep[i][j+2000]+dep[i][j]) % MOD;
			off[i] += 2000-(int)dep[i].size();
			dep[i].erase(dep[i].begin(), dep[i].end()-2000);
		}
	}
	cerr << "Done precomputing" << endl;

	ll k;
	cin >> k;
	if (k < (ll)g.size()) {
		cerr << "Small enough, should be " << g[k] << endl;
	}
	vi kdep{1};
	for (int b = M-1; b >= 0; --b) {
		if (k+off[b]-(int)dep[b].size()-(int)kdep.size() < 0) continue;
		cerr << "Jumping at " << b << " with offset " << off[b] << " and interval " << dep[b].size() << endl;
		vi nkdep(kdep.size()+dep[b].size()-1);
		for (size_t a = 0; a < kdep.size(); ++a)
			for (size_t c = 0; c < dep[b].size(); ++c)
				nkdep[a+c] = (nkdep[a+c] + kdep[a]*dep[b][c]) % MOD;
		k += off[b];
		swap(kdep, nkdep);
		if (kdep.size() > 2000) {
			for (size_t j = 0; j < kdep.size()-2000; ++j)
				kdep[j+1999] = (kdep[j+1999]+kdep[j]) % MOD,
				kdep[j+2000] = (kdep[j+2000]+kdep[j]) % MOD;
			k += 2000-(int)kdep.size();
			kdep.erase(kdep.begin(), kdep.end()-2000);
		}
	}

	cerr << "Final: " << k << endl;

	ll ans = 0LL;
	for (int i = 0; i < (int)kdep.size(); ++i)
		ans = (ans + g[k-i]*kdep[i]) % MOD;
	cout << ans << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout << fixed << setprecision(12);
	
	solve();
	
	return 0;
}
