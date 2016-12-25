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

using ldl = pair<ld, ll>;
using lld = pair<ll, ld>;
void dijkstra(vector<vector<lld>> &E, int s, vector<ld> &d) {
	vb vis(E.size(), false);
	d.assign(E.size(), -1.0);
	priority_queue<ldl, vector<ldl>> pq;
	d[s] = 1.0;
	pq.push({1.0, s});
	while (!pq.empty()) {
		ld ud = pq.top().first;
		ll u = pq.top().second;
		vis[u] = true;
		pq.pop();
		if (ud < d[u]) continue;
		for (lld e : E[u]) {
			ll v = e.first;
			ld w = e.second;
			if (vis[v]) continue;
			if (d[v] < -0.5
				|| (w < -0.5 && ud > d[v])
				|| (w > -0.5 && ud * w > d[v]/* + 1e-20*/)) {
				d[v] = (w < -0.5 ? ud : ud * w);
//				if (d[v] < 1e-30) d[v] = 0;
//				if (d[v] > 1) d[v] = 1;
				pq.push({d[v], v});
			}
		}
	}
}

int bfs(vvi &G, int s, int t) {
	vi d(G.size(), -1LL);
	queue<ll> q;
	q.push(s);
	d[s] = 0LL;
	while (!q.empty()) {
		ll u = q.front();
		q.pop();
		for (ll v : G[u]) {
			if (d[v] >= 0LL) continue;
			d[v] = d[u] + 1LL;
			q.push(v);
		}
	}
	return d[t];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N, M;
	cin >> N >> M;
	if (N == 1) {
		cout << 1 << endl;
		return 0;
	}
	
	vector<pair<ii, ld>> inp;
	vvi G(N, vi());
	while (M--) {
		int a, b;
		ld pr;
		cin >> a >> b >> pr;
		inp.push_back({{a, b}, pr});
		G[a].push_back(b);
		G[b].push_back(a);
	}
	int K = bfs(G, 0, N - 1);
	if (K == -1) {
		for (int i = 0; i < N; ++i)
			cout << "-1" << " \n"[i + 1 == N];
		return 0;
	}

	vector<vector<lld>> E(K*N, vector<pair<ll, ld>>());
	for (int k = 0; k + 1 < K; ++k)
		for (int i = 0; i < N; ++i)
			E[k*N+i].push_back({i+(k+1)*N, -1.0});
	for (auto &p : inp) {
		int a, b;
		ld pr;
		a = p.first.first;
		b = p.first.second;
		pr = p.second;
		if (a > b) swap(a, b);
		for (int k = 0; k < K; ++k) {
			E[a+k*N].push_back({b+k*N, min(ld(1.0),max(ld(0.0),1-pr))});
			if (k+1 < K){
				E[a+k* N].push_back( {b+k* N + N,-1.0} );
				E[b+k* N].push_back( {a+k* N + N,-1.0});
			}
		}
	}
	
	vector<ld> d;
	dijkstra(E, 0LL, d);
	
	ld best = 0.0;
	for (int k = 0; k < N; ++k) {
		if (k < K) {
			if (d[k*N+N-1] < -0.5)
				printf("-1");
			else {
				if (d[k*N+N-1] > best)
					best = d[k*N+N-1];
				printf("%.20Lf", best);//double(best));
			}
			printf(k + 1 < N ? " " : "\n");
		} else {
			printf("1");
			printf(k + 1 < N ? " " : "\n");
		}
	}
	
	return 0;
}
