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

void madd(map<ll, ll> &m, ll k, ll w) {
	auto it = m.find(k);
//	cerr << "Adding " << w << " to " << k << endl;
	if (it == m.end()) m.insert({k, w});
	else it->second += w;
}

ll mfind(map<ll, ll> &m, ll k) {
	auto it = m.find(k);
	ll res = it != m.end() ? it->second : 0LL;
//	cerr << k << " goes to " << res << endl;
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int q;
	cin >> q;
	
	map<ll, ll> cost;
	
	while (q--) {
		int t;
		cin >> t;
		if (t == 1) {
			ll v, u, w;
			cin >> v >> u >> w;
			while (v != u) {
				if (v < u) {
					madd(cost, u, w); u /= 2LL;
				} else if (v > u) {
					madd(cost, v, w); v /= 2LL;
				}
			}
		} else {
			ll v, u, res = 0LL;
			cin >> v >> u;
			while (v != u) {
				if (v < u) {
					res += mfind(cost, u); u /= 2LL;
				} else if (v > u) {
					res += mfind(cost, v); v /= 2LL;
				}
			}
			cout << res << '\n';
		}
	}
	
	return 0;
}
