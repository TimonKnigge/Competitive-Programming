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
#include <complex>

using namespace std;
using ll = unsigned long long;
using ld = long double;
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

constexpr ll MOD = 1004535809;

constexpr ll SIZE = 3e5+10;
bitset<SIZE + 1> bs;
vector<ll> primes;

void sieve() { // call at start in main!
	bs.set();
	bs[0] = bs[1] = 0;
	for (ll i = 2; i <= SIZE; i++) if (bs[i]) {
		for (ll j = i * i; j <= SIZE; j += i) bs[j] = 0;
		primes.push_back(i);
	}
}

void quadratic_convolution(vector<ll> &A, vector<ll> &B, vector<ll> &C, int cap) {
	C.assign(min(int(A.size() + B.size()) - 1, cap), 0LL);
	for (int i = 0; i < A.size(); ++i)
		for (int j = 0; j < B.size() && i + j < cap; ++j) {
			C[i + j] += A[i] * B[j];
			C[i + j] %= MOD;
		}
}

void bin_pow_cap_at(vector<ll> &a, int k, int cap, vector<ll> &res) {
	if (k == 0) {
		res.assign(cap, 0LL);
		res[0] = 1LL;
	} else if (k == 1) {
		res.assign(cap, 0LL);
		for (int i = 0; i < min(int(a.size()), cap); ++i)
			res[i] = a[i] % MOD;
	} else if (!(k&1)) {
		vector<ll> aa;
		quadratic_convolution(a, a, aa, cap);
		bin_pow_cap_at(aa, k / 2, cap, res);
	} else {
		vector<ll> aa, tmp;
		quadratic_convolution(a, a, aa, cap);
		bin_pow_cap_at(aa, k / 2, cap, tmp);
		quadratic_convolution(a, tmp, res, cap);
	}
}


int main() {
	
	int n, k;
	scanf("%d %d", &n, &k);
	
	sieve();
	
	// For each i=0..n, calculate all numbers j
	// such that pi(j) = i
	vector<ll> pic(n + 1, 0);
	for (int i = 0; i < int(primes.size()) && i <= n; ++i) {
		pic[i] = primes[i] - (i > 0 ? primes[i - 1] : 1);
	}
	
	vector<ll> res;
	bin_pow_cap_at(pic, k, n + 1, res);
	cout << (res[n] % MOD) << endl;
	
	return 0;
}
