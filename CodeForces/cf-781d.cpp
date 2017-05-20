#include <iostream> 
#include <cstdio>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <bitset>
#include <numeric>
#include <iterator>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <cassert>

using namespace std;
using ll = long long;
using ld = long double;
using ii = pair<ll, ll>;
using vi = vector<ll>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N, M;
	cin >> N >> M;
	constexpr int IT = 63;
	cerr << "Max: " << (1LL << (IT-1)) << endl;
	
	vector<vector<vector<bitset<501>>>>
		con(2, vector<vector<bitset<501>>>(IT,
			vector<bitset<501>>(N, bitset<501>())));
	while (M--) {
		int x, y, t;
		cin >> x >> y >> t;
		--x; --y;
		con[t][0][x].set(y, true);
	}
	
	for (int i = 0; i + 1 < IT; ++i) {
		for (int a = 0; a < N; ++a)
		for (int b = 0; b < N; ++b) {
			if (con[0][i][a].test(b))
				con[0][i + 1][a] |= con[1][i][b];
			if (con[1][i][a].test(b))
				con[1][i + 1][a] |= con[0][i][b];
		}
	}
	
	ll ans = 0LL;
	vector<vvi> len(2, vvi(2, vi(N, -1)));
	len[0][0][0] = 0;
	for (ll nexl = IT-1, c = 0; nexl >= 0; c = 1 - c, --nexl) {
		vvi olen(2, vi(N, -1));

		for (int t = 0; t < 2; ++t) {
			for (int a = 0; a < N; ++a) {
				if (len[c][t][a] < 0) continue;
				len[1-c][t][a] = max(len[c][t][a], len[1-c][t][a]);
				for (int b = 0; b < N; ++b) {
					if (con[t][nexl][a].test(b))
						len[1-c][1-t][b] = max(
							len[1-c][1-t][b],
							len[c][t][a] + (1LL << nexl));
				}
			}
		}
	}
	for (int c = 0; c < 2; ++c)
	for (int t = 0; t < 2; ++t)
		for (int i = 0; i < N; ++i)
			ans = max(ans, len[c][t][i]);
	
	if (ans > 1000000000000000000LL)
		ans = -1;
	if (ans < -1) ans = -1;
	cout << ans << endl;
	
	return 0;
}
