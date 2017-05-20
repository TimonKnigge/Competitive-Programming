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
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
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
using map_os = tree<int, int, less<int>, rb_tree_tag, tree_order_statistics_node_update>;

struct SegmentTree {
	int n; vector<map_os> tree;
	SegmentTree(int _n) : n(_n), tree(2 * n, map_os()) { }
	void update(int i, int val) {
		for (tree[i+n].insert({val, val}), i = (i+n)/2; i > 0; i /= 2)
			tree[i].insert({val, val});
	}
	ll query(int l, int r, int M) {
		ll ret = 0LL;
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (  l&1 ) ret += tree[l++].order_of_key(M);
			if (!(r&1)) ret += tree[r--].order_of_key(M);
		}
		if (l == r) ret += tree[l].order_of_key(M);
		return ret;
	}
};

int main() {
	ifstream fin("friendcross.in");
	ofstream fout("friendcross.out");
	
	int N, K;
	fin >> N >> K;
	vi posof(N, 0LL), qosof(N, 0LL);
	for (int i = 0, v; i < N; ++i) fin >> v, posof[v-1] = i;
	for (int i = 0, v; i < N; ++i) fin >> v, qosof[v-1] = i;
	
	ll ans = 0LL;
	SegmentTree st(N);
	map_os pmap, qmap;
	for (int i = 0; i < N; ++i) {
		ans += pmap.order_of_key(posof[i])
		     + qmap.order_of_key(qosof[i])
		     - st.query(0, posof[i], qosof[i]) * 2LL;
		if (i >= K) {
			st.update(posof[i-K], qosof[i-K]);
			pmap.insert({posof[i-K], 0});
			qmap.insert({qosof[i-K], 0});
		}
	}
	
	fout << ans << endl;
	
	return 0;
}
