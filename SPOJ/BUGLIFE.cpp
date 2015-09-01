#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <cassert>
using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;

struct Tarjan {
	vvi &edges;
	int V, counter = 0, C = 0;
	vi index, lowlink;
	vb instack;
	stack<int> st;
	
	Tarjan(vvi &e) : edges(e), V(e.size()),
		index(V, -1), lowlink(V, -1), instack(V, false) { }

	void visit(int u, vi &com) {
		lowlink[u] = index[u] = counter++;
		st.push(u); instack[u] = true;
		for (auto &&v : edges[u]) {
			if (index[v] == -1) {
				visit(v, com);
				lowlink[u] = min(lowlink[u],lowlink[v]);
			} else if (instack[v]) {
				lowlink[u] = min(lowlink[u], index[v]);
			}
		}
		if (lowlink[u] == index[u]) {
			while (true) {
				int v = st.top(); st.pop();
				instack[v] = false;
				com[v] = C;
				if (u == v) break;
			}
			C++;
		}
	}

	int find_sccs(vi &com) {
		com.assign(V, -1);
		C = 0;
		for (int u = 0; u < V; ++u)
			if (index[u] == -1) visit(u, com);
		return C;
	}

	// scc is a map of the original vertices of the graph
	// to the vertices of the SCC graph, scc_graph is its
	// adjacency list.
	void scc_collapse(vi &scc, vvi &scc_graph) {
		find_sccs(scc);
		scc_graph.assign(C, vi());
		set<ii> rec;
		for (int u = 0; u < V; ++u) {
			assert(scc[u] != -1);
			for (int v : edges[u]) {
				// Implicit edge (scc[u], scc[v])
				if (rec.find({scc[u], scc[v]}) != rec.end()
					|| scc[u] == scc[v]) continue;
				scc_graph[scc[u]].push_back(scc[v]);
				rec.insert({scc[u], scc[v]});
			}
		}
	}
};

struct TwoSAT {
	int n;
	vvi imp; // implication graph
	Tarjan tj;

	TwoSAT(int _n) : n(_n), imp(2 * _n, vi()), tj(imp) { }

	// Only copy the needed functions:
	void add_implies(int c1, bool v1, int c2, bool v2) {
		int u = 2 * c1 + (v1 ? 1 : 0),
		    v = 2 * c2 + (v2 ? 1 : 0);
		imp[u].push_back(v);		//  u =>  v
		imp[v^1].push_back(u^1);	// -v => -u
	}
	void add_equivalence(int c1, bool v1, int c2, bool v2) {
		add_implies(c1, v1, c2, v2);
		add_implies(c2, v2, c1, v1);
	}
	void add_or(int c1, int v1, int c2, bool v2) {
		add_implies(c1, !v1, c2, v2);
	}
	void add_and(int c1, int v1, int c2, int v2) {
		add_true(c1, v1); add_true(c2, v2);
	}
	void add_xor(int c1, int v1, int c2, int v2) {
		add_or(c1, v1, c2, v2);
		add_or(c1, !v1, c2, !v2);
	}
	void add_true(int c1, int v1) {
		add_implies(c1, !v1, c1, v1);
	}

	// on true: a contains an assignment.
	// on false: no assignment exists.
	bool solve(/*vb &a*/) {
		vi com;
		tj.find_sccs(com);
		for (int i = 0; i < n; ++i)
			if (com[2 * i] == com[2 * i + 1])
				return false;
/*		
		a.assign(n, false);
		vvi bycom(com.size(), vi());
		for (int i = 0; i < 2 * n; ++i)
			bycom[com[i]].push_back(i);
		
		vb vis(n, false);
		for (int c = 0; c < bycom.size(); ++c) {
			for (int u : bycom[c]) {
				if (vis[u / 2]) continue;
				vis[u / 2] = true;
				a[u / 2] = (u % 2 == 1);
			}
		} */
		return true;
	}
};

int main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int T;
	cin >> T;
	for (int t = 1; t <= T; ++t) {
		int n, m; cin >> n >> m;
		TwoSAT ts(n);
		for (int i = 0; i < m; ++i) {
			int x, y;
			cin >> x >> y;
			ts.add_xor(x-1, true, y-1, true);
		}

		cout << "Scenario #" << t << ":\n";
		cout << (ts.solve() ? "No s" : "S");
		cout << "uspicious bugs found!\n";
	}
	cout << flush;

	return 0;
}

