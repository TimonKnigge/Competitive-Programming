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

ll gcd(ll a, ll b) { while (b) a %= b, swap(a, b); return a; }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	ll g1, g2;
	cin >> g1 >> g2;
	for (int i = 1; i < n; ++i) {
		ll a, b;
		cin >> a >> b;
		g1 = gcd(g1, a*b);
		g2 = gcd(g2, a*b);
	}

	if (g1 == 1LL && g2 == 1LL) {
		cout << -1 << endl;
	} else {
		ll g = (g1 > 1LL ? g1 : g2);
		for (ll d = 2LL; d*d <= g + 3LL; ++d) {
			if (g%d == 0LL) {
				cout << d << endl;
				return 0;
			}
		}
		cout << g << endl;
	}

	return 0;
}
