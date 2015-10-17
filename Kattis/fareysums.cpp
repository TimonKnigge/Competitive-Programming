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
	int T;
	scanf("%d", &T);
	
	const int LIM = 10001;
	vector<int> phi(LIM, 0LL);
	for (int i = LIM; i > 0; i--) {
		phi[i] = i;
	}
	for (int i = 2; i <= LIM; i++) {
		if (phi[i] == i) {
			for (int j = i; j <= LIM; j += i) {
      				phi[j] = phi[j] / i * (i - 1);
			}
    		}
	}
	
	for (int t = 1; t <= T; ++t) {
		int n ,x;
		scanf("%d %d", &x, &n);
		
		ll ans = 2;
		for (int i = 2; i <= n; ++i) {
			ans += phi[i] * 3;
		}
		
		int num = 2;
		if (!(ans&1)) { num /= 2; ans /= 2; }
		printf("%d %d/%d\n", x, ans, num);
	}
	
	return 0;
}
