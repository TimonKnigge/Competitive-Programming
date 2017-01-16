#include <iostream> 
#include <fstream>
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

template <class T>
struct FenwickTree {		// use 1 based indices!!!
	int n; vector<T> tree;
	FenwickTree(int n) : n(n) { tree.assign(n + 1, 0); }
	T query(int l, int r) { return query(r) - query(l - 1); }
	T query(int r) {
		T s = 0;
		for(; r > 0; r -= (r & (-r))) s += tree[r];
		return s;
	}
	void update(int i, T v) {
		for(; i <= n; i += (i & (-i))) tree[i] += v;
	}
};

void dfs(ll u, vi &p, vvi &ch, vi &l, vi &r, int &t) {
	l[u] = r[u] = t++;
	for (ll v : ch[u]) {
		dfs(v, p, ch, l, r, t);
		r[u] = r[v];
	}
//	cerr << u << ' ' << l[u] << ' ' << r[u] << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	ifstream fin("promote.in");
	
	int N;
	fin >> N;
	
	vi c(N, 0LL);
	for (ll &v : c) fin >> v;
	
	vi p(N, -1LL);
	vvi ch(N, vi());
	for (int i = 1; i < N; ++i) fin >> p[i], --p[i], ch[p[i]].push_back(i);
	
	vi L(N, -1LL), R(N, -1LL);
	int t = 0;
	dfs(0, p, ch, L, R, t);
	
	vii q;
	for (int i = 0; i < N; ++i) q.push_back({c[i], i});
	sort(q.rbegin(), q.rend());
	
	vi ans(N, 0LL);
	FenwickTree<ll> ft(N+3LL);
	for (int l = 0, r = 0; l < N; l = r) {
		while (r < N && q[l].first == q[r].first) ++r;
		for (int i = l; i < r; ++i) {
//			cerr << "Considering " << q[i].second << endl;
			int j = q[i].second;
			ans[j] = ft.query(L[j]+1, R[j]+1);
		}
		for (int i = l; i < r; ++i) {
			ft.update(L[q[i].second]+1, 1);
		}
	}
	
	ofstream fout("promote.out");
	for (int i = 0; i < N; ++i)
		fout << ans[i] << "\n";
	
	return 0;
}
