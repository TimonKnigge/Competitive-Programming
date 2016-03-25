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
using ld = long double;
using ii = pair<ll, ll>;
using vi = vector<ll>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

struct BCC{		// find AVs and bridges in an undirected graph
	vvi &edges;
	int V, counter = 0, root, rcs;		// root and # children of root
	vi n,l;								// nodes,low
	stack<int> s;
	set<ii> &bridges;
	BCC(vvi &e, set<ii> &bridges) : edges(e), V(e.size()), n(V,-1), l(V,-1), bridges(bridges) {}
	void visit(int u, int p) {			// also pass the parent
		l[u] = n[u] = counter++; s.push(u);
		for(auto &v : edges[u]){
			if (n[v] == -1) {
				if (u == root) rcs++; visit(v,u);
				if (l[v] >= n[u]) {}	// u is an articulation point
				if (l[v] > n[u]) {		// u<->v is a bridge
					bridges.insert({u, v});
					bridges.insert({v, u});
					while(true){		// biconnected component
						int w = s.top(); s.pop();	// <= ACT HERE
						if(w==v) break;
					}
				}
				l[u] = min(l[u], l[v]);
			} else if (v != p) l[u] = min(l[u], n[v]);
		}
	}
	void run() {
		for (int u = 0; u < V; ++u) if (n[u] == -1) {
			root = u; rcs = 0; visit(u,-1);
			if(rcs > 1) {}				// u is articulation point
		}
	}
};

void dfs(int u, vvi &E, vector<vb> &A, vector<vb> &isbridge, vi &partof, vb &hasA, vi &BTpar) {
	
	for (size_t i = 0; i < E[u].size(); ++i) {
		int v = E[u][i];
		if (isbridge[u][i] && partof[v] == -1LL) {
			
			partof[v] = BTpar.size();
			BTpar.push_back(partof[u]);
			hasA.push_back(A[u][i]);

			dfs(v, E, A, isbridge, partof, hasA, BTpar);
			
		} else if (!isbridge[u][i]) {
			
			if (A[u][i])
				hasA[partof[u]] = true;
			if (partof[v] == -1LL) {
				partof[v] = partof[u];
				dfs(v, E, A, isbridge, partof, hasA, BTpar);
			}
		}
	}
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N, M;
	cin >> N >> M;
	
	vvi E(N, vi());
	vector<vb> A(N, vb());
	while (M--) {
		int x, y, z;
		cin >> x >> y >> z;
		--x; --y;
		E[x].push_back(y);
		E[y].push_back(x);
		A[x].push_back(z == 1);
		A[y].push_back(z == 1);
	}
	
	int a, b;
	cin >> a >> b;
	--a; --b;
	
	set<ii> bridges;
	BCC bcc(E, bridges);
	bcc.run();
	
	vector<vb> isbridge(N, vb());
	for (int u = 0; u < N; ++u)
		for (size_t i = 0; i < E[u].size(); ++i)
			if (bridges.find({u, E[u][i]}) != bridges.end())
				isbridge[u].push_back(true);
			else	isbridge[u].push_back(false);
	
//	cerr << "Marked bridges" << endl;
	
	// bridge tree
	vi partof(N, -1), BTpar(1, -1);
	vb hasA(1, false);
	partof[a] = 0;
	dfs(a, E, A, isbridge, partof, hasA, BTpar);
	
	
	int u = partof[b];
	bool ans = false;
	while (u != -1) {
		ans = ans || hasA[u];
		u = BTpar[u];
	}
	
	cout << (ans ? "YES" : "NO") << endl;
	
	return 0;
}
