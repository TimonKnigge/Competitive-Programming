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

template<class T>
T mmin(T l, T r) { return l < r ? l : r; }
template<class T>
T mmax(T l, T r) { return l < r ? r : l; }

int main() {
	
	int N, K;
	scanf("%d %d", &N, &K);
	
	vector<int> V(N, 0LL), C(N, 0LL);
	for (int i = 0; i < N; ++i)
		scanf("%d", &V[i]), V[i] *= 100;
	for (int i = 0; i < N; ++i)
		scanf("%d", &C[i]);
	
	vector<int> Z(N, 0LL);
	SegmentTree<int, mmin, INF> cst(C);
	SegmentTree<int, mmax, 0  > vst(V);
	
	for (int i = 0; i < N; ++i) {
		int l = i, r = N - 1;
		while (l < r) {
			int m = (l + r) / 2;
			if (cst.query(i, m) < vst.query(i, m))
				r = m;
			else	l = m + 1;
		}
		if (l > i) --l;
		for (int j = 0; l + j < N && j < 2; ++j)
			Z[i] = max(Z[i], min(cst.query(i, l+j), vst.query(i, l+j)));
	}
	
	sort(Z.begin(), Z.end());
	
	ld ans = 0.0;
	ld fact = ld(K) / ld(N);
	for (
		int i = 0, U = N - K, L = N - 1;
		i < N - K + 1 && abs(fact) > 1e-9;
		++i, --U, --L) {
		ans += fact * Z[i];
		if (L > 0) {
			fact *= U;
			fact /= L;
		} else	fact = 0.0;
	}
	
	printf("%.7lf\n", double(ans));
	
	return 0;
}
