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

template <class T, const T&(*op)(const T&, const T&), T ident>
struct SegmentTree {
	int n; vector<T> tree;
	SegmentTree(int _n) : n(_n), tree(2 * n, ident) { }
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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N;
	cin >> N;
	vvi A(2, vi(N, 0LL));
	for (vi &v : A) for (ll &a : v) cin >> a;
	
	vvi P(2, vi(N, 0LL));
	for (int i = 0; i < 2; ++i) {
		P[0][0] = A[0][0];
		P[1][0] = A[1][0];
		for (int j = 1; j < N; ++j)
			P[0][j] = P[0][j - 1] + A[0][j],
			P[1][j] = P[1][j - 1] + A[1][j];
	}
	
	vi upper(N, -1LL), lower(N, -1LL), both(N, -1LL);
	map<ll, ll> u{{0LL, 0LL}}, l{{0LL, 0LL}}, b{{0LL, 0LL}};
	for (int i = 0; i < N; ++i) {
		if (u.find(-P[0][i]) != u.end())
			upper[i] = u[-P[0][i]];
		if (l.find(-P[1][i]) != l.end())
			lower[i] = l[-P[1][i]];
		if (b.find(-P[0][i] - P[1][i]) != b.end())
			both[i] = b[-P[0][i] - P[1][i]];
		u[-P[0][i]] = i + 1;
		l[-P[1][i]] = i + 1;
		b[-P[0][i] - P[1][i]] = i + 1;
	}
	
	for (int i = 0; i < N; ++i)
		cout << upper[i] << ' ' << lower[i] << ' ' << both[i] << endl;
	
	SegmentTree<ll, std::max, 0LL> st(N);
	
	return 0;
}
