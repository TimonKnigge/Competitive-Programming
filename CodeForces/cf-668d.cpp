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

template <class T>
struct FenwickTree {		// use 1 based indices!!!
	int n; vector<T> tree;
	FenwickTree(int n) : n(n) { tree.assign(n + 1, 0); }
	T query(int l, int r) { return query(r) - query(l - 1); }
	T query(int r) {
		T s = 0;
		for(; r > 0; r -= (r & (-r))) s += tree[r];
		return s;
	}
	void update(int i, T v) {
		for(; i <= n; i += (i & (-i))) tree[i] += v;
	}
};

int main() {
	
	int N;
	scanf("%d", &N);
	
	// ((value,id),(type,time))
	vector<pair<ii, ii>> Q(N, {{0,0},{0,0}});
	vi ans(N, -1LL);
	set<int> times;
	for (int i = 0; i < N; ++i) {
		int a, t, x;
		scanf("%d %d %d", &a, &t, &x);
		Q[i] = {{x, i}, {a, t}};
		times.insert(t);
	}
	
	map<int, int> tid;
	int _id = 2;
	for (int t : times)
		tid.insert({t, ++_id});
	
	sort(Q.begin(), Q.end());
	
	FenwickTree<int> ft(N + 10);
	for (int l = 0, r = 0; l < N; l = r) {
		
		while (r < N && Q[l].first.first == Q[r].first.first) ++r;
		
		for (int i = l; i < r; ++i) {
			if (Q[i].second.first == 1) { // add
				ft.update(tid[Q[i].second.second], 1);
			} else if (Q[i].second.first == 2) { // remove
				ft.update(tid[Q[i].second.second], -1);
			} else {
				ans[Q[i].first.second] = 
					ft.query(tid[Q[i].second.second]);
			}
		}
		for (int i = l; i < r; ++i) {
			if (Q[i].second.first == 1) { // add
				ft.update(tid[Q[i].second.second], -1);
			} else if (Q[i].second.first == 2) { // remove
				ft.update(tid[Q[i].second.second], 1);
			}
		}
	}
	
	for (int i = 0; i < N; ++i)
		if (ans[i] >= 0)
			cout << ans[i] << '\n';
	
	return 0;
}
