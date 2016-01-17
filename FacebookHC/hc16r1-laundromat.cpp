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
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

int main() {
	
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; ++t) {
		int L, N; 
		ll M, D;
		// L loads
		// N washing machines
		// M dryers
		// D minutes drying time
		cin >> L >> N >> M >> D;
		
		vector<ll> W(N, 0LL);
		for (int i = 0; i < N; ++i) {
			cin >> W[i];
		}
		
		priority_queue<
			pair<ll, ll>, 
			vector<pair<ll, ll> >, 
			greater<pair<ll, ll> > 
				> pq;
		for (int i = 0; i < N; ++i) pq.push({W[i], W[i]});
		
		vector<ll> exit_times;
		for (int l = 1; l <= L; ++l) {
			// Pick the machine which promises to wash
			// the load at the earliest time.
			pair<ll, ll> nxt = pq.top(); pq.pop();
			exit_times.push_back(nxt.first);
			
			// Enqueue the next promise
			pq.push({nxt.first + nxt.second, nxt.second});
		}
		
		// Dry all loads
		priority_queue<ll, vector<ll>, greater<ll> > pq2;
		for (int i = 0; i < min(L, int(M)); ++i)
			pq2.push(0);
		
		ll ans = 0LL;
		for (int i = 0; i < L; ++i) {
			ll nxt = pq2.top(); pq2.pop();
			ll tm = max(nxt, exit_times[i]) + D;
			ans = max(ans, tm);
			pq2.push(tm);
		}
		
		cout << "Case #" << t << ": " << ans << '\n';
	}
	
	return 0;
}
