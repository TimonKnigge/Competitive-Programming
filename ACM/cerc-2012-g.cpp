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
	SegmentTree(int n) : n(n), tree(2 * n, ident) {
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

int add(int l, int r) { return l + r; }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int T;
	cin >> T;
	while (T--) {
	
	int N, K;
	cin >> N >> K;
	
	vector<pair<ii, ll> > Q(N, {{0LL, 0LL}, 0LL});
	vi X(N, 0LL);
	for (int i = 0; i < N; ++i) {
		cin >> Q[i].first.second >> Q[i].first.first >> Q[i].second;
		X[i] = Q[i].first.second;
		--Q[i].second;
	}
	
	sort(X.begin(), X.end());
	map<ll, int> coordmap;
	for (int i = 0, c = 0; i < int(X.size()); ++i) {
		if (i > 0 && X[i - 1] == X[i]) continue;
		coordmap.insert({X[i], c});
//		cerr << "coordmap[" << X[i] << "] = " << c << endl;
		++c;
	}
	
//	cerr << "Built coord map" << endl;
	
	int ans = 0;
	sort(Q.begin(), Q.end());
	vector<set<int> > positions(K, set<int>());
	SegmentTree<int, add, 0> st(coordmap.size());
	
	for (int i = 0; i < K; ++i) {
		positions[i].insert(-1);
		positions[i].insert(coordmap.size());
	}
	
	int l = 0, r = 0;
	while (l < N) {
		while (r < N && Q[r].first.first == Q[l].first.first)
			++r;
//		cerr << "Solving [" << l << ", " << r << "]" << endl;
		
		for (int i = l; i < r; ++i) {
			// compute answer for i
			int xi = coordmap[Q[i].first.second], c = Q[i].second;
			if (positions[c].find(xi) != positions[c].end())
				continue;
			auto ub = positions[c].upper_bound(xi);
			auto lb = ub; --lb;
			int lb_val = *lb;
			int ub_val = *ub;
//			cerr << "For " << Q[i].first.second << "," << Q[i].first.first << " querying [" << lb_val+1 << ", " << ub_val-1 << "] (color " << c << ")" << endl;
			if (ub_val - lb_val > 1)
				ans = max(ans, st.query(lb_val+1, ub_val-1));
		}
		
		for (int i = l; i < r; ++i) {
			int xi = coordmap[Q[i].first.second], c = Q[i].second;
			st.update(xi, st.query(xi, xi) + 1);
			positions[c].insert(xi);
		}
		
		l = r;
	}
	
	// Query unbounded rectangles
	for (size_t c = 0; c < positions.size(); ++c) {
		for (auto it1 = positions[c].begin(),
			  it2 = positions[c].begin();
			  it1 != positions[c].end();) {
			++it1;
			if (it1 == positions[c].end()) break;
			if ((*it1) - (*it2) > 1)
				ans = max(ans, st.query(1 + (*it2), -1 + (*it1)));
			++it2;
		}
	}
	
	cout << ans << endl;
	
	}
	
	return 0;
}
