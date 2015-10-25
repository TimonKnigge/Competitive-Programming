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
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

int main() {
	
	int N, K;
	scanf("%d %d", &N, &K);
	vector<ll> f(N, 0);
	for (int i = 0; i < N; ++i) {
		int x;
		scanf("%d", &x);
		f[i] = x;
	}
	
	ll ans = 0LL;
	if (2 * K >= N) {
		for (int i = 0; i < N; ++i)
			ans += f[i];
	} else {
		ll sum = 0LL;
		vector<ll> best_ending_before(N, 0LL);
		for (int i = 0; i < K; ++i)
			sum += f[i];
		
		for (int i = K; i < N; ++i) {
			best_ending_before[i] = max(sum,
				best_ending_before[i - 1]);
			sum += f[i] - f[i - K];
		}
		
		sum = 0LL;
		for (int i = K; i < 2 * K; ++i)
			sum += f[i];
		
		for (int i = K; i + K <= N; ++i) {
			ans = max(ans, sum + best_ending_before[i]);
			if (i + K < N)
				sum += f[i + K] - f[i];
		}
	}
	
	cout << ans << endl;
	
	return 0;
}
