#include <iostream> 
#include <string>
#include <cstring>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <bitset>
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

constexpr ll SIZE = 1e3+10;
bitset<SIZE> bs;
vector<ll> primes;

void sieve() { 
	bs.set();
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

	int n;
	cin >> n;
	
	vector<int> mustprint;
	for (ll p : primes) {
		for (ll q = p; q <= n; q = q * p) {
			mustprint.push_back(q);
		}
	}
	
	cout << mustprint.size() << endl;
	for (size_t i = 0; i < mustprint.size(); ++i) {
		cout << mustprint[i] << " \n"[i == mustprint.size() - 1];
	}
	
	return 0;
}
