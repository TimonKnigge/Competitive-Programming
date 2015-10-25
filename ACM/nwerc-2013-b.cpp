#include<iostream>
#include<vector>
#include<bitset>
#include<algorithm>
//#define DEBUG

using namespace std;

/*
	This problem can be solved by observing that since the graph is planar,
	all chain groups have a size of at most 4. Since we have at least 2 ships,
	and the graph is connected, the size is at least 2.

	Checking all possible combinations is thus O(V^4), but only because the graph is
	planar (the problem is probably in NP for general graphs?). The algorithm below
	is O(V + E^3), though in practice much faster. It works by incrementally building
	all chain groups of sizes 3 and 4 (chain groups of size 2 are given and checked during
	input stage).
*/

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<ii, int> iii;

vector<bitset<450>> adjMatrix(450);
int unionGroup[2], disjunctGroup[2];

#ifdef DEBUG
void printAdjMatrix(int dim){
	for (int i = 0; i < dim; i++){
		for (int j = 0; j < dim; j++)
			cout << (adjMatrix[i].test(j) ? '1' : '0');
		cout << endl;
	}
}
#endif

// Checks if the union of a given pair of chain groups of size 3
// forms a chain group of size 4.
bool match(iii p1, iii p2){

	disjunctGroup[0] = p1.first.first + p1.first.second + p1.second;
	disjunctGroup[1] = p2.first.first + p2.first.second + p2.second;
	int indx = 0;

	// Find intersection and disjunct parts
	for (int i : {p1.first.first, p1.first.second, p1.second}){
		for (int j : {p2.first.first, p2.first.second, p2.second}){
			if (i == j){
				if (indx < 2)
					unionGroup[indx] = i;
				indx++;
				disjunctGroup[0] -= i;
				disjunctGroup[1] -= i;
			}
		}
	}

	// If the union is size 2 and the disjunct parts are connected, we have
	// a chain group of size 4.
	return ((indx == 2) && (adjMatrix[disjunctGroup[0]].test(disjunctGroup[1])));
}

int main(){

	int T;
	cin >> T;
	while (T-- > 0){

		// Reuse adjacency matrix to prevent time delays because of memory
		// allocation (450*450 max size is small enough).
		for (int i = 0; i < 450; i++){
			adjMatrix[i].reset();			
		}

		int V, E, maxCoins = -1;
		cin >> V >> E;

		vector<int> coins(V);
		vvi edges(V);

		for (int i = 0; i < V; i++){
			cin >> coins[i];
		}

		// Read in edges, store both in adjacency list and adjacency matrix.
		for (int i = 0; i < E; i++){
			int l, r;
			cin >> l >> r;
			edges[l - 1].push_back(r - 1);
			edges[r - 1].push_back(l - 1);

			adjMatrix[l - 1].set(r - 1, true);
			adjMatrix[r - 1].set(l - 1, true);

			// The highest rated chain group might be of size 2.
			if (maxCoins < coins[l - 1] + coins[r - 1]){
				maxCoins = coins[l - 1] + coins[r - 1];
			}
		}
		
		vector<iii> threeGroups;

		// Find all chain groups of size 3, by iterating over all pairs of edges
		// that start from the same vertex, and checking if their ends are connected.
		for (int i = 0; i < V; i++){
			int sz = edges[i].size();
			for (int j = 0; j < sz; j++){
				if (edges[i][j] < i) continue; // avoid duplicates

				for (int k = j + 1; k < sz; k++){
					if (adjMatrix[(edges[i][j])].test(edges[i][k])){
						
						// Sort in advance, will make matching easier & faster.
						int i1 = i, i2 = edges[i][j], i3 = edges[i][k];
						int t1 = min(min(i1, i2), i3), t2 = max(max(i1, i2), i3);
						i2 = i1 + i2 + i3 - t1 - t2; i1 = t1; i3 = t2;

						// Add to the list and update the max coin sum if necessary.
						threeGroups.push_back(iii(ii(i1, i2), i3));
						int s = coins[i1] + coins[i2] + coins[i3];
						if (maxCoins < s)
							maxCoins = s;
					}
				}
			}
		}

		// Try to combine all chain groups of size 3.
		int sz = threeGroups.size();
		for (int i = 0; i < sz; i++){
			for (int j = i + 1; j < sz; j++){
				iii g1 = threeGroups[i], g2 = threeGroups[j];

				// See the match function for more info.
				if (match(g1, g2)){
					int s = coins[unionGroup[0]]
						+ coins[unionGroup[1]]
						+ coins[disjunctGroup[0]]
						+ coins[disjunctGroup[1]];
					if (maxCoins < s)
						maxCoins = s;

#ifdef DEBUG
					cout << "New quad found: " << endl;
					cout << "Union: " << unionGroup[0] << ", " << unionGroup[1] << endl;
					cout << "Disj.: " << disjunctGroup[0] << ", " << disjunctGroup[1] << endl;
#endif
				}
			}
		}

		cout << maxCoins << endl;
	}

	return 0;
}
