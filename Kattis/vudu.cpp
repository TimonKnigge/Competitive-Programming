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
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N;
	cin >> N;
	
	vi A(N, 0LL);
	for (int i = 0; i < N; ++i) cin >> A[i];
	
	ll P;
	cin >> P;
	
	for (int i = 0; i < N; ++i) A[i] -= P;
	
	// #contiguous subsequences with sum >= 0?
	order_tree<ii, null_type> ot;
	ot.insert({0LL, -1LL});
	
	ll sum = 0LL, ans = 0LL;
	for (int i = 0; i < N; ++i) {
		sum += A[i];
		ans += ot.order_of_key({sum, LLINF});
		ot.insert({sum, i});
	}
	
	cout << ans << endl;
	
	return 0;
}
