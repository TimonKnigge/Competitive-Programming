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
	
	void reset() {
		n.assign(V, -1);
		l.assign(V, -1);
		vs.assign(V, false);
		while (!st.empty()) st.pop();
		counter = C = 0;
	}	
};

struct TwoSAT {
	int n;
	vvi imp; // implication graph
	Tarjan tj;

	TwoSAT(int _n) : n(_n), imp(2 * _n, vi()), tj(imp) { }
	
	void erase_true(int c, bool v) {
		erase_last(c, !v, c, v);
	}
	void erase_last(int c1, bool v1, int c2, bool v2) {
		int u = 2 * c1 + (v1 ? 1 : 0);
		int v = 2 * c2 + (v2 ? 1 : 0);
		imp[u].pop_back();
		imp[v^1].pop_back();
	}

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
	void add_or(int c1, bool v1, int c2, bool v2) {
		add_implies(c1, !v1, c2, v2);
	}
	void add_and(int c1, bool v1, int c2, bool v2) {
		add_true(c1, v1); add_true(c2, v2);
	}
	void add_xor(int c1, bool v1, int c2, bool v2) {
		add_or(c1, v1, c2, v2);
		add_or(c1, !v1, c2, !v2);
	}
	void add_true(int c1, bool v1) {
		add_implies(c1, !v1, c1, v1);
	}

	// on true: a contains an assignment.
	// on false: no assignment exists.
	bool solve(vb &a, vi &com, vvi &bycom) {
		tj.find_sccs(com);
		for (int i = 0; i < n; ++i)
			if (com[2 * i] == com[2 * i + 1])
				return false;

		bycom.assign(com.size(), vi());
		for (int i = 0; i < 2 * n; ++i)
			bycom[com[i]].push_back(i);

		a.assign(n, false);
		vb vis(n, false);
		for(auto &&component : bycom){
			for (int u : component) {
				if (vis[u / 2]) continue;
				vis[u / 2] = true;
				a[u / 2] = (u % 2 == 1);
			}
		}
		return true;
	}
};

void print_assignment(vb &s) {
	for (size_t i = 0; i < s.size(); ++i)
		cout << (s[i] ? 1 : 0) << " \n"[i + 1 == s.size()];
}


int main() {
	
	int N, M1, M2;
	scanf("%d %d %d", &N, &M1, &M2);
	
	TwoSAT t1(N), t2(N);
	while (M1--) {
		int l, r;
		scanf("%d %d", &l, &r);
		t1.add_or(abs(l) - 1, l > 0, abs(r) - 1, r > 0);
	}
	while (M2--) {
		int l, r;
		scanf("%d %d", &l, &r);
		t2.add_or(abs(l) - 1, l > 0, abs(r) - 1, r > 0);
	}
	
//	bool solve(vb &a, vi &com, vvi &bycom) {
	vb a1, a2;
	vi com1, com2;
	vvi bycom1, bycom2;
	
	bool p1 = t1.solve(a1, com1, bycom1);
	bool p2 = t2.solve(a2, com2, bycom2);
	
	if (!p1 && !p2)
		cout << "SIMILAR" << endl;
	else if (p1 && !p2)
		print_assignment(a1);
	else if (!p1 && p2)
		print_assignment(a2);
	else {
		vector<vb> imp1(2 * N, vb(2 * N, false)), imp2(2 * N, vb(2 * N, false));
		t1.tj.reset();
		t2.tj.reset();
		
		vi scc1, scc2;
		vvi sccg1, sccg2;
		t1.tj.scc_collapse(scc1, sccg1);
		t2.tj.scc_collapse(scc2, sccg2);
		
		vvi bycom1(sccg1.size(), vi());
		vvi bycom2(sccg2.size(), vi());
		for (size_t i = 0; i < scc1.size(); ++i)
			bycom1[scc1[i]].push_back(i);
		for (size_t i = 0; i < scc2.size(); ++i)
			bycom2[scc2[i]].push_back(i);
		
		for (size_t c = 0; c < sccg1.size(); ++c) {
			for (ll a : bycom1[c])
				for (ll b : bycom1[c])
					imp1[a][b] = true;
			for (ll c2 : sccg1[c])
				for (ll a : bycom1[c])
					for (ll b : bycom1[c2])
						imp1[a][b] = true;
		}
		
		for (size_t c = 0; c < sccg2.size(); ++c) {
			for (ll a : bycom2[c])
				for (ll b : bycom2[c])
					imp2[a][b] = true;
			for (ll c2 : sccg2[c])
				for (ll a : bycom2[c])
					for (ll b : bycom2[c2])
						imp2[a][b] = true;
		}
		
		bool similar = true;
		for (int i = 0; i < 2 * N; ++i)
			for (int j = 0; j < 2 * N; ++j)
				similar = similar && imp1[i][j] == imp2[i][j];
		
		if (similar) cout << "SIMILAR" << endl;
		else {
			int di = -1, dj = -1;
			bool success = false;
			for (int i = 0; i < 2 * N && !success; ++i)
				for (int j = 0; j < 2 * N && !success; ++j)
					if (imp1[i][j] != imp2[i][j]) {
						di = i;
						dj = j;
						t1.tj.reset();
						t2.tj.reset();
				
						int c1 = di / 2, c2 = dj / 2;
						bool v1 = (di % 2) == 1, v2 = (dj % 2) == 1;
//						cerr << di << ' ' << dj << endl;
//						cerr << c1 << ' ' << v1 << ' ' << c2 << ' ' << v2 << endl;
//						cerr << imp1[di][dj] << ' ' << imp2[di][dj] << endl;
			
						t1.add_true(c1, v1);
						t1.add_true(c2, !v2);
						t2.add_true(c1, v1);
						t2.add_true(c2, !v2);
			
						vb ans;
						vi tmp;
						vvi tmp2;
				
						if (t1.solve(ans, tmp, tmp2)) {
							print_assignment(ans);
							success = true;
						} else if (t2.solve(ans, tmp, tmp2)) {
							print_assignment(ans);
							success = true;
						}
						
						t1.erase_true(c1, v1);
						t1.erase_true(c2, !v2);
						t2.erase_true(c1, v1);
						t2.erase_true(c2, !v2);
					}

		}
	}
	
	return 0;
}
