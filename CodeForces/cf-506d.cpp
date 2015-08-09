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
#include <cassert>

const int INF = 2000000000;                     // 9
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

class UnionFind {
private:
	vi par, ran, siz;
	int c;
	map<int, int> mp;
public:
	UnionFind() {
		c = 0;
	}
	void addNode(int id) {
		int i = c;
		mp.insert({id, i});
		c++;
		par.push_back(i);
		ran.push_back(0);
		siz.push_back(1);
	}
	bool has(int id) { return mp.find(id) != mp.end(); }
	int find_id(int i) {
		assert(has(i));
		return mp[i];
	}
	int find(int i) {
		return (i == par[i] ? i : (par[i] = find(par[i])));
	}
	bool same(int i, int j) {
		return (find(i) == find(j));
	}
	int count() { return c; }
	int size(int i) { return siz[find(i)]; }
	void union_set(int i, int j) {
		if ((i = find(i)) == (j = find(j))) {
			return;
		}
		c--;
		if (ran[i] > ran[j]) swap(i, j);
		par[i] = j;
		siz[j] += siz[i];
		if (ran[i] == ran[j]) ran[j]++;
	}
};

void solve(int c, vii &edges, vii &query, vvi &inv, vi &ans, vii &status) {
	UnionFind uf;
	vi qtocheck;
	for (int i = 0; i < edges.size(); ++i) {
		int a = edges[i].first, b = edges[i].second;
		if (!uf.has(a)) uf.addNode(a);
		if (!uf.has(b)) uf.addNode(b);
		for (int j = 0; j < inv[a].size(); ++j) {
			if (status[inv[a][j]].first != c && status[inv[a][j]].first != -c)
				status[inv[a][j]] = {c, a};
			else if (status[inv[a][j]].first == c && status[inv[a][j]].second != a) {
				status[inv[a][j]] = {-c, a};
				qtocheck.push_back(inv[a][j]);
			}
		}
		for (int j = 0; j < inv[b].size(); ++j) {
			if (status[inv[b][j]].first != c && status[inv[b][j]].first != -c)
				status[inv[b][j]] = {c, b};
			else if (status[inv[b][j]].first == c && status[inv[b][j]].second != b) {
				status[inv[b][j]] = {-c, b};
				qtocheck.push_back(inv[b][j]);
			}
		}
		uf.union_set(uf.find_id(a), uf.find_id(b));
	}
	for (int i = 0; i < qtocheck.size(); ++i) {
		if (status[qtocheck[i]].first == -INF) continue;
		status[qtocheck[i]].first = -INF;
		int u = query[qtocheck[i]].first, v = query[qtocheck[i]].second;
		if (uf.same(uf.find_id(u), uf.find_id(v))) ans[qtocheck[i]]++;
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, m;
	cin >> n >> m;
	
	vector<pair<int, ii>> edges;
	for (int i = 0; i < m; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		a--; b--;
		edges.push_back({c, {a, b}});
	}
	sort(edges.begin(), edges.end());

	int q; cin >> q;
	vii query;
	vvi inv(n, vi());
	for (int i = 0; i < q; ++i) {
		int u, v;
		cin >> u >> v;
		u--; v--;
		query.push_back({u, v});
		inv[u].push_back(i);
		inv[v].push_back(i);
	}

	edges.push_back({INF, {INF, INF}});
	vii cedges, status(n, {-INF, -INF});
	vi ans(q, 0);
	for (int i = 0; i <= m; ++i) {
		if (i == 0 || edges[i].first == edges[i - 1].first) {
			cedges.push_back(edges[i].second);
		} else {
			solve(i, cedges, query, inv, ans, status);
			cedges.clear();
			cedges.push_back(edges[i].second);
		}
	}

	for (int i = 0; i < q; ++i) {
		cout  << ans[i] << '\n';
	}
	cout << flush;
	
	return 0;
}
