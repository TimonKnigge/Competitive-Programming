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

int fee;

void dijkstra(vector<vector<pair<ll, int> > > &e, vector<ll> &d, int s) {
	priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > pq;
	d.assign(e.size(), LLINF);
	d[s] = 0;
	pq.push({d[s], s});
	while (!pq.empty()) {
		int u = pq.top().second;
		ll w = pq.top().first;
		pq.pop();
		if (d[u] != w) continue;
		for (pair<ll, int> wv : e[u]) {
			if (w + wv.first < d[wv.second]) {
				d[wv.second] = w + wv.first;
				pq.push({d[wv.second], wv.second});
			}
		}
	}
}

int main() {
	
	int N, M;
	scanf("%d %d", &N, &M);
	vector<vector<pair<ll, int> > > e(N, vector<pair<ll, int> > ());
	while (M--) {
		int x, u, v, w;
		scanf("%d %d %d %d", &x, &u, &v, &w);
		u--; v--;
		e[u].push_back({ll(w), v});
		if (x == 2)
			e[v].push_back({ll(w), u});
	}
	
	scanf("%d", &fee);
	int C;
	scanf("%d", &C);
	C--;
	
	int K;
	scanf("%d", &K);
	vector<int> dest(K + 1, C);
	for (int k = 1; k <= K; ++k) {
		scanf("%d", &dest[k]);
		dest[k]--;
	}
	
	// Find all pairwise distances
	vector<vector<ll> > dist(K + 1, vector<ll>(K + 1, 0LL));
	for (int i = 0; i <= K; ++i) {
		vector<ll> d;
		dijkstra(e, d, dest[i]);
		for (int j = 0; j <= K; ++j)
			dist[i][j] = d[dest[j]];
	}

//	cerr << "Finished dijkstra." << endl;
	
	vector<vector<ll> > cost(K, vector<ll>(1<<K, LLINF));
	vector<ll> fcost(1<<K, LLINF);
	fcost[0] = 0LL;
	for (int s = 0; s < K; ++s) {
		cost[s][1<<s] = fee + dist[0][s + 1];
		fcost[1<<s] = cost[s][1<<s];
		cost[s][0] = 0LL;
	}
	for (int s = 2; s <= 4; ++s) {
		int msk = (1<<s) - 1;
		while (!(msk&1<<K)) {
			ll mn = LLINF;
			for (int k = 0; k < K; ++k) {
				if ((msk&(1<<k)) == 0) continue;
				// We could attach it to another ride
				for (int l = 0; l < K; ++l) {
					if (l==k || ((1<<l)&msk) == 0)
						continue;
					ll nc = cost[l][msk&~(1<<k)]
						+ dist[l+1][k+1];
					if (nc < cost[k][msk])
						cost[k][msk] = nc;
				}
				if (mn > cost[k][msk])
					mn = cost[k][msk];
			}
			fcost[msk] = mn;
			
			int lo = msk&~(msk-1);
			int lz = (msk + lo) &~ msk;
			msk |= lz;
			msk &= ~(lz - 1);
			msk |= (lz /lo /2) - 1;
		}
	}
//	cerr << "Did 1-4's" << endl;
	
	for (int msk = 0; msk < (1<<K); ++msk) {
		if (__builtin_popcount(msk) == 1) continue;
		for (int s = 1; s <= min(4, __builtin_popcount(msk) - 1); ++s) {
			int msk2 = (1<<s) - 1;
			while (!(msk2&1<<K)) {
				
				ll nc = fcost[msk2] + fcost[msk&(~msk2)];
				if (nc < fcost[msk]) fcost[msk] = nc;
				
				int lo = msk2 &~(msk2 - 1);
				int lz = (msk2 + lo) & ~msk2;
				msk2 |= lz;
				msk2 &= ~(lz - 1);
				msk2 |= (lz / lo / 2) - 1;
			}
		}
	}
	
	cout << fcost[(1<<K) - 1] << endl;
	
	return 0;
}
