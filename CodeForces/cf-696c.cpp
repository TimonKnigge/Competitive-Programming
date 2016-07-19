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

constexpr ll MOD = 1e9+7;

ll modpow(ll a, ll b, ll m) {
	if (b == 0LL) return 0LL;
	if (b == 1LL) return a;
	ll r = modpow((a*a) % m, b / 2, m);
	if (b&1) r = (r * a) % m;
	return r;
}

ll mod(ll a) { return (a%MOD+MOD)%MOD; }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int k;
	cin >> k;
	
	vi a(k, 0LL);
	ll s = 1LL;
	bool nisnull = true;
	for (int i = 0; i < k; ++i) {
		cin >> a[i];
		s = (s * a[i]) % 2LL;
		if (a[i] > 1LL) nisnull = false;
	}
	
	ll mtwo = MOD - 2, mtwoinv = modpow(MOD - 2, MOD - 2, MOD);
	for (int i = 0; i < k; ++i) {
		mtwo = modpow(mtwo, a[i], MOD);
	}
	mtwo = (mtwo * mtwoinv) % MOD;
	
//	cerr << "(-2)^(n-1) = " << mtwo << endl;
	
	ll num = mod(mtwo - 1LL);
	ll den = mtwo;
	num = num * modpow(3, MOD-2, MOD) % MOD;
	if (s == 0LL) {
		den = (MOD - den) % MOD;
		num = (MOD - num) % MOD;
	}
	
	cout << num << '/' << den << endl;
	
	return 0;
}
