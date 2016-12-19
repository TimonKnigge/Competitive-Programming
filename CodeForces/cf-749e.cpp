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

#define WHAT(x) cerr << #x << ": " << x << endl

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	ll n;
	cin >> n;
	vi p(n, 0LL);
	for (ll &v : p) cin >> v, --v;
	
	FenwickTree<ll> ft(n + 3LL), ftj(n + 3LL);
	ll num = 0LL, n2 = n * (n + 1LL) / 2LL;
	ld ans = 0.0;
	for (ll _i = 0; _i < n; ++_i) {
		ll i = n - 1LL - _i;

		ll count_larger = ft.query(p[i] + 1LL, n);
		ll sum_larger = ftj.query(p[i] + 1LL, n);
		num += (i + 1LL) * (n * count_larger);
		num -= (i + 1LL) * (sum_larger);

		ll count_smaller = ft.query(p[i] + 1LL);
		ll sum_smaller = ftj.query(p[i] + 1LL);
		num += count_smaller * n2 * 2LL;
		num += (i + 1LL) * (sum_smaller);
		num -= (i + 1LL) * (n * count_smaller);
		
		if (num > 1e18) {
			ans += ld(num) / ld(2LL * n2);
			num = 0LL;
		}
		
		ft .update(p[i] + 1LL, 1LL);
		ftj.update(p[i] + 1LL, i);
	}
	
	ans += ld(num) / ld(2LL * n2);
	printf("%.12lf\n", double(ans));
	
	return 0;
}
