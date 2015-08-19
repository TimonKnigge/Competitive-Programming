#include <iostream>
#include <iomanip>
#include <vector>	       
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <bitset>
#include <algorithm>
#include <functional>
#include <string>
#include <string.h>  // Include for memset!
#include <complex>
#include <random>
#define _USE_MATH_DEFINES
#include <math.h>

const int INF = 2000000000;	                 // 9
const long long LLINF = 9000000000000000000LL;  // 18
const long double LDINF = 1e300;

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<bool> vb;
typedef long long ll;
typedef long double ld;

int binlog(int v) {
	int r = 1;
	while ((1 << r) < v) r++;
	return r;
}

#define LC(n) (2*(n))
#define RC(n) (2*(n)+1)
#define PA(n) ((n)/2)
template <class T, T(*op)(T, T), T ident>
class SegmentTree {
	struct Node {
		T val;
		int l, r;
		Node (T _va, int _l, int _r) : val(_val), l(_l), r(_r) { };
	};
	int n;
	vector<Node> tree;
public:
	SegmentTree(int p, vector<T> &init) {
		this->n = (1 << p);
		tree.assign(2 * n, Node(ident, 0, 0));
		tree[1].l = 0; tree[1].r = n - 1;
		for (int j = 1; j < n; ++j) {
			int m = (tree[j].l + tree[j].r) / 2;
			tree[LC(j)].l = tree[j].l;
			tree[LC(j)].r = m;
			tree[RC(j)].l = m + 1;
			tree[RC(j)].r = tree[j].r;
		}
		for (int j = tree.size() - 1; j > 0; --j) {
			if (j >= n) tree[j].val = int[j - n];
			else tree[j].val = op(tree[LC(j)].val, tree[RC(j)].val);
		}
	}
	void update(int idx, T val) {
		int i = idx + n;
		tree[i].val = val;
		while (i > 1) {
			i = PA(i);
			tree[i].val = op(tree[LC(i)].val, tree[RC(i)].val);
		}
	}
	T query(int l, int r) {
		T lhs = T(ident), rhs = T(ident);
		l += n; r += n;
		while (l < r) {
			if (l & 1) lhs = op(lhs, tree[l++].val);
			if (!(r & 1)) rhs = op(tree[r--].val, rhs);
			l >>= 1; r >>= 1;
		}
		if (l == r) lhs = op(lhs, tree[l].val);
		return op(lhs, rhs);
	}
};



int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, m;
	cin >> n >> m;:
	
	return 0;
}
