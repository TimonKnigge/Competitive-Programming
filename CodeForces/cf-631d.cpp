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

ll gcd(ll a, ll b) { while (b) { a %= b; swap(a, b); } return a; }
ll lcm(ll a, ll b) { return (a / gcd(a, b)) * b;				 }
ll mod(ll a, ll b) { return ((a % b) + b) % b;				   }

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

// solves ab = 1 (mod n), -1 on failure
ll mod_inverse(ll a, ll n) {
	ll x, y, d;
	extended_euclid(a, n, x, y, d);
	return (d > 1 ? -1 : mod(x, n));
}

int main() {
	
	int aN, aM;
	scanf("%d %d", &aN, &aM);
	
	vector<pair<char, ll> > S, P;
	while (aN--) {
		char c;
		int cnt;
		scanf("%d-%c", &cnt, &c);
		if (S.size() > 0 && S.back().first == c)
			S.back().second += cnt;
		else	S.push_back({c, cnt});
	}
	while (aM--) {
		char c;
		int cnt;
		scanf("%d-%c", &cnt, &c);
		if (P.size() > 0 && P.back().first == c)
			P.back().second += cnt;
		else	P.push_back({c, cnt});
	}
	
	ll Pr[4] = {2, 3, 5, 7};
	ll M[4] = {ll(1e9) + 7, ll(1e9) + 9, ll(1e9) + 21, ll(1e9) + 33};
	
	ll hash[4] = {0LL, 0LL, 0LL, 0LL};
	ll pw[4] = {1LL, 1LL, 1LL, 1LL};
	for (size_t i = 1; i + 1 < P.size(); ++i) {
		for (int h = 0; h < 4; ++h) {
			hash[h] = (Pr[h] * hash[h]) + (P[i].first + 256 * P[i].second);
			hash[h] %= M[h];
			pw[h] = (pw[h] * Pr[h]) % M[h];
		}
	}
	
	ll pi[4] = {0LL, 0LL, 0LL, 0LL};
	for (int h = 0; h < 4; ++h)
		pi[h] = mod_inverse(pw[h], M[h]);
	
	if (S.size() < P.size()) {
		cout << 0 << endl;
		return 0;
	}
	if (P.size() == 1) {
		int ans = 0;
		for (size_t i = 0; i < S.size(); ++i) {
			if (S[i].first == P[0].first)
				ans += max(0LL, 1 + S[i].second - P[0].second);
		}
		cout << ans << endl;
		return 0;
	}
	
	ll rhash[4] = {0LL, 0LL, 0LL, 0LL};
	for (size_t i = 1; i + 1 < P.size(); ++i)
		for (int h = 0; h < 4; ++h) {
			rhash[h] = (Pr[h] * rhash[h]) + (S[i].first + 256 * S[i].second);
			rhash[h] %= M[h];
		}
	
	int PS = P.size(), ans = 0;
	for (size_t i = 0; i + PS <= S.size(); ++i) {
		bool y = true;
		for (int h = 0; h < 4; ++h) {
			y = y && (hash[h] == rhash[h]);
		}
		if (y &&
			P[0].first  == S[i].first &&
			P[0].second <= S[i].second &&
			P[PS-1].first  == S[i+PS-1].first &&
			P[PS-1].second <= S[i+PS-1].second
			) {
			++ans;
		}
		if (PS > 2) {
			for (int h = 0; h < 4; ++h) {
				rhash[h] = (rhash[h] * Pr[h]) % M[h];
				rhash[h] = (rhash[h] + M[h] - (pi[h] * (S[i+1].first + 256 * S[i+1].second)) % M[h]) % M[h];
				if (i + PS - 1 < S.size())
					rhash[h] = (rhash[h] + S[i+PS-1].first + 256 * S[i+PS-1].second) % M[h];
			}
		}
	}
	
	cout << ans << endl;
	
	return 0;
}
