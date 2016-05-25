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

void dijkstra(vvii &E, vi &dist) {
	
	priority_queue<ii, vector<ii>, greater<ii>> pq;
	for (size_t i = 0; i < E.size(); ++i)
		if (dist[i] < LLINF)
			pq.push({dist[i], i});
	
	while (!pq.empty()) {
		int u = pq.top().second;
		ll d = pq.top().first;
		pq.pop();
		
		if (d != dist[u]) continue;
		for (ii vw : E[u]) {
			int v = vw.first;
			ll w = vw.second;
			if (dist[v] > d + w) {
				dist[v] = d + w;
				pq.push({dist[v], v});
			}
		}
	}
}

int main() {
	
	int N, M, K;
	scanf("%d %d %d", &N, &M, &K);
	
	vi av(N, 0LL);
	for (int i = 0, t, v; i < N; ++i) {
		scanf("%d", &t);
		while (t--)
			scanf("%d", &v),
			av[i] = (av[i] | (1LL << (v-1)));
	}
	
	vvii E(N, vii());
	while (M--) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		--u; --v;
		E[u].push_back({v, w});
		E[v].push_back({u, w});
	}
	
	vvi dist(1<<K, vi(N, LLINF));
	dist[0][0] = 0LL;
	for (int m = 0; m < (1<<K); ++m) {
		dijkstra(E, dist[m]);
		for (int i = 0; i < N; ++i)
			dist[m | av[i]][i] = min(dist[m | av[i]][i], dist[m][i]);
	}
	
	for (int m = (1<<K) - 1; m >= 0; --m)
		for (int j = 0; j < K; ++j)
			if (((m>>j)&1) == 0) continue;
			else for (int i = 0, nm = (m&~(1<<j)); i < N; ++i)
				dist[nm][i] = min(dist[nm][i], dist[m][i]);
	
	ll ans = LLINF;
	for (int m = 0; m < (1<<K); ++m)
		ans = min(ans, max(dist[m][N - 1], dist[((1<<K)-1)&~m][N - 1]));
	
	cout << ans << endl;
	
	return 0;
}
