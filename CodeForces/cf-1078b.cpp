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

constexpr ll M = 10000;

void solve() {
	ll n;
	cin >> n;
	vi a(n);
	map<ll, ll> dist;
	for (ll &v : a) {
		cin >> v;
		dist[v]++;
	}

	if (dist.size() <= 2) {
		cout << n << endl;
		return;
	}

	vector<vector<int>> cm(n+1, vector<int>(M+1, 0));
	cm[0][0] = 1;
	for (ii pr : dist) {
		int v = pr.first, c = pr.second;
		for (int i = n-1; i >= 0; --i) {
			for (int w = 0; w < M; ++w) {
				if (!cm[i][w]) continue;
				int tc = cm[i][w];
				for (int ni = i+1, nw = w+v; ni <= n && ni-i <= c && nw <= M; ++ni, nw += v) {
					cm[ni][nw] = ((cm[ni][nw]<<1)|tc)&3;
				}
			}
		}
	}

	int ans = 1;
	for (ii pr : dist) {
		int v = pr.first, c = pr.second;
		for (int k = 1; k <= c; ++k)
			if (cm[k][v*k] == 1)
				ans = max(ans, k);
	}
	cout << ans << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout << fixed << setprecision(12);
	
	solve();
	
	return 0;
}
