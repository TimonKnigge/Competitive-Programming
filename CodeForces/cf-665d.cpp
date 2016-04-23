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


ll SIZE;
vector<bool> bs; 
vector<ll> primes;// mf[i]==i when prime

void sieve(ll size = 2e6) { // call at start in main!
	SIZE = size; bs.assign(SIZE+1,1);
	bs[0] = bs[1] = 0;
	for (ll i = 2; i <= SIZE; i++) if (bs[i]) {
		for (ll j = i * i; j <= SIZE; j += i) bs[j] = 0;
		primes.push_back(i);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	sieve();
	
	int N;
	cin >> N;
	map<ll, ll> elems;
	for (int i = 0, v; i < N; ++i) {
		cin >> v;
		auto it = elems.find(v);
		if (it == elems.end())
			elems.insert({v, 1});
		else	it->second++;
	}
	
	ll optc = 1LL;
	ll optf = elems.begin()->first, opts = -1LL;
	ll optfc = 1LL, optsc = 0LL;
	for (auto it : elems) {
		if (bs[2LL * it.first] && it.second > optc) {
			optc = it.second;
			optf = it.first;
			optfc = it.second;
			opts = -1LL;
			optsc = 0LL;
		}
		
		for (auto it2 : elems) {
			if (it2.first == it.first) continue;
			if (!bs[it.first + it2.first]) continue;
			if (optc == 1LL) {
				optc = 2LL;
				optf = it.first;
				opts = it2.first;
				optfc = 1LL;
				optsc = 1LL;
			}
			if (!bs[2LL * it.first]) continue;
			
			if (1 + it.second > optc) {
				optc = 1 + it.second;
				optf = it.first;
				opts = it2.first;
				optfc = it.second;
				optsc = 1LL;
			}
			if (bs[2LL * it2.second] && it.second + it2.second > optc) {
				optc = it.second + it2.second;
				optf = it.first;
				opts = it2.first;
				optfc = it.second;
				optsc = it2.second;
			}
		}
	}
	
	cout << optc << endl;
	while (optfc > 0LL) cout << optf << " \n"[optsc == 0LL], --optfc;
	while (optsc > 0LL) cout << opts << " \n"[optsc == 1LL], --optsc;
	
	return 0;
}
