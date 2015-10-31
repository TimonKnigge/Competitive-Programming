/*	Still gets TLE, suffix array too slow	*/

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

struct SuffixArray {
	vi s;
	int n;
	vvi P;
	SuffixArray(vi &_s) : s(_s), n(_s.size()) { construct(); }
	void construct() {
//		P.push_back(vi(n, 0));
//		compress();
		P.push_back(vi(n, 0));
		for (int k = 0; k < n; ++k) P[0][k] = s[k];
		vi occ(n + 1, 0), s1(n, 0), s2(n, 0);
		for (int k = 1, cnt = 1; cnt / 2 < n; ++k, cnt *= 2) {
			P.push_back(vi(n, 0));
			fill(occ.begin(), occ.end(), 0);
			for (int i = 0; i < n; ++i)
				occ[i+cnt<n ? P[k-1][i+cnt]+1 : 0]++;
			partial_sum(occ.begin(), occ.end(), occ.begin());
			for (int i = n - 1; i >= 0; --i)
				s1[--occ[i+cnt<n ? P[k-1][i+cnt]+1 : 0]] = i;
			fill(occ.begin(), occ.end(), 0);
			for (int i = 0; i < n; ++i)
				occ[P[k-1][s1[i]]]++;
			partial_sum(occ.begin(), occ.end(), occ.begin());
			for (int i = n - 1; i >= 0; --i)
				s2[--occ[P[k-1][s1[i]]]] = s1[i];
			for (int i = 1; i < n; ++i) {
				P[k][s2[i]] = same(s2[i], s2[i - 1], k, cnt) 
					? P[k][s2[i - 1]] : i;
			}
		}
	}
	bool same(int i, int j, int k, int l) {
		return P[k - 1][i] == P[k - 1][j]
			&& (i + l < n ? P[k - 1][i + l] : -1)
			== (j + l < n ? P[k - 1][j + l] : -1);
	}
//	void compress() {
//		vi cnt(256, 0);
//		for (int i = 0; i < n; ++i) cnt[s[i]]++;
//		for (int i = 0, mp = 0; i < 256; ++i)
//			if (cnt[i] > 0) cnt[i] = mp++;
//		for (int i = 0; i < n; ++i) P[0][i] = cnt[s[i]];
//	}
	vi &get_array() { return P.back(); }
	int lcp(int x, int y) {
		int ret = 0;
		if (x == y) return n - x;
		for (int k = P.size() - 1; k >= 0 && x < n && y < n; --k)
			if (P[k][x] == P[k][y]) {
				x += 1 << k;
				y += 1 << k;
				ret += 1 << k;
			}
		return ret;
	}
};


struct S{
	int v;			// neighbour
	const int r;	// index of the reverse edge
	ll f;			// current flow
	const ll cap;	// capacity
	const ll cost;	// unit cost
	S(int v, int reverse_index, ll capacity, ll cost = 0) :
		v(v), r(reverse_index), f(0), cap(capacity), cost(cost) {}
};
struct FlowGraph : vector<vector<S>> {
	FlowGraph(size_t n) : vector<vector<S>>(n) {}
	void add_edge(int u, int v, ll capacity, ll cost = 0){
		operator[](u).emplace_back(v, operator[](v).size(), capacity, cost);
		operator[](v).emplace_back(u, operator[](u).size()-1, 0, -cost);
	}
};


struct Dinic{
	FlowGraph &edges; int V,s,t;
	vi l; vector<vector<S>::iterator> its; // levels and iterators
	Dinic(FlowGraph &edges, int s, int t) :
		edges(edges), V(edges.size()), s(s), t(t), l(V,-1), its(V) {}
	ll augment(int u, ll c) { // we reuse the same iterators
		if (u == t) return c;
		for(auto &i = its[u]; i != edges[u].end(); i++){
			auto &e = *i;
			if (e.cap > e.f && l[u] < l[e.v]) {
				auto d = augment(e.v, min(c, e.cap - e.f));
				if (d > 0) { e.f += d; edges[e.v][e.r].f -= d; return d; }
			}	}
		return 0;
	}
	ll run() {
		ll flow = 0, f;
		while(true) {
			fill(l.begin(), l.end(),-1); l[s]=0; // recalculate the layers
			queue<int> q; q.push(s);
			while(!q.empty()){
				auto u = q.front(); q.pop();
				for(auto &&e : edges[u]) if(e.cap > e.f && l[e.v]<0)
					l[e.v] = l[u]+1, q.push(e.v);
			}
			if (l[t] < 0) return flow;
			for(int u = 0; u < V; ++u) its[u] = edges[u].begin();
			while ((f = augment(s, INF)) > 0) flow += f;
		}	}
};


void imc_dfs(FlowGraph &fg, int u, vb &cut) {
	cut[u] = true;
	for (auto &&e : fg[u]) {
		if (e.cap > e.f && !cut[e.v])
			imc_dfs(fg, e.v, cut);
	}
}
ll infer_minimum_cut(FlowGraph &fg, int s, vb &cut) {
	cut.assign(fg.size(), false);
	imc_dfs(fg, s, cut);
	ll cut_value = 0LL;
	for (size_t u = 0; u < fg.size(); ++u) {
		if (!cut[u]) continue;
		for (auto &&e : fg[u]) {
			if (cut[e.v]) continue;
			cut_value += e.cap;
			// The edge e from u to e.v is
			// in the minimum cut.
		}
	}
	return cut_value;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	vector<int> str;
	int id = 2;
	map<int, int> idmap;
	vi start;
	vi lengthof;
	for (int i = 0; i < n; ++i) {
		string s;
		cin >> s;
		start.push_back(str.size());
		lengthof.push_back(s.length());
		for (int j = 0; j < s.length(); ++j) {
			if (s[j] == 'a')
				str.push_back(0);
			else
				str.push_back(1);
		}
		str.push_back(id);
		idmap.insert({str.size(), i});
		id++;
	}
	idmap.insert({INF, -1});
	
	SuffixArray sa(str);
	vi &inv = sa.get_array();
	vi arr(inv.size(), 0);
	for (int i = 0; i < inv.size(); ++i) {
		arr[inv[i]] = i;
	}
	
	// For each string, note its positions in the suffix array
	vvi pos(n, vi());
	for (int i = 0; i < n; ++i) {
		int s = start[i];
		int e = (i < n - 1 ? start[i + 1] : str.size());
		for (int j = s; j < e; ++j)
			pos[i].push_back(inv[j]);
		sort(pos[i].begin(), pos[i].end());
	}
	
//	for (int i = 0; i < str.size(); ++i)
//		cerr << str[i] << ' ';
//	cerr<<endl;
	
//	cerr << "Suffix array"<<endl;
//	for (int i = 0; i < arr.size(); ++i) {
//		for (int k = arr[i];; ++k) {
//			cerr << str[k];
//			if (str[k] >= 2) break;
//		}
//		cerr<<endl;
//	}
	
//	cerr << "Positions " << endl;
//	for (int i = 0; i < n; ++i) {
//		cerr << (i + 2) << endl;
//		for (int j : pos[i]) cerr << j << ' ';
//		cerr << endl;
//	}
	
	vector<vb> subs(n, vb(n, false));
	
	for (int i = 0; i < n; ++i) {
		int mypos = inv[start[i]];
		// Determine the interval with lcp == lengthof[i]
		int li = -1, ri = -1;
		
		int l = 0, r = mypos;
		while (l < r) {
			int m = (l + r) / 2;
			if (lengthof[i] <= sa.lcp(arr[mypos], arr[m]))
				r = m;
			else	l = m + 1;
		}
		li = l;
		l = mypos; r = arr.size() - 1;
		while (l < r) {
			int m = (l + r) / 2;
			if (lengthof[i] <= sa.lcp(arr[mypos], arr[m]))
				l = m + 1;
			else 	r = m;
		}
		ri = l - 1;
		
		// Determine for all other strings if they contain i
		for (int j = 0; j < n; ++j) {
			if (j == i) continue;
			// Does pos[j] contain an element in [li, ri] ?
			l = 0; r = pos[j].size() - 1;
			if (pos[j][r] < li) continue;
			while (l < r) {
				int m = (l + r) / 2;
				if (pos[j][m] < li)
					l = m + 1;
				else	r = m;
			}
			// pos[j][l] is the first element >= li
			if (pos[j][l] <= ri)
				subs[i][j] = true;
		}
	}
	
//	for (int i = 0; i < n; ++i) {
//		for (int j = 0; j < n; ++j)
//			cerr << subs[i][j];
//		cerr<<endl;
//	}
	
	
	FlowGraph fg(2 * n + 2);
	int SOURCE = 2 * n, SINK = 2 * n + 1;
	for (int i = 0; i < n; ++i) {
		fg.add_edge(SOURCE, i, 1);
		fg.add_edge(i + n, SINK, 1);
		for (int j = 0; j < n; ++j) {
			if (i == j || !subs[i][j]) continue;
			fg.add_edge(i, n + j, 1);
		}
	}
	
	Dinic dn(fg, SOURCE, SINK);
	dn.run();
	
	// Extract the matching
	vi match(n, -1);
	vi rmatch(n, -1);
	int ans = n;
	for (int i = 0; i < n; ++i) {
		for (auto it : fg[i]) {
			if (it.f != 1) continue;
			int v = it.v - n;
			match[i] = v;
			rmatch[v] = i;
			ans--;
//			cerr << "matched " << i << " to " << v << endl;
		}
	}
	cout << ans << endl;
	
	// Construct the vertex cover
	vb cut(2 * n + 2, false);
	infer_minimum_cut(fg, SOURCE, cut);
	vb cover(n, false);
	for (int i = 0; i < n; ++i) {
		if (match[i] >= 0 && !cut[i])
			cover[i] = true;
		if (rmatch[i] >= 0 && cut[i + n])
			cover[i] = true;
	}
	
	bool f = false;
	for (int i = 0; i < n; ++i) {
		if (cover[i]) continue;
		if (f) cout << ' '; else f = true;
		cout << (i + 1);
	}
	cout << endl;
	
	
	return 0;
}
