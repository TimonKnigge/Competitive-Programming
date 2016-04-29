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

void bfs(int s, vvi &E, vector<int> &d) { 
	d[s] = 0;
	queue<int> q;
	q.push(s);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int v : E[u])
			if (d[u] + 1 < d[v]) {
				d[v] = 1 + d[u];
				q.push(v);
			}
	}
}

int main() {
	
	int N, M;
	scanf("%d %d", &N, &M);
	
	vvi E(N, vi());
	while (M--) {
		int u, v;
		scanf("%d %d", &u, &v);
		--u; --v;
		E[u].push_back(v);
	}
	
	vector< vector<int> > dist(N, vector<int>(N, INF));
	for (int u = 0; u < N; ++u)
		bfs(u, E, dist[u]);
	
	constexpr int UP = 3;
	vi bestf[UP], bestfid[UP], bestt[UP], besttid[UP];
	for (int x = 0; x < UP; ++x) {
		bestf[x].assign(N, -1LL);
		bestt[x].assign(N, -1LL);
		bestfid[x].assign(N, -1LL);
		besttid[x].assign(N, -1LL);
	}
	
	for (int u = 0; u < N; ++u) {
		vii candf(N, {-1LL, 0LL});
		vii candt(N, {-1LL, 0LL});
		for (int i = 0; i < N; ++i) {
			candf[i].second = i;
			candt[i].second = i;
			if (i == u) continue;
			if (dist[i][u] < INF)
				candf[i].first = dist[i][u];
			if (dist[u][i] < INF)
				candt[i].first = dist[u][i];
		}
		
		sort(candf.rbegin(), candf.rend());
		sort(candt.rbegin(), candt.rend());
		for (int j = 0; j < UP; ++j) {
			if (candf[j].first != -1LL) {
				bestf[j][u] = candf[j].first;
				bestfid[j][u] = candf[j].second;
			}
			if (candt[j].first != -1LL) {
				bestt[j][u] = candt[j].first;
				besttid[j][u] = candt[j].second;
			}
		}
	}
	
	int ans[4] = {0, 0, 0, 0};
	ll opt = -1LL;
	for (int u = 0; u < N; ++u)
		for (int v = 0; v < N; ++v) {
			if (u == v) continue;
			if (dist[u][v] == INF) continue;
			for (int i = 0; i < UP; ++i) {
				if (bestfid[i][u] == v) continue;
				if (bestfid[i][u] == -1LL) continue;
				for (int j = 0; j < UP; ++j) {
					if (besttid[j][v] == u) continue;
					if (besttid[j][v] == bestfid[i][u]) continue;
					if (besttid[j][v] == -1LL) continue;
					if (opt < bestf[i][u] + dist[u][v] + bestt[j][v]) {
						opt = bestf[i][u] + dist[u][v] + bestt[j][v];
						ans[0] = bestfid[i][u];
						ans[1] = u;
						ans[2] = v;
						ans[3] = besttid[j][v];
					}
				}
			}
		}
	
	printf("%d %d %d %d\n", ans[0]+1, ans[1]+1, ans[2]+1, ans[3]+1);
	
	return 0;
}
