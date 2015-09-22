#include <iostream> 
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

void dfs_rel(int u, vvi &e, vb &rel) {
	if (rel[u]) return;
	rel[u] = true;
	for (int v : e[u]) dfs_rel(v, e, rel);
}

struct Edge_Classification {
	vector<vi> &edges; int V; vi color, parent; bool has_back_edge = false;
	Edge_Classification(vector<vi> &edges) :
		edges(edges), V(edges.size()),
		color(V,-1), parent(V, -1) {}

	void visit(int u) {
		color[u] = 1;		// in progress
		for (int v : edges[u]) {
			if (color[v] == -1) { // u -> v is a tree edge
				parent[v] = u;
				visit(v);
			} else if (color[v] == 1) {
				if (v == parent[u]) { has_back_edge = true; } // u -> v is a bidirectional edge
				else { has_back_edge = true; } // u -> v is a back edge (thus contained in a cycle)
			} else if (color[v] == 2) {} // u -> v is a forward/cross edge
		}
		color[u] = 2;		// done
	}
	void run(){
		for (int u = 0; u < V; ++u) if(color[u] < 0) visit(u);
	}
};


int main() {
	int n;
	scanf("%d", &n);
	
	vvi e(n, vi()), er(n, vi());
	for (int u = 0; u < n - 1; ++u) {
		int k;
		scanf("%d", &k);
		for (int i = 0; i < k; ++i) {
			int v;
			scanf("%d", &v);
			e[u].push_back(v - 1);
			er[v - 1].push_back(u);
		}
	}
	
	vector<bool> rel(n, false), rrel(n, false); // relevant
	dfs_rel(0, e, rel);
	dfs_rel(n - 1, er, rrel);
	
	bool pardon = true;
	for (int u = 0; u < n; ++u) {
		if (rel[u] && !rrel[u]) pardon = false;
	}
	
	Edge_Classification ec(e);
	ec.run();
	
	if (pardon) printf("PARDON ");
	else printf("PRISON ");
	if (ec.has_back_edge) printf("UNLIMITED\n");
	else printf("LIMITED\n");
	
	return 0;
}
