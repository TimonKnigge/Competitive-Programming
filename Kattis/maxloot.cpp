#include <iostream> 
#include <cstring>
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

constexpr int INF = 2000000000;
constexpr ll LLINF = 9000000000000000000LL;

constexpr int magic_constant = 38;
ll mc[1 << ((77 - magic_constant) / 2)];

int main() {
	
	int T;
	scanf("%d", &T);
	while (T--) {
		int n, _C;
		scanf("%d %d", &n, &_C);
		ll C = ll(_C);
		
		vi v(n, 0), c(n, 0);
		for (int i = 0; i < n; ++i) scanf("%d", &v[i]);
		for (int i = 0; i < n; ++i) scanf("%d", &c[i]);
		
		// 	n >= 25
		// <=>	2 log_2 V <= 50
		// <=>	V <= 2^25

		ll VMax = 0LL;
		for (int i = 0; i < n; ++i) VMax += v[i];
		
		if (n <= magic_constant) {
			int sz = n / 2;
			vector<pair<ll, ll> > val; // (cost, value)
			for (unsigned int mask = 0; mask < (1 << sz); ++mask) {
				ll cost = 0LL, value = 0LL;
				for (int i = 0; i < sz; ++i) {
					if (1&(mask >> i)) {
						cost += c[i];
						value += v[i];
					}
				}
				if (cost <= C) {
					val.push_back({cost, value});
				}
			}
			sort(val.begin(), val.end());
			for (int i = 1; i < val.size(); ++i)
				val[i].second = max(val[i].second, 
							val[i-1].second);
			ll best = 0LL;
			for (unsigned int mask = 0; mask < (1 << (n - sz)); 
								++ mask) {
				ll cost = 0LL, value = 0LL;
				for (int i = sz; i < n; ++i) {
					if (1&(mask >> (i - sz))) {
						cost += c[i];
						value += v[i];
					}
				}
				int l = 0, r = -1 + val.size();
				while (l < r) {
					int m = (l + r) / 2;
					if (val[m].first + cost <= C)
						l = m + 1;
					else	r = m;
				}
				while (l > 0 && val[l].first + cost > C) l--;
				if (val[l].first + cost <= C
					&& val[l].second + value > best)
					best = val[l].second + value;
			}
			cout << best << endl;
		} else {
			memset(mc, -1, sizeof(mc));
			mc[0] = 0LL;
			for (int i = 0; i < n; ++i)
			for (int val = VMax - v[i]; val >= 0; --val) {
				if (mc[val] >= 0 
					&& (mc[val + v[i]] > mc[val] + c[i] 
					 || mc[val + v[i]] == -1)
					&& mc[val] + c[i] <= C)
					mc[val + v[i]] = mc[val] + c[i];
			}
			ll best = VMax;
			while (mc[best] == -1) best--;
			cout << best << endl;
		}
	}
	
	return 0;
}
