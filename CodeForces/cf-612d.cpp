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
	
	int n, k;
	scanf("%d %d", &n, &k);
	
	vii seg(n, {0, 0});
	for (int i = 0; i < n; ++i)
		scanf("%d %d", &seg[i].first, &seg[i].second);
	
	sort(seg.begin(), seg.end());
	vii ans;
	
	priority_queue<int, vi, greater<int> > pq;
	int since = -INF;
	for (int i = 0; i < int(seg.size()); ++i) {
		// Erase until seg[i] enters
		while (!pq.empty() && pq.top() < seg[i].first) {
			if (pq.size() == k)
				ans.push_back({since, pq.top()});
			pq.pop();
		}
		
		pq.push(seg[i].second);
		if (pq.size() == k)
			since = seg[i].first;
	}
	while (!pq.empty()) {
		if (pq.size() == k)
			ans.push_back({since, pq.top()});
		pq.pop();
	}
	
	cout << ans.size() << endl;
	sort(ans.begin(), ans.end());
	for (int i = 0; i < ans.size(); ++i)
		cout << ans[i].first << ' ' << ans[i].second << '\n';
	cout << flush;
	
	return 0;
}
