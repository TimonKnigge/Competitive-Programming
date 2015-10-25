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

int main() {
	
	// Knapsacks, slots, time to pick up a knapsack
	int n, s, t;
	assert(3 == scanf("%d %d %d", &n, &s, &t));
	
	vector<int> k(n, 0);
	for (int i = 0; i < n; ++i)
		assert(1 == scanf("%d", &k[i]));
	sort(k.begin(), k.end());
	
	vector<pair<int, ll> > ts; // Time starting from
	for (int j = 0; j < int(k.size()); ++j) {
//		cerr << "Will now simulate " << j << endl;
		if (j > 0 && k[j - 1] == k[j]) continue;
		
		map<int, int> ks;
		for (int i = 0; i < int(k.size()); ++i)
			if (i > 0 && k[i - 1] == k[i])
				ks[k[i]]++;
			else	ks.insert({k[i], 1});
//		for (auto p : ks) cerr << p.first <<' ' << p.second<<endl;
		
		// Simulate starting from position k[j]
		int pos = k[j], ks_left = n;
		ll time = 0LL;
		while (ks_left > 0) {
			// Find the next knapsack
			auto it = ks.lower_bound(pos);
			if (it == ks.end()) it = ks.begin();
//			cerr << "Found (" << it->first << ',' << it->second <<")." <<endl;
			// Move to this knapsack
			time += (it->first + s - pos) % s;
			pos = it->first;
			
			// Pick it up
			time += t;
			pos = (pos + t) % s;
			if (it->second > 1) it->second--;
			else ks.erase(it);
			ks_left--;
//			cerr << ks_left << ' ' << ks.size()<< ' '<<time<<' '<<pos<<endl;
		}
//		cerr << "Done simulating " << j << " time " << time << endl;
		ts.push_back({k[j], time});
	}
	
	// Find the minimum
	ll mintime = 1e18 + 1, maxtime = 0;
	for (auto p : ts)
		mintime = min(mintime, p.second);
//	cerr << "Minimum: " << mintime << endl;
	
	// Finding the maximum
	ll sum = 0LL;
	for (int i = 0; i < ts.size(); ++i) {
		// Add this term
		ll time = ts[i].second;
		ll count = (ts[i].first - ts[(i - 1 + ts.size())%ts.size()].first + s) % s;
		if (count == 0) count += s;
		
		sum += (count * time + (count - 1) * count / 2);
//		cerr<<sum<<endl;
		
		maxtime = max(maxtime, time + count - 1);
	}
	
	ll a = sum, b = s;
	while (b) {
		a %= b;
		swap(a, b);
	}
	
	sum /= a;
	s /= a;
	
	cout << mintime << '\n' << maxtime << '\n' << sum << '/' << s << endl;
	
	return 0;
}
