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


constexpr ll SIZE = 1e8+10;
vector<bool> bs;

int sieve(ll u) { // call at start in main!
	int p = 0;
	bs[0] = bs[1] = false;
	if (u > 1) ++p;
//	for (ll i = 4; i <= u; i += 2) bs[i] = false;
	if (u > 2) ++p;
//	for (ll i = 6; i <= u; i += 3) bs[i] = false;
	for (ll k = 6; k-1 <= u; k += 6) {
		if (bs[k-1]) {
			for (ll j = (k-1)*(k-1); j <= u; j += 2*k-2) bs[j] = false;
			++p;
		}
		if (k+1 <= u && bs[k+1]) {
			for (ll j = (k+1)*(k+1); j <= u; j += 2*k+2) bs[j]=false;
			++p;
		}
	}
//	for (ll i = 3; i <= u; i += 2) if (bs[i]) {
//		for (ll j = i * i; j <= u; j += i+i) bs[j] = false;
//		++p;
//	}
	return p;
}

int main() {
	
	int n, q;
	scanf("%d %d", &n, &q);
	
	bs.assign(n+1, true);
	cout << sieve(n) << '\n';
	
	while (q--) {
		int x;
		scanf("%d", &x);
		if (!(x&1)) cout << (x==2) << '\n';
		else if (x%3==0) cout << (x==3) << '\n';
		else cout << bs[x] << '\n';
	}
	
	return 0;
}
