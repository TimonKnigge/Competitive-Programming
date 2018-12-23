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

int to(char c) {
	if (c == 'R') return 0;
	if (c == 'P') return 1;
	return 2;
}

int solve(const vector<order_tree<int, null_type>> &t, int n) {
	int ans = 0;
	for (int a = 0, b = 1, c = 2; a < 3; ++a, b = (b+1)%3, c = (c+1)%3) {
		// Solve for a
		// Bad is b
		// Good is c
		if (t[b].empty()) {
			ans += (int)t[a].size();
			continue;
		}
		if (t[a].empty() || t[c].empty()) continue;
		int lb = *t[b].begin(), rb = *t[b].rbegin();
		int lg = *t[c].begin(), rg = *t[c].rbegin();

		int toadd = (int)t[a].size();
		if (lb < lg)
			toadd -= (int)t[a].order_of_key(lg) - (int)t[a].order_of_key(lb);
		if (rg < rb)
			toadd -= (int)t[a].order_of_key(rb) - (int)t[a].order_of_key(rg);

		ans += toadd;
	}
	return ans;
}

void solve() {
	int n, q;
	cin >> n >> q;
	
	vector<order_tree<int, null_type>> t(3);
	vector<int> cur(n, -1);
	{
		string S;
		cin >> S;
		for (size_t i = 0; i < S.length(); ++i)
			t[cur[i] = to(S[i])].insert((int)i);
	}

	cout << solve(t, n) << '\n';
	while (q--) {
		int i;
		char c;
		cin >> i >> c;
		--i;
		t[cur[i]].erase(t[cur[i]].find(i));
		cur[i] = to(c);
		t[cur[i]].insert(i);
		cout << solve(t, n) << '\n';
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout << fixed << setprecision(12);
	
	solve();
	
	return 0;
}
