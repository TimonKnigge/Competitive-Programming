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

void root(int u, int p, vvii &E, vvii &R, vi &C, vi &P, vi &D) {
	for (ii vw : E[u]) {
		if (vw.first == p) continue;
		C[vw.first] = C[u] + vw.second;
		R[u].push_back(vw);
		P[vw.first] = u;
		D[vw.first] = D[u] + 1LL;
		root(vw.first, u, E, R, C, P, D);
	}	
}

int lca(int u, int v, vvi &lift, vi &D) {
	if (D[u] < D[v]) swap(u, v);
	int LOG = int(lift.size());
	for (int i = LOG - 1; i >= 0; --i) {
		while (D[u] - D[v] >= (1<<i))
			u = lift[i][u];
	}
	assert(D[u] == D[v]);
	for (int i = LOG - 1; i >= 0; --i) {
		if (lift[i][u] != lift[i][v]) {
			u = lift[i][u];
			v = lift[i][v];
		}
	}
	assert(D[u] == D[v]);
	while (u != v) {
		u = lift[0][u];
		v = lift[0][v];
	}
	return u;
}

void solve() {

	int N;
	cin >> N;
	
	vvii E(N, vii());
	for (int i = 1; i < N; ++i) {
		int a, b;
		ll c;
		cin >> a >> b >> c;
		--a;
		--b;
		E[a].push_back({b, c});
		E[b].push_back({a, c});
	}
	
	vvii R(N, vii());
	vi P(N, -1LL), C(N, 0LL), D(N, 0LL);
	root(0, -1, E, R, C, P, D);
	
	// Binary lifting
	int LOG = 1;
	while ((1<<LOG) < N) ++LOG;
	++LOG;
	
	vvi lift(LOG, vi(N, -1LL));
	for (int i = 0; i < N; ++i)
		lift[0][i] = P[i];
	
	for (int j = 1; j < LOG; ++j)
		for (int i = 0; i < N; ++i)
			lift[j][i] = (lift[j-1][i] >= 0 ? lift[j-1][lift[j-1][i]] : -1LL);
	
	string s;
	while (cin >> s) {
		if (s == "DONE") break;
		if (s == "DIST") {
			int a, b;
			cin >> a >> b;
			--a;
			--b;
			int lc = lca(a, b, lift, D);
			cout << (C[a] + C[b] - 2 * C[lc]) << '\n';
		} else {
			int a, b, k;
			cin >> a >> b >> k;
			--a;
			--b;
			int lc = lca(a, b, lift, D);
			if (k > D[a] - D[lc]) {
				k = D[a] + D[b] + 1 - 2 * D[lc] - k;
				swap(a, b);
			} else --k;
			for (int i = 0; i < LOG; ++i) {
				if (((k>>i)&1)==1)
					a = lift[i][a];
			}
			cout << (a+1) << '\n';
		}
	}
	cout << flush;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int T;
	cin >> T;
	
	while (T--) solve();
	
	return 0;
}
