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

void dijkstra(vvii &E, vi &dist, int s) {
	int N = E.size();
	dist.assign(N, LLINF);
	priority_queue<ii, vector<ii>, greater<ii>> pq;
	dist[s] = 0LL;
	pq.push({0LL, s});
	
	while (!pq.empty()) {
		ll d = pq.top().first;
		int u = pq.top().second;
		pq.pop();
		
		if (d != dist[u]) continue;
		for (ii vw : E[u]) {
			int v = vw.first;
			ll w = vw.second;
			if (dist[v] > w + d) {
				dist[v] = w + d;
				pq.push({dist[v], v});
			}
		}
	}
}
	
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N, M;
	cin >> N >> M;
	
	vvii E(N, vii());
	vvii RE(N, vii());
	while (M--) {
		int u, v;
		ll w;
		cin >> u >> v >> w;
		E[u].push_back({v, w});
		RE[v].push_back({u, w});
	}
	
	int s, t;
	cin >> s >> t;
	
	vi dist, rdist;
	dijkstra(E, dist, s);
	dijkstra(RE, rdist, t);
	
	vi ans;
	priority_queue<ii, vector<ii>, greater<ii>> pq;
	vb pushed(N, false);
	pushed[s] = true;
	pq.push({0LL, s});
	
	while (!pq.empty()) {
		int u = pq.top().second;
		pq.pop();
		
		if (pq.empty()) ans.push_back(u);
		for (ii vw : E[u]) {
			int v = vw.first;
			ll w = vw.second;
			if (pushed[v]) continue;
			if (dist[t] == dist[u] + w + rdist[v]) {
				pq.push({dist[v], v});
				pushed[v] = true;
			}
		}
	}
	
	sort(ans.begin(), ans.end());
	for (int i : ans)
		cout << i << ' ';
	cout << endl;
	
	return 0;
}
