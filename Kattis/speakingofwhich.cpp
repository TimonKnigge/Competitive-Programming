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

constexpr ll MOD = 1e6+9;

inline bool isconsonant(char c) {
	return (
		c == 'a' ||
		c == 'o' ||
		c == 'i' ||
		c == 'u' ||
		c == 'e');
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	string S;
	cin >> S;
	
	ll run = 0LL, ans = 1LL;
	for (size_t l = 0; l < S.length(); ++l) {
		if (l+2 >= S.length()) {
			ans = (ans * ((run + 1LL) / 2LL + 1LL)) % MOD;
			break;
		}
		if (S[l] == S[l+2] && S[l+1] == 'o' && !isconsonant(S[l])) {
			++run;
			++l;
		} else if (run > 0LL) {
			ans = (ans * ((run + 1LL) / 2LL + 1LL)) % MOD;
			run = 0LL;
		}
	}
	
	cout << ans << endl;
	
	return 0;
}
