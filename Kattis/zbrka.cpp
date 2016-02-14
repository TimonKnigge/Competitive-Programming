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
#include <complex>

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

ll MOD = 1e9 + 7;

ll st[2][10001];

int main() {
	
	int N, C;
	cin >> N >> C;
	
	st[0][0] = 1LL;
	
	for (int i = 1, u = 0; i < N; ++i) {
		u = min(u + i, C);
		ll rem = 0LL;
		for (int j = 0; j <= u; ++j) {
			rem = (rem + st[1^i&1][j]) % MOD;
			st[i&1][j] = rem;
			if (j - i >= 0) rem = (rem - st[1^i&1][j-i] + MOD) % MOD;
		}
	}
	
	cout << st[1^N&1][C] << endl;
	
	return 0;
}
