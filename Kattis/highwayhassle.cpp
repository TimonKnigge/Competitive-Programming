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
#include <cstdio>

using namespace std;
using ll = long long;
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000LL;

int main() {
	int TC;
	scanf("%d", &TC);
	while (TC--) {
		int N, M, S;
		scanf("%d %d %d", &N, &M, &S);
		int T;
		scanf("%d", &T);
		
		vector<vector<pair<int, ll> > > e(N, vector<pair<int, ll> >());
		for (int i = 0; i < M; ++i) {
			int A, B, F;
			scanf("%d %d %d", &A, &B, &F);
			A--; B--;
			e[A].push_back({B, F});
			e[B].push_back({A, F});
		}
		
		vi petrolN(N, -1);
		for (int i = 0; i < S; ++i) {
			int X, P;
			scanf("%d %d", &X, &P);
			X--;
			petrolN[X] = P;
		}
		
		int C, D;
		scanf("%d %d", &C, &D);
		C--; D--;
		if (petrolN[D] == -1) {
			petrolN[D] = 100000;
			S++;
		}
		
		// Compute pairwise distances
		vector<vector<ll> > dist(S, vector<ll>(S, LLINF));
		int MS = 0;
		for (int s = 0; s < N; ++s) {
			if (petrolN[s] == -1) continue;
			priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > pq;
			vector<ll> dt(N, LLINF);
			dt[s] = 0;
			pq.push({0, s});
			while (!pq.empty()) {
				int u = pq.top().second;
				ll du = pq.top().first;
				pq.pop();
				if (du != dt[u]) continue;
				for (auto vdv : e[u]) {
					int v = vdv.first;
					ll dv = vdv.second;
					if (du + dv < dt[v]) {
						dt[v] = du + dv;
						pq.push({dt[v], v});
					}
				}
			}
			for (int i = 0, NS = 0; i < N; ++i) {
				if (petrolN[i] == -1) continue;
				dist[MS][NS] = dt[i];
//				cerr << "dist[" << MS << "]["<<NS<<"] = " <<dt[i]<<endl;
				NS++;
			}
			MS++;
		}
		
		// Now we know all pairwise distances, compress the petrol vector;
		// Also reassign C, D.
		vector<ll> petrol;
		for (int i = 0; i < N; ++i) {
			if (i == C) C = petrol.size();
			if (i == D) D = petrol.size();
			if (petrolN[i] != -1)
				petrol.push_back(petrolN[i]);
		}
//		cerr<<"Petrols (" << S << ") ";
//		for (int i = 0; i < petrol.size(); ++i)
//			cerr << petrol[i] << " ";
//		cerr<<endl;
//		cerr << "Dijkstra from " << C << " to " << D << endl;
		
		// Dijkstra time II
		// (vertex, fuel left) -> cost
		map<pair<int, ll>, ll> cost;
		cost[make_pair(C, 0)] = 0;
		priority_queue<pair<ll, pair<int, ll> >,
			vector<pair<ll, pair<int, ll> > >,
			greater<pair<ll, pair<int, ll> > > > pq;
		pq.push(make_pair(0LL, make_pair(C, 0LL)));
		while (!pq.empty()) {
			ll ucost = pq.top().first, fleft = pq.top().second.second;
			int u = pq.top().second.first;
			pq.pop();
			
//			cerr << u << ' ' << fleft << endl;
			
			if (cost[make_pair(u, fleft)] != ucost) continue;
			for (int v = 0; v < S; ++v) {
//				cerr << "Considering "<< u << " -> "<<v<<endl;
				if (v == u) continue;
				// Reachable cost
				// Get as far as possible with fleft
				ll tankcap = fleft, edist = dist[u][v],
					efuel = fleft, ecost = ucost;
				
				if (efuel > edist) {
					efuel -= edist;
					edist  = 0;
				} else {
					edist -= efuel;
					efuel = 0;
				}
				
				// Pay the rest here
				if (edist > 0) {
					tankcap += edist;
					ecost += edist * petrol[u];
					edist = 0;
				}
				
				// Impossible? continue
				if (tankcap > T) continue;
				auto pr = make_pair(v, 0);
				auto it = cost.find(pr);
				if (it == cost.end() || it->second > ecost) {
					if (it == cost.end())
						cost[pr] = ecost;
					else it->second = ecost;
					pq.push(make_pair(ecost, pr));
				}
				
				// Fuel up the rest
				if (tankcap == T) continue;
				ecost += (T - tankcap) * petrol[u];
				efuel += (T - tankcap);
				pr = make_pair(v, efuel);
				it = cost.find(pr);
				if (it == cost.end() || it->second > ecost) {
					if (it == cost.end())
						cost[pr] = ecost;
					else it->second = ecost;
					pq.push(make_pair(ecost, pr));
				}
			}
		}
		
		printf("%lld\n", cost[make_pair(D, 0LL)]);
	}
	
	return 0;
}
