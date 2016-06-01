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

ll val(char c) {
	if (c >= '0' && c <= '9') return c-'0';
	if (c >= 'A' && c <= 'Z') return 10+c-'A';
	if (c >= 'a' && c <= 'z') return 36+c-'a';
	if (c == '-') return 62;
	return 63;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	string s;
	cin >> s;
	
	ll MOD = 1e9+7;
	ll pw[7];
	pw[0] = 1LL;
	for (int i = 1; i < 7; ++i)
		pw[i] = (pw[i - 1] * 3) % MOD;
	
	ll ans = 1LL;
	for (size_t i = 0; i < s.size(); ++i) {
		ans = (ans * pw[6 - __builtin_popcountll(val(s[i]))]) % MOD;
	}
	
	cout << ans << endl;
	
	return 0;
}
