#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef long long ll;
typedef vector<pair<int, long long> > el;
typedef vector<el> ell;
typedef pair<long long, int> PQ;

const ll LLINF = 2e18;

void dijkstra(ell &e, vector<ll> &d, int s) {
	int V = e.size();
	d.assign(V, LLINF);
	priority_queue<PQ, vector<PQ>, greater<PQ> > pq;
	pq.push({0, s});
	d[s] = 0;
	while (!pq.empty()) {
		int u = pq.top().second;
		ll w = pq.top().first;
		pq.pop();
		if (w > d[u]) continue;
		for (pair<int, long long> it : e[u]) {
			int v = it.first;
			ll wv = it.second;
			if (d[v] > w + wv) {
				d[v] = w + wv;
				pq.push({w + wv, v});
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N, P, M, G, T;
	cin >> N >> P >> M >> G >> T;
	
	vector<int> pvisit(P, -1);
	for (int i = 0; i < P; ++i) {
		int _t;
		cin >> pvisit[i] >> _t;
		G -= _t;
	}
	
	ell e(N, el());
	for (int i = 0; i < M; ++i) {
		int s, dd; ll t;
		cin >> s >> dd >> t;
		e[s].push_back({dd, t});
		e[dd].push_back({s, t});
	}


	vector<vector<long long> > d(P, vector<long long>(P, LLINF));
	for (int i = 0; i < P; ++i) {
		int s = pvisit[i];
		vector<long long> dist;
		dijkstra(e, dist, s);
		for (int j = 0; j < P; ++j) {
			d[i][j] = dist[pvisit[j]];
			
			if (dist[pvisit[j]] == LLINF) {
				cout << "impossible" << endl;
				return 0;
			}
		}
	}


	int taxibit = (1 << P);
	// tsp_d[eindpunt][bezochteplekken | taxibit]
	vector<vector<long long> > tsp_d(P, vector<long long>(1 << (P + 1), LLINF));
	tsp_d[0][1] = 0;
	
	for (int mask = 0; mask < (1 << (P + 1)); ++mask) {
		for (int s = 0; s < P; ++s) {
			if ((mask & (1 << s)) == 0) continue;
			if (tsp_d[s][mask] == LLINF) continue;
			for (int t = 0; t < P; ++t) {
				if (s == t) continue;
				if ((mask & (1 << t)) != 0) continue;
				
				if (((mask & taxibit) != taxibit)) {
					ll newt = tsp_d[s][mask] + T;
					if (newt < tsp_d[t][mask | (1 << t) | taxibit])
						tsp_d[t][mask | (1 << t) | taxibit]
							= newt;
				}
				if (d[s][t] < LLINF) {
					ll mewt = tsp_d[s][mask] + d[s][t];
					if (mewt < tsp_d[t][mask | (1 << t)])
						tsp_d[t][mask | (1 << t)]
							= mewt;
				}
			}
		}
	}
	
	int mask = (1 << P) - 1;
	int mask2 = (1 << (P + 1)) - 1;
	ll minz = LLINF;
	ll minm = LLINF;
	for (int v = 1; v < P; ++v) {
		if (tsp_d[v][mask] != LLINF) {
			if (d[v][0] != LLINF)
				minz = min(minz, tsp_d[v][mask] + d[v][0]);
			minm = min(minm, tsp_d[v][mask] + T);
		}
		if (tsp_d[v][mask2] != LLINF && d[v][0] != LLINF)
			minm = min(minm, tsp_d[v][mask2] + d[v][0]);
	}

	bool pz = false, pm = false;
	if (P == 1 && G >= 0) pz = true;
	if (minz <= G) pz = true;
	if (minm <= G) pm = true;

	if (pz) cout << "possible without taxi" << endl;
	else if (pm) cout << "possible with taxi" << endl;
	else cout << "impossible" << endl;
	
	return 0;
}
