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
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

constexpr int INF = 2000000000;
constexpr ll LLINF = 9000000000000000000;

template <class T, T(*op)(T, T), T ident>
struct SegmentTree {
	struct Node {
		T val;
		int l, r;
		Node(T _val, int _l, int _r) : val(_val), l(_l), r(_r) { };
	};
	int n;
	vector<Node> tree;
	SegmentTree(int p, vector<T> &init) : n(1 << p) { // Needs 2^p leafs
		tree.assign(2 * n, Node(ident, 0, n - 1));
		for (int j = 1; j < n; ++j) {
			int m = (tree[j].l + tree[j].r) / 2;
			tree[2*j].l = tree[j].l;
			tree[2*j].r = m;
			tree[2*j+1].l = m + 1;
			tree[2*j+1].r = tree[j].r;
		}
		for (int j = 2 * n - 1; j > 0; --j) {
			if (j >= n) tree[j].val = init[j - n];
			else tree[j].val = op(tree[2*j].val, tree[2*j+1].val);
		}
	}
	void update(int i, T val) {
		for (tree[i+n].val = val, i = (i+n)/2; i > 0; i /= 2)
			tree[i].val = op(tree[2*i].val, tree[2*i+1].val);
	}
	T query(int l, int r) {
		T lhs = T(ident), rhs = T(ident);
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if   (l&1)  lhs = op(lhs, tree[l++].val);
			if (!(r&1)) rhs = op(tree[r--].val, rhs);
		}
		return op(l == r ? op(lhs, tree[l].val) : lhs, rhs);
	}
};

int mmax(int l, int r) { return l < r ? r : l; }

int find(int v, vi &a, int l, int r) {
	while (l < r) {
		int m = (l + r) / 2;
		if (a[m] < v)	l = m + 1;
		else		r = m;
	}
	return l;
}

int main() {
	
	bool e = false;
	while (true) {
		int N;
		scanf("%d", &N);
		
		if (N == 0) break;
		
		if (e)	printf("\n");
		else	e = true;
		
		vi Y(N, 0), R(N, 0);
		for (int i = 0; i < N; ++i)
			scanf("%d %d", &Y[i], &R[i]);
	
		int p = 1;
		while ((1 << p) < N) ++p;
		while (R.size() < (1<<p)) R.push_back(0);
		
		SegmentTree<int, mmax, 0> st(p, R);
		
		int M;
		scanf("%d", &M);
		while (M--) {
			int y, x;
			scanf("%d %d", &y, &x);
			
			if (Y[0] >= x || Y[N-1] <= y) {
				printf("maybe\n");
				continue;
			}
			
			int yp = find(y, Y, 0, N - 1);
			int xp = find(x, Y, 0, N - 1);
			// Smallest i such that Y[i] >=
			
			if (Y[xp] > x) --xp;
			if (yp >= xp) {
				printf("maybe\n");
				continue;
			}
			
			int YGX = (Y[yp] != y) || (Y[xp] != x) || (R[yp] >= R[xp]);
			if (!YGX) {
				printf("false\n");
				continue;
			}
			int lq = (Y[yp] == y ? yp + 1 : yp);
			int rq = (Y[xp] == x ? xp - 1 : xp);
			int mx = (yp <= xp ? st.query(lq, rq) : 0);
			
			if (Y[xp] == x && R[xp] <= mx) {
				printf("false\n");
				continue;
			}
			if (Y[yp] == y && R[yp] <= mx) {
				printf("false\n");
				continue;
			}
			
			if (Y[xp] == x && Y[yp] == y && xp - yp == x - y) {
				printf("true\n");
			} else {
				printf("maybe\n");
			}
		}
	}
	
	return 0;
}
