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
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

void solve() {
	int n, m;
	scanf("%d %d", &n, &m);
	
	vvi bundle(m, vi());
	vector<int> price(m, 0LL);
	vector<vb> has(m, vb(n, false));
	vector<pair<int, int> > sizeid;
	for (int b = 0; b < m; ++b) {
		scanf("%d", &price[b]);
		int s;
		scanf("%d", &s);
		while (s--) {
			int dessert;
			scanf("%d", &dessert);
			dessert--;
			has[b][dessert] = true;
			bundle[b].push_back(dessert);
		}
		sizeid.push_back({bundle[b].size(), b});
	}
	
	vi lastowner(n, -1);
	vi roots;
	vvi children(m, vi());
	sort(sizeid.begin(), sizeid.end());
	for (int j = sizeid.size() - 1; j >= 0; --j) {
		int id = sizeid[j].second;
		int par = lastowner[bundle[id][0]];
		if (par == -1) roots.push_back(id);
		else children[par].push_back(id);
		
		for (int item : bundle[id])
			lastowner[item] = id;
	}
	
	vector<ll> fprice(m, 0LL);
	for (int j = 0; j < sizeid.size(); ++j) {
		int id = sizeid[j].second;
		
		fprice[id] = price[id];
		
		// Do the children cover this bundle? What is its cost?
		ll cost = 0LL;
		int items = 0;
		for (int c : children[id]) {
			cost += fprice[c];
			items += bundle[c].size();
		}
		
		if (items == bundle[id].size() && cost < fprice[id])
			fprice[id] = cost;
	}
	
	ll ans = 0LL;
	for (int r : roots) ans += fprice[r];
	cout << ans << endl;
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		solve();
	}
	
	return 0;
}
