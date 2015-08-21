#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef tree<int, int, less<int>, rb_tree_tag, tree_order_statistics_node_update> map_os;

inline int LC(int n) { return 2 * n; }
inline int RC(int n) { return 2 * n + 1; }
inline int PA(int n) { return n / 2; }
class SegmentTree {
	struct Node {
		int v;
		map_os st;
		int l, r;
		Node(int _l, int _r) : v(-1), l(_l), r(_r) { };
	};
	int n;
	vector<Node> tree;
public:
	SegmentTree(int p) {
		this->n = (1 << p);
		tree.assign(2 * n, Node(0, 0));
		tree[1].l = 0; tree[1].r = n - 1;
		for (int j = 1; j < n; ++j) {
			int m = (tree[j].l + tree[j].r) / 2;
			tree[LC(j)].l = tree[j].l;
			tree[LC(j)].r = m;
			tree[RC(j)].l = m + 1;
			tree[RC(j)].r = tree[j].r;
		}
	}
	void update(int idx, int v) {
		int i = idx + n;
		tree[i].v = v;
		tree[i].st.insert({v, v});
		while (i > 1) {
			i = PA(i);
			tree[i].st.insert({v, v});
		}
	}

	ll query(int l, int r, int M) {
		ll ret = 0;
		l += n; r += n;
		while (l < r) {
			if (l & 1) {
				ret += tree[l].st.order_of_key(M);
				l++;
			}
			if (!(r & 1)) {
				ret += tree[r].st.order_of_key(M);
				r--;
			}
			l >>= 1; r >>= 1;
		}
		if (l == r) ret += tree[l].st.order_of_key(M);
		return ret;
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	while (true) {
		int n;
		cin >> n;
		if (n == 0) break;
		
		vector<int> p_id(n + 1, -1);
		for (int i = 1; i <= n; ++i) {
			int x;
			cin >> x;
			p_id[x] = i;
		}
		
		vector<int> vlnr(n, -1);
		for (int i = 0; i < n; ++i) {
			int x; cin >> x;
			vlnr[i] = p_id[x];
		}

		vector<int> inboom(n + 1, -1);
		for (int i = 0; i < n; ++i) {
			int x; cin >> x;
			x = p_id[x];
			inboom[x] = i;
		}
		
		int p = 1;
		while ((1LL << p) < n) p++;
		SegmentTree st(p);
		ll ans = 0LL;
		for (int i = 0; i < n; ++i) {
			int x = vlnr[i];
			st.update(inboom[x], x);
			ans += st.query(0, inboom[x], x);
		}

		cout << ans << endl;
	}
	
	return 0;
}
