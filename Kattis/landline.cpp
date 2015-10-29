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
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;


struct AdjEdge { int v; ll weight; };	// adjacency list edge
struct Edge { int u, v; };			// edge u->v for output
struct PQ { ll weight; Edge e; };	// PQ element
bool operator>(const PQ &l, const PQ &r) { return l.weight > r.weight; }
ll prim(vector<vector<AdjEdge>> &adj, vector<Edge> &tree, int u) {
	ll tc = 0; vb intree(adj.size(), false);
	priority_queue<PQ, vector<PQ>, greater<PQ> > pq;
	intree[u] = true;
	for (auto &e : adj[u]) pq.push({e.weight, {u, e.v}});
	while (!pq.empty()) {
		auto &top = pq.top();
		ll c = top.weight; auto e = top.e; pq.pop();
		if (intree[e.v]) continue;
		intree[e.v] = true; tc += c; tree.push_back(e);
		for (auto &e2 : adj[e.v])
			if (!intree[e2.v]) pq.push({e2.weight, {e.v, e2.v}});
	}
	return tc;
}

int main() {
	int n, m, p;
	scanf("%d %d %d", &n, &m, &p);
	
	vb insec(n, false);
	int s = n;
	for (int i = 0; i < p; ++i) {
		int x;
		scanf("%d", &x);
		x--;
		insec[x] = true;
		s--;
	}
	
	int sec = 0;
	while (insec[sec]) sec++;
	
	vector<vector<AdjEdge> > e(n, vector<AdjEdge>());
	vector<ll> best(n, LLINF);
	ll wght;
	for (int i = 0; i < m; ++i) {
		int x, y, l;
		scanf("%d %d %d", &x, &y, &l);
		x--; y--;
		wght = l;
		if (insec[x] && insec[y]) continue;
		if (insec[x]) {
			if (l < best[x]) best[x] = l;
			continue;
		}
		if (insec[y]) {
			if (l < best[y]) best[y] = l;
			continue;
		}
		e[x].push_back({y, ll(l)});
		e[y].push_back({x, ll(l)});
	}
	
	vector<Edge> tr;
	ll mst = 0LL;
	bool possible = true;
	if (sec < n) mst = prim(e, tr, sec);
	ll ans = 0LL;
	
	for (int i = 0; i < n; ++i) {
		if (!insec[i]) continue;
		if (best[i] == LLINF)
			possible = false;
		else ans += best[i];
	}
	
	if (int(tr.size()) < s - 1) possible = false;
	else ans += mst;
	
	if (n == 1) {
		possible = true;
		ans = 0;
	} else if (m == 0) {
		possible = false;
	} else if (n == 2) {
		possible = true;
		ans = wght;
	}
	
	if (possible) cout << ans << endl;
	else cout << "impossible"<<endl;
	
	return 0;
}
