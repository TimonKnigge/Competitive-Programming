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

struct Tarjan {
	vvi &edges;
	int V, counter = 0, C = 0;
	vi n, l;
	vb vs;
	stack<int> st;

	Tarjan(vvi &e) : edges(e), V(e.size()),
		n(V, -1), l(V, -1), vs(V, false) { }

	void visit(int u, vi &com) {
		l[u] = n[u] = counter++;
		st.push(u); vs[u] = true;
		for (auto &&v : edges[u]) {
			if (n[v] == -1) visit(v, com);
			if (vs[v]) l[u] = min(l[u], l[v]);
		}
		if (l[u] == n[u]) {
			while (true) {
				int v = st.top(); st.pop(); vs[v] = false;
				com[v] = C;		//<== ACT HERE
				if (u == v) break;
			}
			C++;
		}
	}

	int find_sccs(vi &com) { // component indices will be stored in 'com'
		com.assign(V, -1);
		C = 0;
		for (int u = 0; u < V; ++u)
			if (n[u] == -1) visit(u, com);
		return C;
	}

	// scc is a map of the original vertices of the graph
	// to the vertices of the SCC graph, scc_graph is its
	// adjacency list.
	// Scc indices and edges are stored in 'scc' and 'scc_graph'.
	void scc_collapse(vi &scc, vvi &scc_graph) {
		find_sccs(scc);
		scc_graph.assign(C,vi());
		set<ii> rec; // recorded edges
		for (int u = 0; u < V; ++u) {
			assert(scc[u] != -1);
			for (int v : edges[u]) {
				if (scc[v] == scc[u] ||
					rec.find({scc[u], scc[v]}) != rec.end()) continue;
				scc_graph[scc[u]].push_back(scc[v]);
				rec.insert({scc[u], scc[v]});
			}
		}
	}
};


int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		int N, M, K;
		scanf("%d %d %d", &N, &M, &K);
		vector<bool> delcity(N, false);
		for (int i = 0; i < K; ++i) {
			int u; scanf("%d", &u); delcity[u - 1] = true;
		}
		
		vvi e(N, vi());
		for (int i = 0; i < M; ++i) {
			int x, y;
			scanf("%d %d", &x, &y);
			x--; y--;
			e[x].push_back(y);
		}
		
		Tarjan tj(e);
		
		vi scc; vvi scc_graph;
		tj.scc_collapse(scc, scc_graph);
		
		int C = scc_graph.size();
		vvi delcom(C, vi());
		for (int i = 0; i < N; ++i) if (!delcity[i]) continue; else
			delcom[scc[i]].push_back(i);
		
//		for (int i = 0; i < C; ++i) {
//			cerr << i << ": ";
//			for (int v : scc_graph[i]) cerr << v << ' ';
//			cerr << endl;
//		}
		
		int CUR = -1;
		vi rch(C, -1);
		int st = C - 1;
		while (delcom[st].size() == 0) st--;
		
		rch[st] = CUR;
		bool pos = true;
		for (int c = st; c >= 0; --c) {
			if (delcom[c].size() > 0) {
				if (rch[c] == CUR) {
					rch[c]++; CUR++;
				} else {
					pos = false;
				}
			}
			for (int v : scc_graph[c]) {
				rch[v] = max(rch[v], rch[c]);
			}
		}
		
		if (!pos) printf("-1\n");
		else {
			bool sp = false;
			for (int c = C - 1; c >= 0; --c) {
				sort(delcom[c].begin(), delcom[c].end());
				for (int i = 0; i < delcom[c].size(); ++i) {
					if (!sp) sp = true;
					else printf(" ");
					printf("%d", 1 + delcom[c][i]);
				}
			}
			printf("\n");
		}
	}
	
	return 0;
}
