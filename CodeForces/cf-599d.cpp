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
using ll = unsigned long long;
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

ll nsq(ll n) {
	return n * (n + 1) * (2 * n + 1) / 6;
}
ll ns(ll n) {
	return n * (n + 1) / 2;
}

int main() {
	
	ll k;
	cin >> k;
	
	vector<pair<ll, ll> > ans;
	for (int n = 1; nsq(n) <= k; ++n) {
		ll sm = nsq(n);
		ll ad = ns(n);
		ll tm = (k - sm) / ad;
		if (tm * ad + sm == k) {
			ans.push_back({n, n + tm});
			if (tm != 0)
				ans.push_back({n + tm, n});
		}
	}
	
	sort(ans.begin(), ans.end());
	cout << ans.size() << endl;
	for (int i = 0; i < ans.size(); ++i) {
		cout << ans[i].first << ' ' << ans[i].second << '\n';
	}
	
	return 0;
}
