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
	ifstream fin("nocross.in");
	ofstream fout("nocross.out");
	
	int N;
	fin >> N;
	vi posof(N, 0LL);
	for (int i = 0, v; i < N; ++i) {
		fin >> v;
		posof[v - 1] = i;
	}
	
	SegmentTree<ll, max, 0LL> st(N);
	vi positions(9, 0LL);
	for (int i = 0, v; i < N; ++i) {
		fin >> v;
		--v;
		for (int w = v - 4, j = 0; w <= v + 4; ++w, ++j) {
			if (w < 0 || w >= N)
				positions[j] = -LLINF;
			else	positions[j] = posof[w];
		}
		sort(positions.rbegin(), positions.rend());
		for (int j = 0; j < 9 && positions[j] >= 0; ++j) {
			int p = positions[j];
			st.update(p, max(st.query(p, p),
					 1LL + st.query(0, p - 1)));
		}
	}
	
	fout << st.query(0, N - 1) << endl;
	
	return 0;
}
