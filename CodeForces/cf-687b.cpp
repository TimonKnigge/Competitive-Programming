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

ll gcd(ll a, ll b) {
	while (b) { a %= b; swap(a, b); } return a;
}

ll SIZE; vector<bool> bs; vector<ll> primes, mf;// mf[i]==i when prime
void sieve2(ll size=1e6) {	// call at start in main!
	SIZE = size; mf.assign(SIZE+1,-1);
	mf[0] = mf[1] = 1;
	for (ll i = 2; i <= SIZE; i++) if (mf[i] < 0) {
		mf[i] = i;
		for (ll j = i * i; j <= SIZE; j += i)
			if(mf[j] < 0) mf[j] = i;
		primes.push_back(i);
	}
}

void madd(map<ll, ll> &m, ll v) {
	auto it = m.find(v);
	if (it == m.end())
		m.insert({v, 1});
	else	it->second++;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	sieve2(1e6+3);
	
	ll n, k;
	cin >> n >> k;
	
	map<ll, ll> kfactors;
	ll kk = k;
	while (kk > 1) {
		madd(kfactors, mf[kk]);
		kk /= mf[kk];
	}
	
	map<ll, ll> tfactors;
	while (n--) {
		ll v;
		cin >> v;
		while (v > 1) {
			ii pr = {mf[v], 0};
			while (v % pr.first == 0) v /= pr.first, ++pr.second;
			auto it = tfactors.find(pr.first);
			if (it == tfactors.end())
				tfactors.insert(pr);
			else	it->second = max(it->second, pr.second);
		}
	}
	
	bool y = true;
	for (ii pr : kfactors) {
		auto it = tfactors.find(pr.first);
		y = y && (it != tfactors.end() && it->second >= pr.second);
	}
	
	cout << (y ? "Yes" : "No") << endl;
	
	return 0;
}
