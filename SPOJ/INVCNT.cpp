#include <cstdio>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
using order_tree =
	tree<
	int, int, less<int>, 
	rb_tree_tag, tree_order_statistics_node_update>;

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		int n;
		scanf("%d", &n);
		
		order_tree ot;
		long long ans = 0LL;
		for (int i = 0; i < n; ++i) {
			int x;
			scanf("%d", &x);
			x *= -1;
			ans += ot.order_of_key(x);
			ot.insert({x, x});
		}
		
		printf("%lld\n", ans);
	}
	
	return 0;
}
