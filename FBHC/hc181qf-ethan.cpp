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

void solve(int t) {
	string A;
	cin >> A;
	cout << "Case #" << t << ": ";

	// Find valid internal wrong-shift.
	for (size_t j = 1, l = 0; j < A.length(); ++j) {
		for (l = 0; j + l < A.length() && A[j + l] == A[0 + l]; ++l);
		if (l == 0 || j + l >= A.length()) continue;
		cout << A.substr(0, j) + A << '\n';
		return;
	}

	cout << "Impossible\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int T;
	cin >> T;
	for (int t = 1; t <= T; ++t) solve(t);
	
	return 0;
}
