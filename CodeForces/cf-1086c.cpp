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

bool dfs(size_t i, const string &s, const string &a, vector<int> &ans,
			vector<int> &fr, int k, bool strict = false) {
	if (i == s.length()) {
		return true;
	}
	int sv = s[i]-'a', av = a[i]-'a';
	if (ans[sv] >= 0) {
		if (av <= ans[sv] || strict)
			return dfs(i+1, s, a, ans, fr, k, strict || av < ans[sv]);
		else
			return false;
	}
	for (int d = 0; d < k; ++d) {
		if (fr[d] && (av <= d || strict)) {
			fr[d] = 0;
			ans[sv] = d;
			if (dfs(i+1, s, a, ans, fr, k, strict || av < d))
				return true;
			ans[sv] = -1;
			fr[d] = 1;
		}
	}
	return false;
}
void solve() {
	int k;
	string s, a, b;
	cin >> k >> s >> a >> b;

	vector<int> ans(k, -1);
	vector<int> fr(k, 1);
	bool ok = dfs(0, s, a, ans, fr, k);

	int nf = 0;
	string anss(k, ' ');
	for (int j = 0; j < k; ++j) {
		if (ans[j] < 0) {
			while (nf < k && !fr[nf]) ++nf;
			fr[nf] = 0;
			ans[j] = nf;
		}
		anss[j] = ans[j]+'a';
	}
	string an(s.length(), ' ');
	for (size_t i = 0; i < s.length(); ++i)
		an[i] = 'a'+ans[s[i]-'a'];
	if (ok && an <= b)
		cout << "YES\n" << anss << '\n';
	else
		cout << "NO\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout << fixed << setprecision(12);
	
	int T;
	cin >> T;
	while (T--) solve();
	
	return 0;
}
