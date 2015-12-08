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
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

ll MOD = 1e9 + 7;

ll modpow(ll a, ll n, ll m) {
	if (n == 0) return 1LL;
	if (n == 1) return a % m;
	ll res = modpow((a*a) % m, n / 2, m);
	if (n&1) res = (res * a) % m;
	return res;
}

int main() {
	
	ll p, k;
	cin >> p >> k;
	
	if (k == 0) {
		cout << modpow(p, p - 1, MOD) << endl;
	} else {
		// Find cycles
		int cyc = 0;
		vb vis(p, false);
		vis[0] = true;
		int zeropos = 1;
		for (ll i = 1; i < p; ++i) {
			if ((k*i) % p == i) zeropos++;
			if (vis[i]) continue;
			cyc++;
			ll j = i;
			while (!vis[j]) {
				vis[j] = true;
				j = (k * j) % p;
			}
		}
		
		cout << ((ll(zeropos) * modpow(p, cyc, MOD)) % MOD) << endl;
	}
	
	return 0;
}
