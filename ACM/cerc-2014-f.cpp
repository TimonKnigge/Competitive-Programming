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
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

ll MOD  = 1e9+9;

ll mod(ll v, ll M) { return ((v%M)+M)%M; }
void fix (ll &v) { v = mod(v, MOD); }

constexpr int Q = '?', EPT = -1;
int symb(string &s, size_t i) { return i < s.length() ? int(s[i]) : -1; }
int eqsubst(int l, int r) {
	if (l == -1 || r == -1) return -1;
	if (l == Q && r == Q) return Q;
	return (l == Q ? r : l);
}

ll sum_upto(ll N) {
	return (N * (N + 1LL)) / 2LL;
}

ll toequal(int l, int r) {
	if (l == -1 || r == -1) return (l == r ? 1LL : 0LL);
	if (l == Q && r == Q) return 26LL;
	if (l == Q || r == Q) return 1LL;
	return l == r;
}

ll tostrict(int l, int r) {
	if (r == -1) return 0LL;
	if (l == -1) return (r == Q ? 26LL : 1LL);
	if (l == Q && r == Q) return sum_upto(25LL); 
	if (l == Q) return r - 'a';
	if (r == Q) return 'z' - l;
	return (l < r ? 1LL : 0LL);
}

ll toequal3(int l, int m, int r) {
	if (l == -1 || m == -1 || r == -1) return (l == -1 && m == -1 && r == -1 ? 1LL : 0LL);
	if (l != Q && r != Q && l != r) return 0LL;
	if (l != Q && m != Q && l != m) return 0LL;
	if (m != Q && r != Q && m != r) return 0LL;
	if (l != Q || r != Q || m != Q) return 1LL;
	return 26LL;
}

ll V = 0LL;
ll tostrict3(int l, int m, int r) {
	if (m == -1 || r == -1) return 0LL;
	if (l == -1) return tostrict(m, r);
	if (m != Q) return tostrict(l, m) * tostrict(m, r);
	if (l != Q && r != Q) return max(0LL, ll(r - l - 1));
	if (l != Q) return max(0LL, sum_upto(ll('z' - l - 1)));
	if (r != Q) return max(0LL, sum_upto(ll(r - 'a' - 1)));
	return V;
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	ll tw[4];
	tw[0] = 1LL;		tw[1] = 26LL;
	tw[2] = 26LL * tw[1];	tw[3] = 26LL * tw[2];
	for (int i = 2; i <= 25; ++i)
		V += sum_upto(ll(i - 1));
	
	int T;
	cin >> T;
	while (T--) {
		string str[3];
		cin >> str[0] >> str[1] >> str[2];
		
		size_t L = max(str[0].length(), max(str[1].length(), str[2].length()));
		vector<ll> dp[4];
		for (int m = 0; m < 4; ++m) dp[m].assign(L + 1, 0LL);
		dp[3][0] = 1LL;
		
		for (size_t i = 0; i < L; ++i) {
			int s[3];
			bool q[3];
			for (int m = 0; m < 3; ++m) {
				s[m] = symb(str[m], i);
				q[m] = s[m] == Q;
			}
			
			// 0	< <
			dp[0][i + 1] = mod(dp[0][i] * tw[q[0]+q[1]+q[2]], MOD);
		
			// 1	< =
			dp[1][i + 1] = mod(dp[1][i] * mod(tw[q[0]] * toequal(s[1], s[2]), MOD), MOD);
			dp[0][i + 1] = mod(dp[0][i+1] + mod(dp[1][i] * mod(tw[q[0]] * tostrict(s[1], s[2]), MOD), MOD), MOD);

			// 2	= <
			dp[2][i + 1] = mod(dp[2][i] * mod(tw[q[2]] * toequal(s[0], s[1]), MOD), MOD);
			dp[0][i + 1] = mod(dp[0][i+1] + mod(dp[2][i] * mod(tw[q[2]] * tostrict(s[0], s[1]), MOD), MOD), MOD);
			
			// 3	= =
			dp[3][i + 1] = mod(dp[3][i] * toequal3(s[0], s[1], s[2]), MOD);
			// 	to = <
			if (s[0] == s[1] || (s[0] == Q && s[1] != EPT) || (s[1] == Q && s[0] != EPT))
				dp[2][i + 1] = mod(dp[2][i+1] + dp[3][i] * tostrict(eqsubst(s[0], s[1]), s[2]), MOD);
			//	to < =
			if (s[1] == s[2] || (s[1] == Q && s[2] != EPT) || (s[2] == Q && s[1] != EPT))
				dp[1][i + 1] = mod(dp[1][i+1] + dp[3][i] * tostrict(s[0], eqsubst(s[1], s[2])), MOD);
			//	to < <
			dp[0][i + 1] = mod(dp[0][i + 1] + dp[3][i] * tostrict3(s[0], s[1], s[2]), MOD);
		}
		
		cout << dp[0][L] << '\n';
	}
	
	cout << flush;
	
	return 0;
}
