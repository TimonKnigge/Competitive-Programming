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
	int n;
	cin >> n;

	unordered_map<int, int> a, b;
	while (n--) {
		string s;
		cin >> s;

		{
			bool ok = true;
			int rem = 0;
			for (int i = 0; ok && i < (int)s.length(); ++i) {
				if (s[i] == '(') ++rem;
				else if (rem > 0) --rem;
				else ok = false;
			}
			if (ok) a[rem]++;
		}
		{
			bool ok = true;
			int rem = 0;
			for (int i = -1 + (int)s.length(); ok && i >= 0; --i) {
				if (s[i] == ')') ++rem;
				else if (rem > 0) --rem;
				else ok = false;
			}
			if (ok && rem) b[rem]++;
		}
	}

	int ans = 0;
	for (pair<int, int> xy : a) {
		int x = xy.first, y = xy.second;
		if (!x) ans += y/2;
		else ans += min(y, b[x]);
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
