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

ll sq(int v) {
	return ll(v) * ll(v);
}

int main() {
	
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; ++t) {
		int N;
		scanf("%d", &N);
		vi X(N, 0), Y(N, 0);
		for (int i = 0; i < N; ++i) {
			scanf("%d %d", &X[i], &Y[i]);
		}
		
		ll ans = 0LL;
		for (int i = 0; i < N; ++i) {
			map<ll, int> mp;
			for (int j = 0; j < N; ++j) {
				ll d = sq(X[i] - X[j]) + sq(Y[i] - Y[j]);
				auto it = mp.find(d);
				if (it == mp.end()) mp.insert({d, 1});
				else it->second++;
			}
			for (auto it : mp) {
				ll v = it.second;
				ans += (v * (v - 1)) / 2;
			}
		}
		
		printf("Case #%d: %lld\n", t, ans);
	}
	
	return 0;
}
