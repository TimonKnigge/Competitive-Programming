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
	
	int T;
	cin >> T;
	for (int t = 1; t <= T; ++t) {
		ll N, K, V;
		cin >> N >> K >> V;
		cout << "Case #" << t << ":";

		ll L = (V - 1LL) * K % N, R = V * K % N;
		for (int i = 0; i < N; ++i) {
			string word;
			cin >> word;
			if ((L < R && L <= i && i < R) || (L >= R && (L <= i || i < R)))
				cout << ' ' << word;
		}
		cout << '\n';
	}
	
	return 0;
}
