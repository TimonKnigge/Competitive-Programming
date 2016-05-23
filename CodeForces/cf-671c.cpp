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

constexpr int MX = 200010;

int main() {
	
	int n;
	scanf("%d", &n);
	vi a(n, 0LL);
	for (int i = 0, v; i < n; ++i) {
		scanf("%d", &v);
		a[i] = ll(v);
	}
	
	vi fst(MX, -1LL);
	ll ans = 0LL, best = 0LL;
	for (int i = 0; i < n; ++i) {
		
		for (ll d = 1; d * d <= a[i]; ++d) {
			if (a[i] % d != 0LL) continue;
			ll dd = d;
			if (fst[dd] == -1LL)
				fst[dd] = i;
			else	ans = max(ans, dd);
			dd = a[i] / d;
			if (a[i] / d == d) continue;
			if (fst[dd] == -1LL)
				fst[dd] = i;
			else	ans = max(ans, dd);
		}
		
		if (i + 1 < n) ans += best;
	}
	
	return 0;
}
