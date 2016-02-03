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

constexpr ll SIZE = 1e6+10;
vector<ll> primes;
vector<ll> mf(SIZE + 1, -1);		// mf[i]==i when prime

void sieve2() { // call at start in main!
	mf[0] = mf[1] = 1;
	for (ll i = 2; i <= SIZE; i++) if (mf[i] < 0) {
		mf[i] = i;
		for (ll j = 2 * i; j <= SIZE; j += i)
			mf[j] = i;
		primes.push_back(i);
	}
}

int gcd(int a, int b) {
	while (b) { a %= b; swap(a, b); }
	return a;
}


int main() {
	
	int N, K;
	scanf("%d %d", &N, &K);
	vi A(N, 0LL);
	for (int i = 0; i < N; ++i)
		scanf("%d", &A[i]);
	
	sieve2();
	
	int l = 1, r = int(1e6);
	while (l < r) {
		int m = (l+r) / 2;
		// require that mf[gcd]>=m
		int blocks = 1, g = A[0];
		bool pos = true;
		for (int i = 1; i < N && pos; ++i) {
			if (mf[A[i]] < m) pos = false;
			
			int ng = gcd(g, A[i]);
			if (mf[ng] >= m) g = ng;
			else {
				g = A[i];
				++blocks;
			}
		}
		if (pos && blocks <= K) l = m + 1;
		else			r = m;
	}
	
	cout << (l == 2 ? 0 : l - 1) << endl;
	
	return 0;
}
