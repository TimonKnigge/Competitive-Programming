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
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

ll mod(ll a, ll b) { return ((a % b) + b) % b; }
ll gcd(ll a, ll b) { while (b) { a %= b; swap(a, b); } return a; }

// Finds x, y s.t. ax + by = d = gcd(a, b).
void extended_euclid(ll a, ll b, ll &x, ll &y, ll &d) {
	ll xx = y = 0;
	ll yy = x = 1;
	while (b) {
		ll q = a / b;
		ll t = b; b = a % b; a = t;
		t = xx; xx = x - q * xx; x = t;
		t = yy; yy = y - q * yy; y = t;
	}
	d = a;
}

ll mod_inverse(ll a, ll n) {
	ll x, y, d;
	extended_euclid(a, n, x, y, d);
	return (d > 1 ? -1 : mod(x, n));
}

// Solve ax + by = c, returns false on failure.
bool linear_diophantine(ll a, ll b, ll c, ll &x, ll &y) {
	ll d = gcd(a, b);
	if (c % d) {
		return false;
	} else {
		x = c / d * mod_inverse(a / d, b / d);
		y = (c - a * x) / b;
		return true;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int T;
	cin >> T;
	while (T--) {
		int K, C;
		cin >> K >> C;
		
		ll x, y;
		if (linear_diophantine(K, C, 1LL, x, y)) {
			ll Kinc = K / gcd(K, C);
			ll Cinc = C / gcd(K, C);
			
			// Kx + Cy = 1
			if (y <= 0) {
				ll d = abs(y) / Kinc;
				y += Kinc * d;
				x -= Cinc * d;
				while (y <= 0) {
					y += Kinc;
					x -= Cinc;
				}
			}
			if (y > ll(1e9)) {
				ll d = (y - ll(1e9)) / Kinc;
				y -= Kinc * d;
				x += Cinc * d;
				while (y > ll(1e9)) {
					y -= Kinc;
					x += Cinc;
				}
			}
			if (y <= 0) cout << "IMPOSSIBLE\n";
			else {
				if (x >= 0) {
					ll d = x / Cinc;
					x -= d * Cinc;
					y += d * Kinc;
					while (x >= 0) {
						x -= Cinc;
						y += Kinc;
					}
				}
				if (x >= 0 || y <= 0 || y > ll(1e9))
					cout << "IMPOSSIBLE\n";
				else	cout << y << '\n';
			}
		} else cout << "IMPOSSIBLE\n";
	}
	
	cout << flush;
	
	return 0;
}
