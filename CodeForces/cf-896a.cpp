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
constexpr ll LLINF = 2e18+10;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	string r = "What are you doing at the end of the world? Are you busy? Will you save us?";
	string s[3] = {
		"What are you doing while sending \"",
		"\"? Are you busy? Will you send \"",
		"\"?"};

	vi f(1e5+3, 0LL);
	f[0] = (ll)r.length();
	for (int i = 1; i < (int)f.size(); ++i) {
		ll inc = ll(s[0].length() + s[1].length() + s[2].length());
		f[i] = min(LLINF, 2LL * f[i-1] + inc);
	}

	int q;
	cin >> q;
	while (q--) {
		ll n, k;
		cin >> n >> k;

		if (f[n] < k) {
			cout << '.';
			continue;
		}

		while (n >= 0) {
			if (n == 0) {
				cout << r[k-1];
				break;
			} else {
				if (k <= (ll)s[0].length()) {
					cout << s[0][k-1];
					break;
				} else if (k <= (ll)s[0].length() + f[n-1]) {
					k -= (ll)s[0].length();
					--n;
				} else if (k <= (ll)s[0].length() + f[n-1] + (ll)s[1].length()) {
					cout << s[1][k-((ll)s[0].length() + f[n-1])-1];
					break;
				} else if (k <= (ll)s[0].length() + 2LL*f[n-1] + (ll)s[1].length()) {
					k -= (ll)(s[0].length() + s[1].length()) + f[n-1];
					--n;
				} else {
					cout << s[2][k-((ll)(s[0].length()+s[1].length())+2LL*f[n-1])-1];
					break;
				}
			}
		}
	}

	cout << endl;
	
	return 0;
}
