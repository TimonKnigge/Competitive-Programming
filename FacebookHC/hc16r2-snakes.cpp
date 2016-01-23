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

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

using T = ll;
T ident = 0;
T op(T l, T r) { return max(l, r); }

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

ll mod(ll a, ll b) {
	return (((a%b)+b)%b);
}

int main() {
	
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; ++t) {
		int N;
		scanf("%d", &N);
		
		vector<pair<ll, ll> > XH;
		for (int i = 0; i < N; ++i) {
			int x, h;
			scanf("%d %d", &x, &h);
			XH.push_back({x, h});
		}
		sort(XH.begin(), XH.end());
		
		vector<ll> H(N, 0LL);
		for (int i = 0; i < N; ++i) H[i] = XH[i].second;
		vector<pair<ll, int> > Hp;
		for (int i = 0; i < N; ++i) Hp.push_back({H[i], i});
		sort(Hp.begin(), Hp.end());
		
		int r = 1;
		while ((1<<r) < N) ++r;
		while (H.size() < (1<<r)) H.push_back(0LL);
		SegmentTree st(r, H);
		
		ll ans = 0LL;
		ll MOD = 1e9 + 7;
		int j = 0;
		while (j < N) {
			int n = j;
			vi inds;
			while (n < N && Hp[j].first == Hp[n].first) {
				inds.push_back(Hp[n].second);
				++n;
			}
			sort(inds.begin(), inds.end());
			ll Height = Hp[j].first;
			j = n;
			
			// inds is a series of sorted indices
			// of ladders of equal height
			int l = 0;
			while (l < int(inds.size())) {
				int r = l;
				while (r + 1 < int(inds.size()) && 
					st.query(inds[l], inds[r+1]) == Height)
					++r;
				
				// [l, r] is maximal wrt no obstructions
				vector<ll> Xs;
				for (int k = l; k <= r; ++k) {
					Xs.push_back(XH[inds[k]].first);
				}
				
				ll qsum = 0LL;
				int cnt = int(Xs.size());
				for (int k = 0; k < cnt; ++k) {
					ll add1 = ((cnt-1)*mod(Xs[k]*Xs[k],MOD)) % MOD;
					ll add2 = mod(-2LL * qsum * Xs[k], MOD);
					qsum = (qsum+Xs[k])% MOD;
					ans = mod(ans+add1+add2,MOD);
				}
				
				l = r + 1;
			}
		}
		cout << "Case #" << t << ": " << ans << endl;
	}
	
	return 0;
}
