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
	
	int N, M;
	scanf("%d %d", &N, &M);
	
	vi Pi(N, 0LL);
	for (int i = 0, v; i < N; ++i) {
		scanf("%d", &v);
		Pi[v - 1] = i;
	}
	
	vvi open(N, vi());
	while (M--) {
		int a, b;
		scanf("%d %d", &a, &b);
		--a;
		--b;
		if (Pi[a] > Pi[b]) swap(a, b);
		open[Pi[a]].push_back(Pi[b]);
	}
	
	ll ans = 0LL;
	priority_queue<ll, vi, greater<ll> > pq, rm;
	for (int l = 0, r = -1; l < N; ++l) {
		
		while (!rm.empty() && rm.top() == pq.top()) {
			rm.pop();
			pq.pop();
		}
		
		while (r + 1 < N && (pq.empty() || pq.top() > r + 1)) {
			++r;
			for (ll o : open[r])
				pq.push(o);
		}
		
		ans += ll(r - l + 1);
		for (ll o : open[l])
			rm.push(o);
	}
	
	cout << ans << endl;
	
	return 0;
}
