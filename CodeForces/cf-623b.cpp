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
const ll LLINF = 90000000000000000;

ll gcd(ll a, ll b) {
	while (b) {
		a %= b;
		swap(a, b);
	}
	return a;
}


ll SIZE;
vector<bool> bs;
vector<ll> primes;

void sieve(ll size = 1e6) { // call at start in main!
	SIZE = size; bs.assign(SIZE+1,1);
	bs[0] = bs[1] = 0;
	for (ll i = 2; i <= SIZE; i++) if (bs[i]) {
		for (ll j = i * i; j <= SIZE; j += i) bs[j] = 0;
		primes.push_back(i);
	}
}

void factors(ll n, set<ll> &f) {
	for (size_t i = 0; i < primes.size(); ++i) {
		if (n % primes[i] == 0) f.insert(primes[i]);
		while (n%primes[i] == 0) n /= primes[i];
	}
	if (n > 1) f.insert(n);
}

vector<ll> cost[3];

ll cost_of(ll v, ll p, ll b) {
	if (v % p == 0) return 0;
	if ((v-1) % p == 0) return b;
	if ((v+1) % p == 0) return b;
	return LLINF;
}

void cap_at_llinf(ll &v) {
	if (v > LLINF) v = LLINF;
}

// b for change, a for seg
ll solve(int N, ll a, ll b, vector<ll> &A, ll p) {
	cost[0][0] = cost[2][0] = cost_of(A[0], p, b);
	cost[1][0] = a;
	for (int i = 1; i < N; ++i) {
		cost[0][i] = cost[0][i - 1] + cost_of(A[i], p, b);
		cost[1][i] = a + min(cost[0][i - 1], cost[1][i - 1]);
		cost[2][i] = min(cost[2][i - 1], cost[1][i - 1])
				+ cost_of(A[i], p, b);
		cap_at_llinf(cost[0][i]);
		cap_at_llinf(cost[1][i]);
		cap_at_llinf(cost[2][i]);
	}
	return min(cost[0][N-1], min(cost[1][N-1], cost[2][N-1]));
}

int main() {
	sieve();
	
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	ll N, a, b;
	cin >> N >> a >> b;
	
	cost[0].assign(N + 1, 0LL);
	cost[1].assign(N + 1, 0LL);
	cost[2].assign(N + 1, 0LL);
	vector<ll> A(N, 0LL);
	
	cin >> A[0];
	ll g = A[0];
	for (int i = 1; i < N; ++i) {
		cin >> A[i];
		g = gcd(g, A[i]);
	}
	if (g > 1) {
		cout << 0 << endl;
		return 0;
	}
	
	set<ll> ps;
	factors(A[0], ps);
	factors(A[0] + 1, ps);
	factors(A[0] - 1, ps);
	factors(A[N-1], ps);
	factors(A[N-1]+1, ps);
	factors(A[N-1]-1, ps);
	
	ll mn = LLINF;
	for (ll p : ps) {
		mn = min(mn, solve(N, a, b, A, p));
	}
	cout << mn << endl;
	
	return 0;
}
