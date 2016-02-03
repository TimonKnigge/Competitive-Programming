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

using T = ii;
T op(T l, T r) { return max(l, r); }
T ident = {0, -1};

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

int main() {
	
	int N;
	scanf("%d", &N);
	
	vii invs(N, {0, 0});
	set<int> pts;
	for (int i = 0; i < N; ++i) {
		int A, B;
		scanf("%d %d", &A, &B);
		pts.insert(A);
		pts.insert(B);
		invs[i] = {A, B};
	}
//	cerr << "Read input"<<endl;
	map<int, int> idmap;
	vi pos;
	int id = 0;
	for (auto it = pts.begin(); it != pts.end(); ++it) {
		idmap.insert({*it, id});
		pos.push_back(*it);
		++id;
	}
	for (int i = 0; i < N; ++i) {
		invs[i].first = idmap[invs[i].first];
		invs[i].second = idmap[invs[i].second];
	}
//	cerr << "Remapped" << endl;
	
	int M = id;
	vvii entry(M, vii());
	for (int i = 0; i < N; ++i) {
		entry[invs[i].first].push_back({invs[i].second, i});
	}
//	cerr << "Stored entries"<< endl;
	
	int p = 1;
	while ((1<<p) < M) ++p;
	vii init(1<<p, ident);
	SegmentTree st(p, init);
//	cerr << "Constructed segtree." << endl;
	
	vii val(N, ident);
	for (int l = 0; l < M; ++l) {
		sort(entry[l].rbegin(), entry[l].rend());
		
		for (ii ev : entry[l]) {
			int r = ev.first;
			int i = ev.second;
			
			ii best = st.query(r, M - 1);
			val[i] = {1+best.first, best.second};
			ii nw = {1+best.first, i};
			st.update(r, max(st.query(r, r), nw));
		}
	}
//	cerr << "Sweeped" << endl;
	
	int i = 0;
	for (int j = 1; j < N; ++j) {
		if (val[j].first > val[i].first) i = j;
	}
//	cerr << "Constructed answer"<<endl;
	vii ans;
	while (i != -1) {
		ans.push_back({pos[invs[i].first], pos[invs[i].second]});
		i = val[i].second;
	}
	
	cout << int(ans.size()) << endl;
	for (int i = int(ans.size()) - 1; i >= 0; --i) {
		cout << ans[i].first << ' ' << ans[i].second << '\n';
	}
	cout << flush;
	
	return 0;
}
