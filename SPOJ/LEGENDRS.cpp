#include <iostream> 
using namespace std; 

long long modpow(long long a, long long b, long long p) { 
//	cerr << a << ' ' << b << ' ' << p << endl;
	if (b == 0) return (a == 0 ? 0 : 1); 
	if (b == 1) return a % p; 
	long long r = modpow((a * a) % p, b / 2, p); 
	if (b&1) r = (r * a) % p; 
	return r;
} 

long long fix(long long r, long long p) { return r <= p / 2 ? r : r - p; }

int main() { 
	int t; 
	cin >> t; 
	while (t--) { 
		long long a, p; 
		cin >> a >> p; 
		cout << fix(modpow(a % p, (p - 1) / 2, p), p) << endl; 
	} 
	return 0; 
}

