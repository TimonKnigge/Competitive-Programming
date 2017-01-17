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
using namespace chrono;
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

bool test(vi &cyc, ll k) {
	// k <= n/2 given
	while (!cyc.empty() && cyc.back() > k) cyc.pop_back();
	if (cyc.empty()) return k == 0;
	if (cyc.back() == k) return true;
	
	vb dp(k+1, false);
	dp[0] = true;
	for (size_t l = 0, r = 0; l < cyc.size(); l = r) {
		while (r < cyc.size() && cyc[l] == cyc[r]) ++r;
		for (int i = 0; i < cyc[l]; ++i) {
			int last = -INF;
			for (int j = i; j <= k; j += cyc[l]) {
				if (dp[j]) last = j;
				if (last >= j - cyc[l] * int(r - l))
					dp[j] = true;
			}
		}
	}
	return dp[k];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, k;
	cin >> n >> k;
	
	vi p(n, 0LL);
	for (ll &v : p) cin >> v, --v;
	
	if (k <= 1) { 
		cout << (2*k) << ' ' << (2*k) << endl;
		return 0;
	}
	
	// Collect cyles
	vi cyc;
	vb vis(n, false);
	for (int i = 0; i < n; ++i) {
		if (vis[i]) continue;
		int j = i, l = 0;
		while (!vis[j]) {
			vis[j] = true;
			j = p[j];
			++l;
		}
		cyc.push_back(l);
	}
	
	sort(cyc.begin(), cyc.end());

//	cerr << "Found cycles => ";
//	for (ll v : cyc) cerr << v << ' ';
//	cerr << endl;
	
	ll maxans = 0LL, minans = 0LL;
	
	// Calculate the max
	ll kk = k;
	for (ll v : cyc) {
		if (v&1) continue;
		if (kk >= v/2LL) {
			maxans += v;
			kk -= v/2LL;
		} else {
			maxans += 2LL * kk;
			kk -= kk;
		}
	}
	ll e = 0LL;
	for (ll v : cyc) {
		if (v&1) {
			if (kk >= (v-1LL) / 2LL) {
				maxans += v-1LL;
				kk -= (v-1LL) / 2LL;
				++e;
			} else {
				maxans += 2LL * kk;
				kk -= kk;
			}
		}
	}
	maxans += min(kk, e);
	
	// Calculate the min
	minans = k + 1LL;
	if (k > n - k) k = n - k;
	if (test(cyc, k)) --minans;
	
	cout << minans << ' ' << maxans << endl;
	
	return 0;
}
