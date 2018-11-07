#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
using ll = long long;
using ld = long double;
using ii = pair<ll, ll>;
using vi = vector<ll>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

template<class T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<class TIn, class TOut = null_type>
using order_tree = tree<TIn, TOut, less<TIn>, rb_tree_tag,
	tree_order_statistics_node_update>;

constexpr int INF = 2000000010;
constexpr ll LLINF = 9000000000000000010LL;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N;
	cin >> N;

	vvii E(N, vii());
	vi p(N), deg(N);
	for (int i = 0; i < N; ++i) {
		cin >> p[i];
		int l = (i + p[i]) % N, r = (N + i - p[i]) % N;
		if (l != r)
			E[l].push_back({r, i}),
			E[r].push_back({l, i}),
			deg[l]++, deg[r]++;
		else
			deg[l]++, E[l].push_back({l, i});
	}

	queue<int> q;
	for (int i = 0; i < N; ++i) if (deg[i] == 1) q.push(i);
	vi m(N, -1);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		if (deg[u] <= 0) continue;
		for (ii vw : E[u]) {
			int v = vw.first, id = vw.second;
			if (deg[v] == 0) continue;
			if (v != u) {
				deg[v]--;
				m[id] = u;
				if (deg[v] == 1) q.push(v);
			} else {
				m[id] = u;
			}
			break;
		}
		deg[u]--;
	}

//	cerr << "Result";
//	for (int v : m) cerr << ' ' << v;
//	cerr << endl;

	vi ord;
	for (int i = 0; i < N; ++i)
		if (m[i] < 0) {
			if (deg[(i + p[i]) % N] > 0)
				ord.push_back((i + p[i]) % N);
			else if (deg[(N + i - p[i]) % N] > 0)
				ord.push_back((N + i - p[i]) % N);
		}

	for (int u : ord) {
		if (deg[u] == 0) continue;
		int v = u;
//		cerr << "Searching from " << u << endl;
		while (true) {
			ii vw = {-1,-1};
			for (ii _vw : E[v])
				if (m[_vw.second] < 0) {
					vw = _vw;
					break;
				}
			if (vw.first < 0) break;
//			cerr << "Successor " << vw.first << endl;

			int w = vw.first;
			int id = vw.second;

			if (w == v) {
				m[id] = w;
				deg[v] = 0;
				break;
			} else {
				m[id] = v;
				deg[v] = 0;
				v = w;
			}
			if (v == u) break;
		}
	}

//	cerr << "Result";
//	for (int v : m) cerr << ' ' << v;
//	cerr << endl;

	bool ok = true;
	for (int v : m) ok = ok && v >= 0;
	if (ok) {
		for (int i = 0; i < N; ++i)
			cout << ((i+p[i])%N == m[i] ? 'L' : 'R');
		cout << endl;
	} else cout << "no dance" << endl;
	
	return 0;
}
