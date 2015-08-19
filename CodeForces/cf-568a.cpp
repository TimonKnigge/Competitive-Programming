#include <iostream>
#include <iomanip>
#include <vector>	       
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <bitset>
#include <algorithm>
#include <functional>
#include <string>
#include <string.h>  // Include for memset!
#include <complex>
#include <random>
#define _USE_MATH_DEFINES
#include <math.h>

const int INF = 2000000000;	                 // 9
const long long LLINF = 9000000000000000000LL;  // 18
const long double LDINF = 1e300;

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<bool> vb;
typedef long long ll;
typedef long double ld;

ll _sieve_size;
bitset<10000010> bs;
vi primes;

void sieve(ll upperbound) {
	_sieve_size = upperbound + 1;
	bs.reset(); bs.flip();
	bs.set(0, false); bs.set(1, false);
	for (ll i = 2; i <= _sieve_size; ++i) {
		for (ll j = i * i; j <= _sieve_size; j += i) bs.set((size_t)j, false);
		primes.push_back(int(i));
	}
}
int primes_leq_than(int n) {
	int l = 0, r = primes.size() - 1;
	while (l < r) {
		int m = int((ll(l) + ll(r)) / 2);
		if (primes[m] < n) l = m + 1;
		else r = m;
	}
	return l + 1;
}

stack<int> st;
ll palindromes_leq_than(ll n) {
	while (n > 0) { st.push(n % 10); n /= 10; }
	int d = st.size(), d2 = st.size();
	bool ch = 
	ll ans = 1;
	while (!st.empty()) {
		int x = st.top(); st.pop();
		if (d > 0) {
			ans *= (x + 1);
			d -= 2;
		}
	}
	return ans + 
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
		
	
	return 0;
}
