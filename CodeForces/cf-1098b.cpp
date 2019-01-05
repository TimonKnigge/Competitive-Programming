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

void solve() {
	int n, m;
	cin >> n >> m;
	vector<string> B(n);
	for (auto &s : B) cin >> s;

	int bestcost = INF;
	vector<string> best(n, string(m, ' ')), reserve(n, string(m, ' '));
	for (string spr : {"AGCT", "ACGT", "ATCG", "GCAT", "GTAC", "CTAG"}) {
		for (int rows = 0; rows < 2; ++rows) {
			int cost = 0;
			for (int i = 0; i < (rows ? n : m); ++i) {
				int tc = INF;
				for (int of = 0; of < 2; ++of) {
					int t = 0;
					for (int j = 0; j < (rows ? m : n); ++j) {
						t += (B[(rows?i:j)][(rows?j:i)] != spr[((i&1)<<1)|((of+j)&1)]);
					}
					if (t < tc) {
						tc = t;
						for (int j = 0; j < (rows ? m : n); ++j)
							reserve[(rows?i:j)][(rows?j:i)] = spr[((i&1)<<1)|((of+j)&1)];
					}
				}
				cost += tc;
			}
			if (cost < bestcost) {
				bestcost = cost;
				swap(best, reserve);
			}
		}
	}

	cerr << "Required " << bestcost << " changes." << endl;
	for (const auto &s : best) cout << s << '\n';
	cout << flush;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout << fixed << setprecision(12);
	
	solve();
	
	return 0;
}
