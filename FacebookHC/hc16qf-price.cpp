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
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

int main() {
	
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; ++t) {
		int N;
		scanf("%d", &N);
		
		ll P;
		vector<ll> B(N, 0LL);
		scanf("%lld", &P);
		for (int i = 0; i < N; ++i)
			scanf("%lld", &B[i]);
		
		ll ans = 0LL, sum = 0LL;
		for (int l = 0, r = -1; l < N; ++l) {
			if (r < l) {
				r = l;
				sum += B[l];
			}
			while (r + 1 < N && sum + B[r + 1] <= P) {
				sum += B[r + 1];
				r++;
			}
			
			if (sum <= P) {
				ans += ll(r - l + 1);
			}
			
			sum -= B[l];
		}
		
		printf("Case #%d: %lld\n", t, ans);
	}
	
	return 0;
}
