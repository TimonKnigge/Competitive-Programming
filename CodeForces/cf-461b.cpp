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

// {open (black), open (no black)
pair<ll, ll> dfs(int u, vvi &ch, vb &color) {
	
	vii vch(ch[u].size(), {0LL, 0LL});
	for (size_t i = 0; i < ch[u].size(); ++i) {
		vch[i] = dfs(ch[u][i], ch, color);
		vch[i].second = (vch[i].second + vch[i].first) % MOD;
	}
	
	ii ret = {0LL, 0LL};
	
	if (color[u]) { // this vertex is black
		ll openb = 1LL;
		for (size_t i = 0; i < ch[u].size(); ++i) {
			if (color[ch[u][i]]) {
				openb = (openb * vch[i].first) % MOD;
			} else {
				openb = (openb * vch[i].second) % MOD;
			}
		}
		ret.first = openb;
	} else {
		ll openw = 1LL;
		vi oppref(ch[u].size(), 1LL), opsuff(ch[u].size(), 1LL);
		for (size_t i = 0; i < ch[u].size(); ++i) {
			openw = (openw * vch[i].second) % MOD;
			oppref[i] = openw;
		}
		openw = 1LL;
		for (size_t i = 0; i < ch[u].size(); ++i) {
			openw = (openw * vch[ch[u].size() - 1 - i].second) % MOD;
			opsuff[ch[u].size() - 1 - i] = openw;
		}
		
		ll openb = 0LL;
		for (size_t i = 0; i < ch[u].size(); ++i) {
			openb = (openb + (((i > 0 ? oppref[i - 1] : 1LL)
				* vch[i].first) % MOD) * (i + 1 < ch[u].size()
				? opsuff[i + 1] : 1LL)) % MOD;
		}
		
		ret.first = openb;
		ret.second = openw;
	}
	
	return ret;
}

int main() {
	
	int N;
	scanf("%d", &N);
	vi P(N, -1);
	vvi ch(N, vi());
	
	for (int i = 1; i < N; ++i) {
		int v;
		scanf("%d", &v);
		P[i] = v;
		ch[v].push_back(i);
	}
	
	vb color(N, false);
	for (int i = 0; i < N; ++i) {
		int xi;
		scanf("%d", &xi);
		color[i] = xi == 1;
	}
	
	pair<ll, ll> ans = dfs(0, ch, color);
	cout << ans.first << endl;
	
	return 0;
}
