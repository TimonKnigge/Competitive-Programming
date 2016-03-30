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

ll MOD = 1e9 + 7;

ll solveleft(int l, int r, ll U, vi &H) {
	
	ll ret = min(U, H[r] - 1LL);
	if (l < r) {
		ll thisw = min(H[r - 1] - 1, min(U, H[r] - 1));
		ret = (ret + thisw * solveleft(l, r - 1, H[r] - 1, H)) % MOD;
	}
	
	return ret;
}

ll solveright(int l, int r, ll U, vi &H) {
	
	ll ret = min(U, H[l] - 1LL);
	if (l < r) {
		ll thisw = min(H[l + 1] - 1, min(U, H[l] - 1));
		ret = (ret + thisw * solveright(l + 1, r, H[l] - 1, H)) % MOD;
	}
	
	return ret;
}

ll divcon(int l, int r, vi &H) {
	
	if (l > r) return 0LL;
	if (l == r) return H[l] - 1LL;
	
	int m = (l + r) / 2;
	ll ret = 0LL;
	
	ll lways = 1LL, rways = 1LL;
	if (l < m) lways = solveleft (l, m - 1, H[m] - 1, H);
	if (m < r) rways = solveright(m + 1, r, H[m] - 1, H);
	
	ret = H[m] - 1;
	if (l < m)
		ret = (ret + (min(H[m], H[m - 1]) - 1) * lways) % MOD;
	if (m < r)
		ret = (ret + (min(H[m], H[m + 1]) - 1) * rways) % MOD;
	if (l < m && m < r)
		ret = (ret + (min(H[m],min(H[m+1],H[m-1]))-1) * 
			((lways * rways) % MOD)) % MOD;
	
	ret += divcon(l, m - 1, H);
	ret += divcon(m + 1, r, H);
	ret %= MOD;
	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	ll N;
	cin >> N;
	
	vi H(N, 0LL);
	for (int i = 0; i < N; ++i)
		cin >> H[i];
	
	cout << divcon(0, N - 1, H) << endl;
	
	return 0;
}
