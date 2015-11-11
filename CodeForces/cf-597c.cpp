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

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
using ll = long long;
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

template <class T>
class FenwickTree {
private:
	vector<T> tree;
	int n;
public:
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
	int n, k;
	scanf("%d %d", &n, &k);
	
	vi a(n, 0);
	for (int i = 0; i < n; ++i)
		scanf("%d", &a[i]);
	
	if (k == 0) {
		cout << n << endl;
		return 0;
	}

	vector<FenwickTree<ll> > otree(k, FenwickTree<ll>(n));
	ll ans = 0LL;
	for (int i = 0; i < n; ++i) {
		for (int t = k; t >= 0; --t) {
			ll q = (t > 0 ? otree[t - 1].query(a[i]) : 1);
//			cerr << i << ' ' << t << ' '<<q<<endl;
			if (t < k)
				otree[t].update(a[i], q);
			else	ans += q;
		}
	}
	
	cout << ans << endl;
	
	return 0;
}
