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

ll seq[2005][2005];
ll MOD = 1e9 + 7;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	ll N, M;
	cin >> N >> M;
	string s;
	cin >> s;
	
	ll lopen = 0LL, ropen = 0LL;
	for (size_t i = 0; i < s.length(); ++i) {
		if (s[i] == '(') ropen++;
		else if (ropen > 0) --ropen;
		else ++lopen;
	}
	
	seq[0][0] = 1LL;
	for (int op = 1; op < 2005; ++op)
		seq[op][0] = 0LL;
	for (int i = 1; i < 2005; ++i) {
		for (int op = 0; op < 2005; ++op) {
			seq[op][i] = 0LL;
		}
		seq[1][i] = (seq[1][i] + seq[0][i - 1]) % MOD;
		seq[2003][i] = (seq[1][i] + seq[2004][i - 1]) % MOD;
		for (int op = 1; op < 2004; ++op) {
			seq[op - 1][i] = (seq[op-1][i] + seq[op][i - 1]) % MOD;
			seq[op + 1][i] = (seq[op+1][i] + seq[op][i - 1]) % MOD;
		}
	}
//	for (int i = 1; i < 2005; ++i) {
//		if (i&1) seq[0][i] = 0LL;
//		else {
//			for (int l = 0; l <= i - 2; ++l)
//				seq[0][i] = (seq[0][i] + seq[0][l] * seq[0][i - 2 - l]) % MOD;
//		}
//	}
//	for (int op = 1; op < 2005; ++op) {
//		seq[op][0] = 0LL;
//		for (int i = 1; i < 2005; ++i) {
//			for (int l = 0; l < i; ++l)
//				seq[op][i] = (seq[op][i] + seq[op-1][l] * seq[0][i - l - 1]) % MOD;
//		}
//		cerr << op << endl;
//	}
	
	ll ans = 0LL;
	for (int extra = 0; lopen + ropen + 2 * extra <= N - M; ++extra)
		for (int l = lopen + extra; l + ropen + extra <= N - M; ++l) {
			ans = (ans + seq[lopen + extra][l] * seq[ropen + extra][N - M - l]) % MOD;
		}
	
	cout << ans << endl;
	
	return 0;
}
