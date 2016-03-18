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

int dfs(int u, int p, vvi &E, vi &P1, vi &P2, int N, int M, int K, bool &pos) {
	
	if ((u < N + K && u >= N) || (u >= N + K + M)) {
		// u is a leaf
		P1[u] = p;
		return u;
	}
	
	vector<int> leaves_up;
	for (ll v : E[u]) {
		if (p == v) continue;
		int res = dfs(v, u, E, P1, P2, N, M, K, pos);
		if (res != -1)
			leaves_up.push_back(res);
	}
	
	if (leaves_up.size() == 0 || leaves_up.size() > 2) {
		pos = false;
		return -1;
	}
	
	P1[u] = leaves_up[0];
	if (leaves_up.size() > 1) {
		P2[u] = leaves_up[1];
		return -1;
	} else {
		P2[u] = p;
		return u;
	}
}

void solve() {
	int K, N, M;
	cin >> K >> N >> M;
	
	vvi E(N + M + K + K, vi());
	
	for (int i = 0; i < N + K - 1; ++i) {
		string a, b;
		cin >> a >> b >> ws;
		int l = 0, r = 0;
		if (a[1] == 'S') l += N;
		if (b[1] == 'S') r += N;
		int numa = 0, numb = 0;
		for (size_t j = 2; j < a.size(); ++j)
			numa = 10 * numa + (a[j] - '0');
		for (size_t j = 2; j < b.size(); ++j)
			numb = 10 * numb + (b[j] - '0');
		l += numa;
		r += numb;
		--l;
		--r;
		E[l].push_back(r);
		E[r].push_back(l);
	}
	for (int i = 0; i < M + K - 1; ++i) {
		string a, b;
		cin >> a >> b >> ws;
		int l = 0, r = 0;
		if (a[1] == 'S') l += M;
		if (b[1] == 'S') r += M;
		int numa = 0, numb = 0;
		for (size_t j = 2; j < a.size(); ++j)
			numa = 10 * numa + (a[j] - '0');
		for (size_t j = 2; j < b.size(); ++j)
			numb = 10 * numb + (b[j] - '0');
		l += numa;
		r += numb;
		--l;
		--r;
		E[N + K + l].push_back(N + K + r);
		E[N + K + r].push_back(N + K + l);
	}
	
	vi P1(N + M + K + K, -1LL), P2(N + M + K + K, -1LL);
	
	bool possible = true;
	dfs(0, -1, E, P1, P2, N, M, K, possible);
	dfs(N+K, -1, E, P1, P2, N, M, K, possible);
	
	for (int k = 0; k < K; ++k) {
		string a, b;
		cin >> a >> b >> ws;
		if (a[0] == 'B') swap(a, b);
		int l = N, r = M;
		int numa = 0, numb = 0;
		for (size_t j = 2; j < a.size(); ++j)
			numa = 10 * numa + (a[j] - '0');
		for (size_t j = 2; j < b.size(); ++j)
			numb = 10 * numb + (b[j] - '0');
		l += numa;
		r += numb;
		--l;
		--r;
		P2[l] = r + N + K;
		P2[r + N + K] = l;
	}
	
	vi ans;
	if (possible) {
		int u = 0, prev = -1;
		while (u != 0 || prev == -1) {
			ans.push_back(u);
			if (P1[u] != prev) {
				prev = u;
				u = P1[u];
			} else {
				prev = u;
				u = P2[u];
			}
		}
	}
	
	possible = possible && (ans.size() == P1.size());
	if (!possible) cout << "NO\n";
	else {
		cout << "YES";
		for (size_t i = 0; i < ans.size(); ++i) {
			cout << " ";
			ll v = ans[i];
			if (v < N) {
				cout << "AP";
			} else if (v < N + K) {
				cout << "AS";
				v -= N;
			} else if (v < N + K + M) {
				cout << "BP";
				v -= N + K;
			} else {
				cout << "BS";
				v -= N + K + M;
			}
			ll numc = 1 + v;
			cout << numc;
		}
		cout << '\n';
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int T;
	cin >> T;
	while (T--) solve();
	
	return 0;
}
