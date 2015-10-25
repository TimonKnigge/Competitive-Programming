#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include <functional>

using namespace std;

typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef vector<vii> vvii;

// Unionfind
vii pset;
int psets;

void initSet(int N){
	pset.resize(N);
	for (int i = 0; i < N; ++i) pset[i] = { i, 1 };
	psets = N;
}

int findSet(int i){
	return (pset[i].first == i) ? i : pset[i].first = findSet(pset[i].first);
}

void unionSet(int i, int j){
	int x = findSet(i), y = findSet(j);
	if (x != y){
		pset[x].first = y;
		psets--;
		pset[y].second += pset[x].first;
	}
}

bool isSameSet(int i, int j){
	return findSet(i) == findSet(j);
}
// -Unionfind

// Kruskal
viii kruskal(viii edges){

	viii result;
	
	size_t V = edges.size();

	initSet(V);

	for (int i = 0; i < V; i++){
		iii f = edges[i];

		if (!isSameSet(f.second.first, f.second.second)){
			unionSet(f.second.first, f.second.second);
			result.push_back(f);
		}
	}

	return result;
}
// -Kruskal

// Dijkstra
const int INF = 2000000000;
int dijkstra(vvii edges, int s, int t){ // Returns the shortest distance between s and t.

	int V = edges.size();
	vector<int> dist(V, INF);

	dist[s] = 0;
	priority_queue<ii, vii, greater<ii>> pq;
	pq.push(ii(0, s));

	while (!pq.empty()){

		ii top = pq.top(); pq.pop();
		int d = top.first, u = top.second;

		if (d == dist[u]){

			if (u == t)
				return d;
			
			for (auto it = edges[u].begin(); it != edges[u].end(); it++){
				int v = it->first, weighted_u_v = it->second;
				if (dist[u] + weighted_u_v < dist[v]){
					dist[v] = dist[u] + weighted_u_v;
					pq.push(ii(dist[v], v));
				}
			}
		}
	}

	return INF;
}
// -Dijkstra

bool edgeCompare(iii l, iii r){
	return l.first < r.first;
}

void printRoad(int a, int b, int c){
	cout << (a + 1) << " " << (b + 1) << " " << c << endl;
}

int main(){
	
	int cases;
	cin >> cases;

	while (cases-- > 0){

		int N;
		cin >> N;

		viii edges;

		// Add all edges to the graph
		int cost;
		for (int i = 0; i < N; i++){
			for (int j = 0; j < N; j++){
				cin >> cost;
				if (i < j){
					edges.push_back(iii(cost, ii(i, j)));
				}
			}
		}

		// Sort by weight (lowest first)
		sort(edges.begin(), edges.end(), edgeCompare);
		viii mst = kruskal(edges); // find MST

		// Reconstruct the MST as a graph that we can perform dijkstra's on.
		vvii dEdges(N);
		for (int i = 0; i < N - 1; i++){
			dEdges[mst[i].second.first].push_back(ii(mst[i].second.second, mst[i].first));
			dEdges[mst[i].second.second].push_back(ii(mst[i].second.first, mst[i].first));
		}

		// Check all edges
		int sz = edges.size();
		iii toAdd = edges[sz - 1]; // It might happen that all shortest paths are in the MST, in that case we pick a random edge.
		for (int i = 0; i < sz; i++){
			// Find the shortest edges not in the MST.
			if (edges[i].first < dijkstra(dEdges, edges[i].second.first, edges[i].second.second)){
				toAdd = edges[i];
				break;
			}
		}

		// output
		printRoad(toAdd.second.first, toAdd.second.second, toAdd.first);
		sz = mst.size();
		for (int i = 0; i < sz; i++){
			printRoad(mst[i].second.first, mst[i].second.second, mst[i].first);
		}
	}

	return 0;
}
