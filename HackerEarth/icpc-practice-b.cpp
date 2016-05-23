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


ll SIZE;
vector<bool> bs;
vector<ll> primes;// mf[i]==i when prime

void sieve(ll size = 1e6) { // call at start in main!
	SIZE = size; bs.assign(SIZE+1,1);
	bs[0] = bs[1] = 0;
	for (ll i = 2; i <= SIZE; i++) if (bs[i]) {
		for (ll j = i * i; j <= SIZE; j += i) bs[j] = 0;
		primes.push_back(i);
	}
}

ll ccost(int i, int j) {
	ll ret = 0LL;
	if (i + 1 < j) {
		ret = primes[j - 1] - primes[i];
	}
	if (i + 1 > j) {
		ret = primes[i + 1] - primes[j];
	}
	return ret;
}

int main() {
	
	sieve(1e6 + 500);
	
	int N;
	scanf("%d", &N);
	if (N == 0) {
		printf("%d\n", 0);
		return 0;
	}
	
	ll cost = N / 2LL;
	
	vi A(N, 0LL);
	for (int i = 0, v; i < N; ++i) {
		scanf("%d", &v);
		
		int l = 0, r = primes.size();
		while (l < r) {
			int m = (l+r) / 2;
			if (primes[m] < v)
				l = m + 1;
			else	r = m;
		}
		
		cost += primes[l] - ll(v);
		A[i] = l;
	}
	
	vvi dp(N, vi(N, LLINF));
	for (int l = N - 2; l >= 0; --l) {
		
		dp[l][l + 1] = ccost(A[l], A[l + 1]);
		
		for (int r = l + 3; r < N; r += 2) {
			// calculate dp[l .. r]
			// stored in dp[l][r]
			for (int k = l + 1; k <= r; k += 2) {
				ll v = ccost(A[l], A[k]);
				if (k > l + 1)
					v += dp[l + 1][k - 1];
				if (k < r)
					v += dp[k + 1][r];
				if (v < dp[l][r])
					dp[l][r] = v;
			}
		}
	}
	
	cout << cost + dp[0][N - 1] << endl;
	
	return 0;
}
