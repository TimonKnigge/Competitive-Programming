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

int dx[8] = {1,1,0,-1,-1,-1, 0, 1};
int dy[8] = {0,1,1, 1, 0,-1,-1,-1};

constexpr ll D = 400LL;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	vector<vb> F(D+D+1LL, vb(D+D+1LL, false));
	
	int n;
	cin >> n;
	
	vi t(n, 0LL);
	for (ll &v : t) cin >> v;
	
	queue<pair<ii, ii>> q[2];
	q[0].push({{D, D}, {0, 0}});
	for (int i = 0; i < n; ++i) {
		int m = i % 2;
		int o = 1-m;
//		cerr << q[m].size() << endl;
		
		set<pair<ii, ii>> vis;
		while (!q[m].empty()) {
			if (vis.find(q[m].front()) != vis.end()) {
				q[m].pop(); continue;
			}
			ll x, y, d, ti;
			tie(x, y) = q[m].front().first;
			tie(d, ti) = q[m].front().second;
			vis.insert(q[m].front());
			q[m].pop();
			for (int j = 1; j <= t[ti]; ++j) {
				F[x + dx[d] * j][y + dy[d] * j] = true;
			}
			if (ti + 1 < n) {
				q[o].push({{x + t[ti]*dx[d], y + t[ti]*dy[d]}, {(d+1)%8, ti + 1}});
				q[o].push({{x + t[ti]*dx[d], y + t[ti]*dy[d]}, {(d+7)%8, ti + 1}});
			}
		}
	}
	
	ll ans = 0LL;
	for (vb &f : F) for (size_t i = 0; i < f.size(); ++i) if (f[i]) ++ans;
	cout << ans << endl;
	
	return 0;
}
