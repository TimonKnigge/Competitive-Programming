#include <iostream>
#include <iomanip>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <bitset>
#include <algorithm>
#include <functional>
#include <string>
#include <math.h>

#define INF 2000000000

using namespace std;

typedef pair <int, int > ii;
typedef vector <int > vi;
typedef vector < vi > vvi;
typedef vector < ii > vii;
typedef vector < vii > vvii;
typedef vector <bool > vb;
typedef long long ll;
typedef long double ld;

// PRIMES
ll _sieve_size;
bitset<10000010> bs;
vi primes;

void sieve(ll upperbound) {
	_sieve_size = upperbound + 1;
	bs.reset(); bs.flip();
	bs.set(0, false); bs.set(1, false);
	for (ll i = 2; i <= _sieve_size; ++i) {
		for (ll j = i * i; j <= _sieve_size; j += i) bs.set((size_t)j, false);
		primes.push_back((int)i);
	}
}

bool is_prime(ll N) {
	if (N < _sieve_size) return bs.test(N);
	for (int i = 0; i < primes.size(); ++i) if (N % primes[i] == 0) return false;
	return true;
}
// -PRIMES
// MAXFLOW

// -MAXFLOW

struct Fox {
public:
	int a = -1, id = -1;
	bool odd = false;
	Fox() {}
	Fox(int a, int id) : a(a), odd(a % 2 == 1), id(id) {}
};

int main() {
	sieve(1e5);
	int n;
	cin >> n;

	vector<Fox> oddFoxes, evenFoxes;
	for (int i = 0; i < n; ++i) {
		int a; cin >> a;
		if (a % 2 == 0)
			evenFoxes.push_back(Fox(a, i + 1));
		else
			oddFoxes.push_back(Fox(a, i + 1));
	}

	// Connect all odd foxes to the sink, even foxes to the source:
	for (Fox v : evenFoxes) e[0][v.id].push_back(ii(..));
	for (Fox v : oddFoxes)  e[v.id]
	
	return 0;
}
