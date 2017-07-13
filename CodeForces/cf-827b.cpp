#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ii = pair<ll, ll>;
using vi = vector<ll>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

constexpr int INF = 2000000000;
constexpr ll LLINF = 9000000000000000000;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, k;
	cin >> n >> k;

	int ans = 2 * ((n - 1) / k);
	ans += max(2, (n - 1) % k);
	cout << ans << endl;
	for (int i = 1; i < n; ++i) cout << i << ' ' << min(i + k, n) << '\n';
	
	return 0;
}
