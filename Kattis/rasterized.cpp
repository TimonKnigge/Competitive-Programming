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

constexpr ll SIZE = 1e7+10;
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

ll phi(ll n) {
	ll ans = n, pn = n;
	unsigned int s = primes.size();
	for (unsigned int i = 0; i < s && primes[i]*primes[i]<=pn; ++i)
		if (pn % primes[i] == 0) {
			ans -= ans / primes[i];
			while (pn % primes[i] == 0) pn /= primes[i];
		}
	if (pn > 1) ans -= ans / pn;
	return ans;
}

void factorize(ll n, vector<pair<ll, int> > &f) {
	for (unsigned int i = 0; i<primes.size()
				&& primes[i]*primes[i] <= n; ++i) {
		if (n % primes[i] == 0) {
			int p = 0;
			while (n%primes[i] == 0) {
				n /= primes[i];
				++p;
			}
			f.push_back({primes[i], p});
		}
	}
	if (n > 1) f.push_back({n, 1});
}

vector<ll> divisors(vector<pair<ll, int> > &f) {
	vector<ll> res(1, 1);
	for (unsigned int i = 0; i < f.size(); ++i) {
		int o = int(res.size());
		for (int j = 0; j < f[i].second * o; ++j) {
			res.push_back(res[int(res.size()) - o] * f[i].first);
		}
	}
	return res;
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	sieve();
	
	int T;
	cin >> T;
	while (T--) {
		ll N;
		cin >> N;
		
		ll sq = ll(sqrt(N)) + 10, ans = 0LL;
//		int div = 0;
//		for (ll d = 1; d <= sq && div < 47; ++d) {
//			if (N % d != 0) continue;
//			if (d <= N / d) { 
//				ans += phi(d + 1);
//				++div;
//			} else break;
//			if (d <  N / d) {
//				ans += phi(N / d + 1);
//				++div;
//			}
//		}
		vector<pair<ll, int> > f;
		factorize(N, f);
		vector<ll> div = divisors(f);
		for (int i = 0; i < int(div.size()); ++i)
			ans += phi(div[i] + 1);
		cout << ans << '\n';
	}
	
	return 0;
}
