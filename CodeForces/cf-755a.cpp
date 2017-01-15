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

ll SIZE; vector<bool> bs; vector<ll> primes, mf;// mf[i]==i when prime
void sieve(ll size = 1e6) { // call at start in main!
	SIZE = size; bs.assign(SIZE+1,1);
	bs[0] = bs[1] = 0;
	for (ll i = 2; i <= SIZE; i++) if (bs[i]) {
		for (ll j = i * i; j <= SIZE; j += i) bs[j] = 0;
		primes.push_back(i);
	}
}
bool is_prime(ll n) { // for N <= SIZE^2
	if (n <= SIZE) return bs[n];
	for(const auto &prime : primes)
	   	if (n % prime == 0) return false;
	return true;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	sieve(1e6);
	
	ll n;
	cin >> n;
	
	for (ll m = 1;; ++m) {
		if (!is_prime(n*m+1LL)) {
			cout << m << endl;
			break;
		}
	}
	
	return 0;
}
