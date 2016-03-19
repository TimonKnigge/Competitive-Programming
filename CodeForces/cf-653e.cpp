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

template <class T, T(*op)(T, T), T ident>
struct SegmentTree {
	int n; vector<T> tree;
	SegmentTree(vector<T> &init) : n(init.size()), tree(2 * n, ident) {
		copy(init.begin(), init.end(), tree.begin() + n);
		for (int j = n - 1; j > 0; --j)
			tree[j] = op(tree[2*j], tree[2*j+1]);
	}
	void update(int i, T val) {
		for (tree[i+n] = val, i = (i+n)/2; i > 0; i /= 2)
			tree[i] = op(tree[2*i], tree[2*i+1]);
	}
	T query(int l, int r) {
		T lhs = T(ident), rhs = T(ident);
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (  l&1 ) lhs = op(lhs, tree[l++]);
			if (!(r&1)) rhs = op(tree[r--], rhs);
		}
		return op(l == r ? op(lhs, tree[l]) : lhs, rhs);
	}
};

ll mx(ll l, ll r) { return min(l, r); }

void dfs(int i, vvi &E, vi &comp, SegmentTree<ll, mx, LLINF> &st, int id) {
	comp[i] = id;
	st.update(i, LLINF);
	E[i].push_back(-1LL);
	E[i].push_back(ll(E.size()));
	sort(E[i].begin(), E[i].end());
	for (size_t j = 0; j + 1 < E[i].size(); ++j) {
		if (E[i][j+1] - E[i][j] <= 1) continue;
		ll mn;
		while ((mn = st.query(E[i][j] + 1, E[i][j+1] - 1)) < LLINF) {
			dfs(mn, E, comp, st, id);
		}
	}
}

int main() {
	
	int N, M, K;
	scanf("%d %d %d", &N, &M, &K);
	
	vvi E(N, vi());
	for (int j = 0; j < M; ++j) {
		int a, b;
		scanf("%d %d", &a, &b);
		--a; --b;
		if (a > b) swap(a, b);
		E[a].push_back(b);
		E[b].push_back(a);
	}
	
	vi init(N, LLINF);
	for (int i = 1; i < N; ++i) init[i] = i;
	SegmentTree<ll, mx, LLINF> st(init);
	
	sort(E[0].begin(), E[0].end());
	vi comp(N, -1);
	comp[0] = 0;
	size_t j = 0;
	for (int i = 1; i < N; ++i) {
		if (j < E[0].size() && E[0][j] == i) {
			++j;
			continue;
		}
		if (comp[i] != -1LL) continue;
		dfs(i, E, comp, st, i);
	}
	
	bool unreachable = false;
	set<int> comps;
	for (int i = 1; i < N; ++i) {
		unreachable = unreachable || (comp[i] == -1);
		comps.insert(comp[i]);
	}
	
	int C = int(comps.size()), V = N - 1 - int(E[0].size());

//	cerr << "unreachable: " << unreachable << endl;
//	cerr << "C: " << C << ", V: " << V << endl;	
	
	if (unreachable) {
		cout << "impossible" << endl;
		return 0;
	}
	
	// we have C distinct components adjacent to 0, and V vertices
	if (C > K || V < K) {
		cout << "impossible" << endl;
	} else	cout << "possible" << endl;
	
	return 0;
}
