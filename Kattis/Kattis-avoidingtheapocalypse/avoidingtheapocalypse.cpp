#include <iostream>
#include <iomanip>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <bitset>
#include <algorithm>
#include <functional>
#include <string>
#include <cstring>
#include <cmath>

#define LLINF 9000000000000000000LL
using namespace std;

typedef long long ll;

struct FlowNetwork {
	struct edge {
		int v, nxt; ll cap, flo;
		edge(int _v, ll _cap, int _nxt) : v(_v), cap(_cap), nxt(_nxt), flo(0) { }
	};
	int n, edge_count = 0, *h;
	vector<edge> e;
	FlowNetwork(int V, int E = 0) : n(V) {
		e.reserve(2 * (E == 0 ? V : E));
		memset(h = new int[V], -1, n * sizeof(int));
	}
	void add_edge(int u, int v, ll uv_cap, ll vu_cap = 0) {
		e.push_back(edge(v, uv_cap, h[u])); h[u] = edge_count++;
		e.push_back(edge(u, vu_cap, h[v])); h[v] = edge_count++;
	}
	void cleanup() { delete[] h; }
	ll edmonds_karp(int s, int t);
};

#define MAXV 102000
ll FlowNetwork::edmonds_karp(int s, int t) {
	int v, *p = new int[MAXV], *q = new int[MAXV]; ll f = 0, *c = new ll[MAXV];
	while (true) {
		memset(p, -1, n * sizeof(int));
		int i, u = -1, l = 0, r = 0;
		c[s] = LLINF; p[q[r++] = s] = -2;
		while (l != r && u != t) {
			for (u = q[l++], i = h[u]; i != -1; i = e[i].nxt) {
				if (e[i].cap > e[i].flo && p[v = e[i].v] == -1) {
					p[q[r++] = v] = i;
					c[v] = min(c[u], e[i].cap - e[i].flo);
				}
			}
		}
		if (p[t] == -1) break;
		for (i = p[t]; i != -2; i = p[e[i ^ 1].v]) {
			e[i].flo += c[t]; e[i ^ 1].flo -= c[t];
		}
		f += c[t];
	}
	delete[] p;
	delete[] q;
	delete[] c;
	return f;
}

#define VTX(position, time) ((position) + (n + 1) * (time))
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int T; cin >> T;
	for (int _T = 1; _T <= T; ++_T) {

		int n, i, g, s, m;
		cin >> n >> i >> g >> s >> m;

		// Add medical facilities
		int SOURCE = 0, SINK = (n + 1) * (s + 1) + 1;
		FlowNetwork fn((n + 1) * (s + 1) + 2);
		fn.add_edge(SOURCE, VTX(i, 0), g);
		for (int j = 0; j < m; ++j) {
			int x; cin >> x;
			for (int t = 0; t <= s; ++t)
				fn.add_edge(VTX(x, t), SINK, LLINF);
		}

		// Add remain-in-one-place edges
		for (int p = 0; p < n; ++p) {
			for (int t = 0; t < s; ++t) {
				fn.add_edge(VTX(p, t), VTX(p, t + 1), LLINF);
			}
		}

		// Add move vertices for every timestamp
		int r;
		cin >> r;
		for (int j = 0; j < r; ++j) {
			int a, b, p, d;
			cin >> a >> b >> p >> d;
			for (int t = 0; t <= s - d; ++t) {
				fn.add_edge(VTX(a, t), VTX(b, t + d), p);
			}
		}

		cout << fn.edmonds_karp(SOURCE, SINK) << endl;
	}
	return 0;
}