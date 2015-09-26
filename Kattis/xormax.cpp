#include <iostream> 
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
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	vector<ll> bucket[64];
	for (int i = 0; i < n; ++i) {
		ll a;
		cin >> a;
		bucket[64 - __builtin_clzll(a)].push_back(a);
	}
	
	vector<ll> desc;
	for (int l = 63; l >= 0; --l) {
		if (bucket[l].size() == 0) continue;
		desc.push_back(bucket[l].back());
		bucket[l].pop_back();
		for (int i = 0; i < bucket[l].size(); ++i) {
			ll nw = bucket[l][i] ^ desc.back();
			if (nw > 0)
				bucket[64 - __builtin_clzll(nw)].push_back(nw);
		}
	}
	
	ll ans = 0LL;
	for (size_t i = 0; i < desc.size(); ++i) {
		if ((ans ^ desc[i]) > ans) ans = ans ^ desc[i];
	}
	
	cout << ans << endl;
	
	return 0;
}
