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

ll MOD = 1e9+7;

inline int g(char c) { return c - '0'; }

inline void add(ll &l, ll r) { l = (l + r) % MOD; }

ll f(string &s, int m, int D) {

	int N = int(s.length());
	vvi dp(N, vi(m, 0LL));
	
	for (int i = 0; i < g(s[0]); ++i)
		dp[0][i%m]++;
	if (g(s[0]) > D) dp[0][D%m]--;
	
//	cerr << "dp[" <<0 << "]:";
//	for(int j = 0; j < m; ++j)
//		cerr << " " << dp[0][j];
//	cerr<<endl;

	
	ll mod = (g(s[0]) % m);
	bool atop = (g(s[0]) != D);
	for (int i = 1; i < N; ++i) {
		for (int d = ((i&1) ? D : 0); d <= ((i&1) ? D : 9); ++d) {
			if (!(i&1) && d == D) continue;
			for (int j = 0; j < m; ++j) {
				add(dp[i][(10 * j + d) % m],
				    dp[i - 1][j]);
			}
			if (atop && d < g(s[i])) {
				add(dp[i][(mod * 10 + d) % m], 1LL);
			}
		}
		if ( (i&1) && D != g(s[i])) atop = false;
		if (!(i&1) && D == g(s[i])) atop = false;
		
		mod = (mod * 10 + g(s[i])) % m;
		
//		cerr << "dp[" <<i << "]:";
//		for(int j = 0; j < m; ++j)
//			cerr << " " << dp[i][j];
//		cerr<< "  (" << atop << ")"<<endl;
	}
	
	ll ans = ((mod == 0 && atop ? 1LL : 0LL) + dp[N - 1][0]) % MOD;
//	cerr << "Returning " << ans << " (" << atop << ")" << endl;
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int m, d;
	cin >> m >> d;
	
	string a, b;
	cin >> a >> b;
	
//	cerr << "a: " << a << ", b: " << b << endl;
	
	for (int i = -1 + a.length(); i >= 0; --i) {
		if (a[i] == '0') {
			a[i] = '9';
		} else {
			a[i] = char(int(a[i]) - 1);
			break;
		}
	}
//	cerr  << "New a: " << a << endl;
	
	cout << ((f(b, m, d) + MOD - f(a, m, d)) % MOD) << endl;
	
	return 0;
}
