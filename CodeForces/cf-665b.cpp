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
	
	int N, M, K;
	scanf("%d %d %d", &N, &M, &K);
	
	int free = 0;
	vector<int> pos(K, 0);
	order_tree<int, null_type> ot;
	
	for (int i = 0,v; i < K; ++i) {
		scanf("%d", &v);
		pos[v - 1] = i + 1;
		ot.insert(v);
	}
	
	ll ans = 0;
	while (N--) {
		for (int i = 0, v; i < M; ++i) {
			scanf("%d", &v);
			ans += ll(1 + ot.order_of_key(pos[v - 1]));
			ot.erase(pos[v - 1]);
			pos[v - 1] = free--;
			ot.insert(pos[v - 1]);
		}
	}
	
	cout << ans << endl;
	
	return 0;
}
