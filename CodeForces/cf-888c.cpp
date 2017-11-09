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
	
	string s;
	cin >> s;

	vi pos[26];
	for (int i = 0; i < 26; ++i) pos[i].push_back(-1);
	for (int i = 0; i < (int)s.length(); ++i) pos[s[i]-'a'].push_back(i);
	for (int i = 0; i < 26; ++i) pos[i].push_back((int)s.length());

	int ans = 1e9;
	for (int i = 0; i < 26; ++i) {
		int nans = 0;
		for (int j = 1; j < (int)pos[i].size(); ++j)
			nans = max(nans, int(pos[i][j] - pos[i][j-1]));
		ans = min(ans, nans);
	}
	cout << ans << endl;
	
	return 0;
}
