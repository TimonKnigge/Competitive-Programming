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
	T query(int l, int r) { return (l <= r ?  query(r) - query(l - 1) : 0LL); }
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
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	ll n, k;
	cin >> n >> k;
	if (k > n/2) k = n-k;
	
	FenwickTree<ll> ft(n+10LL);
	ll V = n, E = n;
	for (ll i = 0; i < n; ++i) {
		ll l = (k*i) % n, r = (k*i+k) % n;
		E++;

		ll intersections = (l < r ?
			 ft.query(l + 2LL, r) :
			(ft.query(1LL, r) + ft.query(l+2LL, n)));
		V += intersections;
		E += 2LL * intersections;
		ft.update(l+1, 1LL);
		ft.update(r+1, 1LL);
		
		cout << (1LL + E - V) << (i + 1 == n ? '\n' : ' ');
	}
	
	return 0;
}
