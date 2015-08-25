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
#include <string.h>  // Include for memset!
#include <complex>
#include <random>
#define _USE_MATH_DEFINES
#include <math.h>

const int INF = 2000000000;	                 // 9
const long long LLINF = 9000000000000000000LL;  // 18
const long double LDINF = 1e300;

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<bool> vb;
typedef long long ll;
typedef long double ld;

struct FlowNetwork {
	struct edge {
		int v, nxt; ll cap, flo;
		edge(int _v, ll _cap, int _nxt) : v(_v), nxt(_nxt), cap(_cap), flo(0) { }
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
	ll dinic(int s, int t);
	ll dinic_augment(int s, int t, int *d, ll cap);
};

#define MAXV 4050
ll FlowNetwork::dinic_augment(int s, int t, int *d, ll cap) {
	if (s == t) return cap;
	ll f = 0, df = 0;
	for (int i = h[s]; i != -1; i = e[i].nxt) {
		if (e[i].cap > e[i].flo && d[s] + 1 == d[e[i].v]) {
			f += (df = dinic_augment(e[i].v, t, d, min(cap, e[i].cap - e[i].flo)));
			e[i].flo += df;
			e[i ^ 1].flo -= df;
			if ((cap -= df) == 0) break;
		}
	}
	return f;
}

ll FlowNetwork::dinic(int s, int t) {
	int q[MAXV], d[MAXV]; ll f = 0;
	while (true) {
		memset(d, -1, n * sizeof(int));
		int l = 0, r = 0, u = -1, i;
		d[q[r++] = s] = 0;
		while (l != r && u != t)
			for (u = q[l++], i = h[u]; i != -1; i = e[i].nxt)
				if (e[i].cap > e[i].flo && d[e[i].v] == -1)
					d[q[r++] = e[i].v] = d[u] + 1;
		if (d[t] == -1) break;
		f += dinic_augment(s, t, d, LLINF);
	}
	return f;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N;
	cin >> N;
	FlowNetwork fn(2 * N + 2);
	for (int i = 0; i < N; ++i) {
		int k;
		cin >> k;
		for (int j = 0; j < k; ++j) {
			int v; cin >> v;
			if (v == i) continue;
			fn.add_edge(i, v + N, 1);
		}
		fn.add_edge(2 * N, i, 1);
		fn.add_edge(i + N, 2 * N + 1, 1);
	}

	cout << (N -int(fn.dinic(2 * N, 2 * N + 1))) << endl;

	fn.cleanup();
	
	return 0;
}
