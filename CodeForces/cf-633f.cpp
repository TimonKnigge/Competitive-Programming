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

ll ans = 0LL;

void dfs(int u, int p, vvi &e, vi &A,
	vi &p1, vi &p2) {

	for (int v : e[u])
		if (v != p)
			dfs(v, u, e, A, p1, p2);
	
	ll v1 = 0LL, v2 = 0LL;
	for (int v : e[u]) {
		if (v == p) continue;
		if (p1[v] > v1) { v2 = v1; v1 = p1[v]; }
		else if (p1[v] > v2) v2 = p1[v];
		p2[u] = max(p2[u], p2[v]);
	}
	p2[u] = max(p2[u], A[u] + v1 + v2);
	p1[u] = A[u] + v1;
}

void dfs2(int u, int p, vvi &e, vi &A,
	vi &p1, vi &p2, vi &p3) {
	
	ll v1 = 0LL, v2 = 0LL;
	int i1 = -1;
	for (int v : e[u]) {
		if (v == p) continue;
		p3[v] = A[u] + p3[u];
		if (p1[v] > v1) {
			v2 = v1;
			v1 = p1[v];
			i1 = v;
		} else if (p1[v] > v2) v2 = p1[v];
	}
	
	for (int v : e[u]) {
		if (v == p) continue;
		if (v == i1)
			p3[v] = max(p3[v], A[u] + v2);
		else	p3[v] = max(p3[v], A[u] + v1);
	}
	
	for (int v : e[u])
		if (v != p)
			dfs2(v, u, e, A, p1, p2, p3);
}

void dfs4(int u, int p, vvi &e, vi &A,
	vi &p1, vi &p2, vi &p3, vi &p4) {
	for (int v : e[u])
		if (p != v)
			dfs4(v, u, e, A, p1, p2, p3, p4);
	
	ll v1 = 0LL, v2 = 0LL, v3 = 0LL;
	int i1 = -1, i2 = -1;
	for (int v : e[u]) {
		if (p == v) continue;
		if (p1[v] > v1) {
			v3 = v2;
			v2 = v1;
			i2 = i1;
			v1 = p1[v];
			i1 = v;
		} else if (p1[v] > v2) {
			v3 = v2;
			v2 = p1[v];
			i2 = v;
		} else if (p1[v] > v3) v3 = p1[v];
	}
	
	p4[u] = A[u] + p3[u];
	for (int v : e[u]) {
		if (p == v) continue;
		if (v == i1)
			p4[u] = max(p4[u], p2[v] + A[u] + v2 + max(p3[u], v3));
		else if (v == i2)
			p4[u] = max(p4[u], p2[v] + A[u] + v1 + max(p3[u], v3));
		else	p4[u] = max(p4[u], p2[v] + A[u] + v1 + max(p3[u], v2));
	}
	
	v1 = 0LL; v2 = 0LL;
	for (int v : e[u]) {
		if (p == v) continue;
		if (p2[v] > v1) {
			v2 = v1;
			v1 = p2[v];
		} else if (p2[v] > v2)
			v2 = p2[v];
	}
	p4[u] = max(p4[u], v1 + v2);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N;
	cin >> N;
	
	vi A(N, 0LL);
	for (int i = 0; i < N; ++i) cin >> A[i];
	vvi e(N, vi());
	for (int i = 1; i < N; ++i) {
		int a, b;
		cin >> a >> b;
		--a;
		--b;
		e[a].push_back(b);
		e[b].push_back(a);
	}
	
	vi p1(N, 0LL), p2(N, 0LL);
	dfs(0, -1, e, A, p1, p2);
	vi p3(N, 0LL);
	dfs2(0, -1, e, A, p1, p2, p3);
	vi p4(N, 0LL);
	dfs4(0, -1, e, A, p1, p2, p3, p4);
	
	ll ans = 0LL;
	for (int i = 0; i < N; ++i) {
		if (p4[i] > ans) ans = p4[i];
//		cerr << i << '\t' << p1[i] << '\t' << p2[i] << '\t' << p3[i] << '\t' << p4[i] << endl;
	}
	cout << ans << endl;
	
	return 0;
}
