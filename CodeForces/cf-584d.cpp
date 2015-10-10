#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

// (a*b)%m
ll mulmod(ll a, ll b, ll m){
	ll x = 0, y=a%m;
	while(b>0){
		if(b&1)
			x = (x+y)%m;
		y = (2*y)%m;
		b/=2;
	}
	return x % m;
}

// Finds a^n % m in O(lg n) time, ensure that a < m to avoid overflow!
ll powmod(ll a, ll n, ll m) {
	if (n == 0) return 1;
	if (n == 1) return a;
	ll aa = (a*a)%m; // use mulmod when b > 1e9
	if (n % 2 == 0) return powmod(aa, n / 2, m);
	return (a * powmod(aa, (n - 1) / 2, m)) % m;
}

vector<ll> test_primes = {2,3,5,7,11,13,17,19,23}; // sufficient to 3.8e18
bool miller_rabin(const ll n){ // true when prime
	if(n<2) return false;
	if(n%2==0) return n==2;
	ll s = 0, d = n-1; // n-1 = 2^s * d
	while(d&1) s++, d/=2;
	for(auto a : test_primes){
		if(a > n-2) break;
		ll x = powmod(a,d,n);	// needs powmod with mulmod!
		if(x == 1 || x == n-1) continue;
		for (int i = 0; i < s - 1; ++i) {  //REP(i,s-1){
			x = mulmod(x,x,n);
			if(x==1) return false;
			if(x==n-1) goto next_it;
		}
		return false;
next_it:;
	}
	return true;
}

int main() {
	ll n;
	cin >> n;
	
	int p1 = n;
	while (!miller_rabin(p1)) p1 -= 2;
	
	if (p1 == n) { cout << 1 << endl << n << endl; }
	else {
		n -= p1;
		if (n == 2) cout << 2 << endl << p1 << ' ' << n << endl;
		else if (n == 4) cout << 3 << endl << p1 << " 2 2" << endl;
		else {
			for (int d = 3; d <= n; d += 2) {
				bool dp = true, ndp = true;
				for (int q = 3; q < d && dp; q += 2)
					dp = dp && (d % q != 0);
				for (int q = 3; q < n - d && ndp; q += 2)
					ndp = ndp && ((n-d) % q != 0);

				if (dp && ndp) {
					cout << 3 << endl;
					cout << p1 << " " << d << " ";
					cout << n-d << endl;
					break;
				}
			}
		}
	}
	
	return 0;
}
