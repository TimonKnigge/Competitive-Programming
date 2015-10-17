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
	int N;
	scanf("%d", &N);
	
	vii v(N, {0, 0});
	for (int i = 0; i < N; ++i)
		scanf("%d %d", &v[i].first, &v[i].second);
	
	sort(v.begin(), v.end());
	
	int l = 0, r = 10000;
	vi time(N, 0);
	while (l < r) {
		int t = (l + r) / 2;
		
		bool pos = true;
		for (int i = 0; i < N; ++i) time[i] = 0;
		priority_queue<ii, vii, greater<ii> > pq;
		
		int T = 0, nT, dT;
		for (int i = 0; pos && i < v.size(); ++i) {
			nT = v[i].first;
			dT = nT - T;
			
			// Empty the queue upto time T
			while (!pq.empty() && dT > 0) {
				int left = pq.top().first - T, id = pq.top().second;
				int needed = t - time[id];
				int use = max(0, min(needed, min(left, dT)));
				
				time[id] += use;
				T += use;
				dT -= use;
				if (time[id] == t) pq.pop();
				else if (pq.top().first == T) {
					pos = false;
					break;
				}
			}
			T = nT;
			pq.push({v[i].second, i});
		}
		
		while (!pq.empty()) {
			int left = pq.top().first - T, id = pq.top().second;
			int needed = t - time[id];
			int use = max(0, min(needed, left));
			time[id] += use;
			T += use;
			if (time[id] == t) pq.pop();
			else {
				pos = false;
				break;
			}
		}
		
		if (pos) l = t + 1;
		else r = t;
	}
	
	printf("%d\n", (l - 1) * N);
	
	return 0;
}
