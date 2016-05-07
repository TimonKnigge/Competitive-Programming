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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	ll n, k, mk = LLINF;
	cin >> n >> k;
	
	vi a(n, 0LL), b(n, 0LL);
	for (int i = 0; i < n; ++i) cin >> a[i];
	for (int i = 0; i < n; ++i) cin >> b[i];
	
	for (int i = 0; i < n; ++i) {
		mk = min(mk, b[i] / a[i]);
	}
	
	vector<pair<ll, ii>> remmod(n, {0LL, {0LL, 0LL}});
	for (int i = 0; i < n; ++i) {
		b[i] -= a[i] * mk;
		remmod[i] = {b[i] / a[i], {a[i] - b[i] % a[i], a[i]}};
	}
	
	ll sum = 0LL, sofar = 0LL;
	sort(remmod.begin(), remmod.end());
	
	bool cont = true;
	for (int l = 0, r = 0; l < n; l = r) {
		
		while (r < n && remmod[l].first == remmod[r].first) ++r;
		
		ll restcost = 0LL, sumcost = 0LL;
		for (int i = l; i < r; ++i) {
			remmod[i].first -= sofar;
			restcost += remmod[i].second.first;
			sumcost += remmod[i].second.second;
		}
		
		ll nw = remmod[l].first;
		if (sum > 0) nw = min(nw, k / sum);
		sofar += nw;
		k -= sum * nw;
		if (k < sum) {
			cont = false;
			break;
		}

		if (k >= restcost + sum) {
			sofar++;
			k -= restcost + sum;
		} else {
			cont = false;
			break;
		}
		
		sum += sumcost;
	}
	
	if (cont)
		sofar += k / sum;
	
	cout << (mk + sofar) << endl;
	
	
	return 0;
}
