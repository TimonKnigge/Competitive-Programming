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
#include <cassert>

const int INF = 2000000000;                     // 9
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

int find_p(int n) { 
   int r = 1;
   while ((1LL << r) < n) r++;
   return r;
}

//SEGTREE
#define LC(n) (2 * (n))
#define RC(n) (2 * (n) + 1)
#define PA(n) ((n) / 2)
template <class T, T(*op)(T, T), T ident>
class SegmentTree {
	struct Node {
		T val;
		int l, r;
		Node(T _val, int _l, int _r) : val(_val), l(_l), r(_r) { };
	};
	int n;
	vector<Node> tree;

public:
	SegmentTree(int p, vector<T>& init) { // The segment tree will support 2^p leafs
		this->n = (1 << p);
		tree.assign(2 * n, Node(ident, 0, 0));
		tree[1].l = 0; tree[1].r = n - 1;
		for (int j = 1; j < n; ++j) {
assert(RC(j) < tree.size());
			int m = (tree[j].l + tree[j].r) / 2;
			tree[LC(j)].l = tree[j].l;
			tree[LC(j)].r = m;
			tree[RC(j)].l = m + 1;
			tree[RC(j)].r = tree[j].r;
		}
		for (int j = tree.size() - 1; j > 0; --j) {
			if (j >= n) {
				assert(j < tree.size() && j - n >= 0 && j - n < init.size());
				tree[j].val = init[j - n];
			}
			else
			{	
				assert(j > 0 && RC(j) < tree.size());
				tree[j].val = op(tree[LC(j)].val, tree[RC(j)].val);
				assert(j > 0 && RC(j) < tree.size());
			}
		}
	}

	void update(int idx, T val) {
		int i = idx + n;
                assert(i > 0 && i < tree.size());
		tree[i].val = val;
		while (i > 1) {
			i = PA(i);
                        assert(i > 0 && RC(i) < tree.size());
			tree[i].val = op(tree[LC(i)].val, tree[RC(i)].val);
		}
	}

	T query(int l, int r) {
		T lhs = T(ident), rhs = T(ident);
		l += n; r += n;
		while (l < r) {
                        assert(l > 0 && r > 0 && l < tree.size() && r < tree.size());
			if (l & 1) lhs = op(lhs, tree[l++].val);
			if (!(r & 1)) rhs = op(tree[r--].val, rhs);
			l >>= 1; r >>= 1;
		}
		assert(l > 0 && l < tree.size());
		if (l == r) lhs = op(lhs, tree[l].val);
		return op(lhs, rhs);
	}
};
//-SEGTREE

int mymax(int l, int r) {
    if (r != -1) return r; else return l;
}

int possible_placements(int le, int sz) {
    le--;
    int ret = 0;
    if (le >= sz) { le -= sz; ret++; }
    ret += le / (sz + 1);
    return ret;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k, a, m;
    cin >> n >> k >> a >> m;
    vector<int> _x(m, 0);
    for (int i = 0; i < m; ++i) cin >> _x[i];
    
    vector<int> startx(1, -1), leng(1, n + 1), sup(1, 0);
    sup[0] = possible_placements(n+1, a);
    // assert k <= sup[0]

    int no = sup[0], p = 1 + find_p(n);
    vector<int> init(1 << p, -1);
    SegmentTree<int, mymax, -1> segtree(p, init);
    segtree.update(0, 0);
    
    int ans = -1;
    for (int i = 0; i < m; ++i) {
        int x = _x[i] - 1;
        int ix = segtree.query(0, x), newix = startx.size();
	assert(ix >= 0 && ix < startx.size() && newix >= 0 && newix <= n);
        startx.push_back(x);
        leng.push_back(startx[ix] + leng[ix] - x);
        leng[ix] -= leng[newix];
        no -= sup[ix];
        sup[ix] = possible_placements(leng[ix], a);
        sup.push_back(possible_placements(leng[newix], a));
        no += sup[ix] + sup[newix];
        segtree.update(x, newix);
        
        if (no < k) { ans = i + 1; break; }
    }

    cout << ans << endl;
    
    return 0;
}
