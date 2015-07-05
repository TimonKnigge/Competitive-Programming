#include<iostream>
#include<vector>
#include<queue>
#include<functional>
#include<algorithm>

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef vector<vii> vvii;

const int INF = 2000000000;

// Gives the sum of the lengths of the first x lines. Used for array indexing, see below
int lineSum(int x, vi lineLengths){
	int r = 0;
	for (int _x = 0; _x < x; _x++)
		r += lineLengths[_x];
	return r;
}

// For a (line, stop) pair, gives the index in the array.
int coordToIndex(int x, int y, vi lineLengths){
	return lineSum(x, lineLengths) + y;
}

// Uses dijkstra's to find the shortest path from c1 to c2. Returns -1 if no path exists.
int query(int c1, int c2, vvii edges){
	// Set all distances to infinity first, except the source (which is set to zero), and
	// add the source to the queue.
	int V = edges.size();
	vi dist(V);
	fill(dist.begin(), dist.end(), INF);
	dist[c1] = 0;
	priority_queue<ii, vii, greater<ii>> pq;
	pq.push(ii(dist[c1], c1));

	// Push the frontier over the graph.
	while (!pq.empty()){
		ii top = pq.top(); pq.pop();
		int d = top.first, u = top.second;

		// Spread to other vertices
		if (d == dist[u]){
			int sz = edges[u].size();
			for (int i = 0; i < sz; i++){
				int v = edges[u][i].second, weight_u_v = edges[u][i].first;
				// Only spread if this new route is faster.
				if (dist[u] + weight_u_v < dist[v]){
					dist[v] = dist[u] + weight_u_v;
					pq.push(ii(dist[v], v));
				}
			}
		}
	}

	// return the found distance
	if (dist[c2] < INF)
		return dist[c2];
	return -1;
}

int main(){
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++){
		int N, M, Q;
		cin >> N;

		vvii edges;
		vi lineLengths(N);
		
		// Read in all metro lines
		for (int i = 0; i < N; i++){
			int SN, W;
			cin >> SN >> W;

			for (int j = 0; j < SN*2; j++)
				edges.push_back(vii());

			lineLengths[i] = SN;

			int ls = lineSum(i, lineLengths);
			for (int j = 0; j < SN - 1; j++){
				int time;
				cin >> time;
				// Connect this stop to the next.
				edges[(ls + j)*2    ].push_back(ii(time, (ls + j + 1)*2));
				edges[(ls + j + 1)*2].push_back(ii(time, (ls + j    )*2));

				// Add a connection between the 'waiting for train' vertex of (i, j)
				// and the 'train has arrived' vertex of (i, j) (notice the different weights).
				edges[(ls + j) * 2].push_back(ii(0, (ls + j) * 2 + 1));
				edges[(ls + j) * 2 + 1].push_back(ii(W, (ls + j) * 2));
			}
			// See right above, now for last edge.
			int l = lineSum(i + 1, lineLengths) - 1;
			edges[l * 2].push_back(ii(0, l * 2 + 1));
			edges[l * 2 + 1].push_back(ii(W, l * 2));
		}

		// Read in all tunnels
		cin >> M;
		for (int i = 0; i < M; i++){
			int m1, s1, m2, s2, t;
			cin >> m1 >> s1 >> m2 >> s2 >> t;
			m1 -= 1; s1 -= 1; m2 -= 1; s2 -= 1;

			int c1 = coordToIndex(m1, s1, lineLengths),
				c2 = coordToIndex(m2, s2, lineLengths);

			// Connect the 'waiting for train' vertices of both stops.
			edges[c1 * 2 + 1].push_back(ii(t, c2 * 2 + 1));
			edges[c2 * 2 + 1].push_back(ii(t, c1 * 2 + 1));
		}

		cout << "Case #" << t << ":" << endl;

		// Q queries
		cin >> Q;
		for (int i = 0; i < Q; i++){
			int x1, y1, x2, y2;
			cin >> x1 >> y1 >> x2 >> y2;

			// Convert to indices and query.
			int c1 = coordToIndex(x1 - 1, y1 - 1, lineLengths),
				c2 = coordToIndex(x2 - 1, y2 - 1, lineLengths);

			cout << query(c1*2+1, c2*2 + 1, edges) << endl;
		}
	}

	return 0;
}
