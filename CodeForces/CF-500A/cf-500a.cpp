#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {

	int n, t;
	cin >> n >> t;
	t--;

	vector< vector<int> > edges(n);
	for (int i = 0; i < n - 1; ++i) {
		int ai;
		cin >> ai;
		edges[i].push_back(i + ai);
	}

	queue<int> frontier;
	vector<bool> marked(n, false);
	marked[0] = true;
	frontier.push(0);

	bool success = false;
	while (!frontier.empty()) {
		int u = frontier.front(); frontier.pop();

		for (int v : edges[u]) {
			if (v == t) {
				success = true;
				break;
			}

			if (!marked[v]){
				marked[v] = true;
				frontier.push(v);
			}
		}
	}

	cout << (success ? "YES" : "NO") << endl;

	return 0;
}