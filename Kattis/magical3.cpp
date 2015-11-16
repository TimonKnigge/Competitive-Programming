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

ll smpf(ll n) {
	if (n == 0 || n == 1) return n;
	if (n % 2 == 0) return 2;
	if (n % 3 == 0) return 3;
	if (n % 5 == 0) return 5;
	for (ll i = 7; i*i <= n; i += 30) {
	        if ( n % i == 0 ) {
	            return i;
	        }
	        if ( n % ( i+4 ) == 0) {
	            return i+4;
	        }
	        if ( n % ( i+6 ) == 0) {
	            return i+6;
	        }
	        if ( n % ( i+10 ) == 0) {
	            return i+10;
	        }
	        if ( n % ( i+12 ) == 0) {
	            return i+12;
	        }
	        if ( n % ( i+16 ) == 0) {
	            return i+16;
	        }
	        if ( n % ( i+22 ) == 0) {
	            return i+22;
	        }
	        if ( n % ( i+24 ) == 0) {
	            return i+24;
	        }
	}
	return n;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	while (true) {
		ll n;
		cin >> n;
		if (n == 0) break;
		
		if (n < 3 || (n > 3 && n <= 6)) {
			cout << "No such base\n";
			continue;
		}
		if (n % 4 == 3) {
			cout << 4 << '\n';
			continue;
		}
		
		n -= 3;
		// Find any divisor of n-3
		ll d = smpf(n);
		if (d < 4) { 
			ll d2 = smpf(n / d);
			if (d2 < 4) {
				d *= d2;
				for (int pd = 4; pd <= d; ++pd) {
					if (n%pd == 0) d = pd;
				}
			} else d = d2;
		}
		if (d < 4) cout << "No such base\n";
		else cout << d << '\n';
		
	}
	
	return 0;
}
