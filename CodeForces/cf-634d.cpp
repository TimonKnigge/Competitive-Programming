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

ll mmin(ll l, ll r) { return l < r ? l : r; }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	ll D, N;
	int M;
	cin >> D >> N >> M;
	
	vii XP(M + 1, {0LL, 0LL});
	for (int i = 1; i <= M; ++i)
		cin >> XP[i].first >> XP[i].second;
	
	++M;
	++M;
	XP.push_back({D, 0LL});
	
	assert(M == int(XP.size()));
	
	sort(XP.begin(), XP.end());
	vi X(M, 0LL), P(M, 0LL);
	for (int i = 0; i < M; ++i) {
		X[i] = XP[i].first;
		P[i] = XP[i].second;
	}
	
	bool pos = true;
	for (int i = 1; i < M; ++i)
		pos = pos && X[i] - X[i-1] <= N;
	if (!pos) {
		cout << -1 << endl;
		return 0;
	}
	
	SegmentTree<ll, mmin, LLINF> st(P);
	
	int p = 0;
	ll fuel = N, cost = 0LL;
	while (p != M - 1) {
		int l = p+1, r = M - 1;
		while (l < r) {
			int m = (l+r+1)/2;
			if (X[m] - X[p] > N)	r = m-1;
			else			l = m;
		}
		// we can reach [p+1, R]
		int R = l;
		ll mn = st.query(p+1, R);
		if (mn < P[p]) {
			l = p+1; r = R;
			while (l < r) {
				int m = (l+r) / 2;
				if (st.query(p+1, m) < P[p])	r = m;
				else				l = m + 1;
			}
			// go to l
			cost += max(0LL, X[l] - X[p] - fuel) * P[p];
			fuel += max(0LL, X[l] - X[p] - fuel);

		} else {
			l = p+1; r = R;
			while (l < r) {
				int m = (l+r) / 2;
				if (st.query(p+1, m) > mn) l = m + 1;
				else			   r = m;
			}
			cost += (N - fuel) * P[p];
			fuel = N;
		}
		assert(p < l);
		fuel -= X[l] - X[p];
		p = l;
	}
	
	cout << cost << endl;
	
	return 0;
}
