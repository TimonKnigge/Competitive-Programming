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
	
	freopen("cardgame.in", "r", stdin);
	freopen("cardgame.out", "w", stdout);
	
	int N;
	scanf("%d", &N);
	
	vi elsie;
	vb has(N+N, true);
	for (int i = 0; i < N; ++i) {
		int v;
		scanf("%d", &v);
		has[v-1]=false;
		elsie.push_back(v-1);
	}
	
	vi bessy;
	for (int i = 0; i < N+N; ++i)
		if (has[i]) bessy.push_back(i);
	
	sort(bessy.begin(), bessy.end());
	set<pair<int, int> > leftover;
	
	// Find an initial matching
	vi bessymatch(N, -1), elsiematch(N, -1);
	vii selsie;
	for (int i = 0; i < N; ++i)
		selsie.push_back({elsie[i], i});
	sort(selsie.begin(), selsie.end());
	int j = 0, ans = 0;

	for (int i = 0; i < N; ++i) {
		while (j < N && bessy[j] < selsie[i].first) {
			leftover.insert({bessy[j], j});
			j++;
		}
		if (j < N) {
			int m = selsie[i].second;
			bessymatch[j] = m;
			elsiematch[m] = j;
			ans++;
			j++;
		}
	}
	
	while(j<N) { leftover.insert({bessy[j], j}); j++; }
	
	int best = ans;
	for (int s = N - 1; s >= 0; --s) {
		// Transfer s to the smaller side
		if (elsiematch[s] > -1) {
			int m = elsiematch[s];
			bessymatch[m] = -1;
			leftover.insert({bessy[m], m});
			elsiematch[s] = -1;
			ans--;
		}
		
		auto it = leftover.lower_bound({elsie[s], 0});
		if (it == leftover.begin()) { // no smaller elements available
			// Find a smaller element in bessy
			int l = 0, r = N - 1;
			while (l < r) {
				int mid = (l+r) / 2;
				if (bessy[mid] < elsie[s]) l = mid + 1;
				else r = mid;
			}
			while (l >= 0 && bessy[l] > elsie[s]) --l;
			if (l >= 0) {
				int own = bessymatch[l];
				// Steal from own!
				elsiematch[own] = -1;
				elsiematch[s] = l;
				bessymatch[l] = s;
				
				// Can we find a match for own?
				it = leftover.lower_bound({elsie[own], 0});
				if ((own < s && it != leftover.end())
					|| (own>s && it != leftover.begin())){
					if (own>s) it--;
					elsiematch[own] = it->second;
					bessymatch[it->second] = own;
					leftover.erase(it);
					ans++;
				}
			}
		} else {
			// Just use leftover!
			it--;
			elsiematch[s] = it->second;
			bessymatch[it->second] = s;
			leftover.erase(it);
			ans++;
		}
		best = max(ans, best);
	}
	
	cout << best << endl;
	
	return 0;
}
