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
	
	string S;
	cin >> S;
	int n = (int)S.length();

	S=S+S;
	int ans = 1, run = 1;
	for (size_t i = 1; i < S.length(); ++i) {
		run = (S[i] != S[i-1] ? run+1 : 1);
		ans = min(n, max(ans, run));
	}
	cout << ans << endl;
	
	return 0;
}
