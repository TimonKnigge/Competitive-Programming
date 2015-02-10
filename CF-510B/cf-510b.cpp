#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <bitset>
#include <algorithm>
#include <functional>
#include <string>
#include <math.h>

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef long long ll;

#define COORD(x, y) ((x) + n * (y))
#define X(u) ((u) % n)
#define Y(u) ((u) / n)
int n, m;
vvi edges;
vector<bool> mark;
vi color;
bool cycle = false;

void dfs(int u, int p) {
	if (mark[u] || cycle){
		cycle = true;
		return;
	}
	mark[u] = true;
	for (int v : edges[u]) {
		if (v == p) continue;
		else dfs(v, u);
	}
}

int main(){
	cin >> m >> n;

	// Read the graph
	color = vi(n * m);
	for (int y = 0; y < m; ++y) {
		for (int x = 0; x < n; ++x) {
			char c;
			cin >> c;
			color[COORD(x, y)] = c - 'A';
		}
	}

	// Reconstruct the graph
	edges = vvi(n * m);

	for (int y = 0; y < m; ++y) {
		for (int x = 0; x < n; ++x) {
			if (x > 0 && color[COORD(x - 1, y)] == color[COORD(x, y)])
				edges[COORD(x, y)].push_back(COORD(x - 1, y));
			if (y > 0 && color[COORD(x, y - 1)] == color[COORD(x, y)])
				edges[COORD(x, y)].push_back(COORD(x, y - 1));
			if (x < n - 1 && color[COORD(x + 1, y)] == color[COORD(x, y)])
				edges[COORD(x, y)].push_back(COORD(x + 1, y));
			if (y < m - 1 && color[COORD(x, y + 1)] == color[COORD(x, y)]){
				edges[COORD(x, y)].push_back(COORD(x, y + 1));
			}
		}
	}

	// DFS from all nodes
	mark = vector<bool>(n * m, false);
	for (int y = 0; y < m; ++y) {
		for (int x = 0; x < n; ++x) {
			if (mark[COORD(x, y)]) continue;
			else dfs(COORD(x, y), -1);
		}
	}

	cout << (cycle ? "YES" : "NO") << endl;

	return 0;
}