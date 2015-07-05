#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {

	int n;
	cin >> n;

	// Read the *inverse* of the permutation, i.e. p[i] contains
	// the position of i in the permutation
	vector<int> p(n);
	for (int i = 0; i < n; ++i) {
		int val;
		cin >> val;
		p[val - 1] = i; // -1 to account for 0-based representation
	}

	// Read adjancency matrix
	vector< vector<bool> > adjMatrix(n, vector<bool>(n, false));
	for (int h = 0; h < n; ++h) {
		for (int w = 0; w < n; ++w) {
			char symb;
			cin >> symb;
			adjMatrix[w][h] = (symb == '1') || (w == h);
			adjMatrix[h][w] = (symb == '1') || (w == h);
		}
	}

	// Floyd Warshall (sort of, distances are not relevant)
	for (int b = 0; b < n; ++b)
		for (int a = 0; a < n; ++a)
			for (int c = 0; c < n; ++c)
				if (adjMatrix[a][b] && adjMatrix[b][c])
					adjMatrix[a][c] = true;
	

	// Greedily put each value as close to the front as possible,
	// prioritizing low values.
	vector<int> fp(n, -1);
	for (int i = 0; i < n; ++i) {
		// Number i is at p[i], move it to the first available spot:
		for (int pos = 0; pos < n; ++pos) {
			if (adjMatrix[p[i]][pos] && fp[pos] == -1) {
				fp[pos] = i + 1; // +1 to account for 0-based representation
				break;
			}
		}
	}

	// Do output
	cout << fp[0];
	for (int i = 1; i < n; ++i) {
		cout << ' ' << fp[i];
	}
	cout << endl;
	
	return 0;
}