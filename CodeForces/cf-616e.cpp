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

ll MOD = 1e9 + 7;

ll mod(ll v, ll m) {
	return ((v%m)+m)%m;
}

int main() {
	
	ll N, M;
	cin >> N >> M;
	
	ll ans = 0LL;
	
	if (M > N) {
		ll d = M - N;
		d %= MOD;
		ans = (d * (N % MOD)) % MOD;
		M = N - 1;
	}
	
	ll sqc = ll(sqrt(N)) + 1;
	
	ll lowest = M + 1;
	for (ll k = 1; k < sqc; ++k) {
		ll UP = N / k;
		if (UP == 0) continue;
		if (UP > M) UP = M;
		ll LO = N / (k + 1) + 1;
		if (UP < LO) continue;
		lowest = min(lowest, LO);
		
		ll diff = k;
		ll len  = UP - LO + 1;
		ll base = N % UP;
		diff %= MOD; len %= MOD; base %= MOD;
		
		ll sum = (len * base) % MOD;
		sum = (sum + diff * ((len * (len-1) / 2) % MOD)) % MOD;
		
		ans = (ans + sum) % MOD;
	}
	
	for (ll v = 1; v < lowest; ++v) {
		ans = (ans + (N % v)) % MOD;
	}
	
	cout << ans << endl;
	
	return 0;
}
