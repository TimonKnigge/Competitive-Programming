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

// Order Statistics Tree
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class TIn, class TOut>
using order_tree = tree<
	TIn, TOut, less<TIn>, // key, value types. TOut can be null_type
	rb_tree_tag, tree_order_statistics_node_update>;
// find_by_order(int r) (0-based)
// order_of_key(TIn v)
// use key pair<Tin,int> {value, counter} for multiset/multimap

int main() {
	
	int N;
	scanf("%d", &N);
	
	vector<pair<ii, int> > Q(N, {{0LL, 0LL}, 0});
	for (int i = 0; i < N; ++i) {
		int l, r;
		scanf("%d %d", &l, &r);
		Q[i] = {{l - 1, r - 1}, i};
	}
	
	sort(Q.begin(), Q.end());
	
	vi ans(N, 0LL);
	order_tree<ll, ll> ot;
	for (int i = N - 1; i >= 0; --i) {
		
		ans[Q[i].second] = ot.order_of_key(Q[i].first.second);
		ot.insert({Q[i].first.second, Q[i].first.second});
	}
	
	for (int i = 0; i < N; ++i)
		cout << ans[i] << '\n';
	
	return 0;
}
