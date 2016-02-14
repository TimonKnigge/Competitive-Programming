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

ll MOD = 1e8;
vvi dp (201, vi(201, -1LL));

ll count(char l, char r) {
	if (l == '(') return (r == ')' || r == '?' ? 1LL : 0LL);
	if (l == '[') return (r == ']' || r == '?' ? 1LL : 0LL);
	if (l == '{') return (r == '}' || r == '?' ? 1LL : 0LL);
	if (l == ')' || l == '}' || l == ']') return 0LL;
	if (r == '(' || r == '{' || r == '[') return 0LL;
	if (r != '?') return 1LL;
	return 3LL;
}

ll calc(ll L, ll R, string &S) {
	if ((R - L) % 2 == 0LL) return 0LL;
	if (L > R) return (L == R + 1 ? 1LL : 0LL);
	if (dp[L][R] != -1LL) return dp[L][R];
	
	dp[L][R] = 0LL;
	for (int s = L + 1; s <= R; s += 2) {
		ll add1 = (count(S[L]  , S[s]) * calc(L + 1, s - 1, S)) % MOD;
		ll add2 = (s + 1 < R ? calc(s + 1, R, S) : 1LL);
		dp[L][R] = (dp[L][R] + add1 * add2) % MOD;
	}
	
	dp[L][R] %= MOD;
	
	return dp[L][R];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N;
	string S;
	cin >> N >> S;
	
	ll ans = calc(0, N - 1, S);
	if (ans < ll(1e5)) cout << ans << endl;
	else {
		ll v = ans % ll(1e5);
		int d = 0;
		while (v > 0) {
			++d;
			v /= 10;
		}
		for (int i = d; i < 5; ++i) cout << '0';
		cout << (ans % ll(1e5)) << endl;
	}
	
	return 0;
}
