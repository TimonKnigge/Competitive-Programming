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

int main() {
	
	int N, Q;
	scanf("%d %d", &N, &Q);
	
	ll ep = 0LL, op = 1LL;
	
	while (Q--) {
		int c;
		scanf("%d", &c);
		switch (c) {
		case 1:
			int x;
			scanf("%d", &x);
			ep += x;
			op += x;
			break;
		case 2:
			if (ep&1) {
				--ep;
				++op;
			} else {
				++ep;
				--op;
			}
			break;
		}
		ep = (ep + 2 * N) % N;
		op = (op + 2 * N) % N;
	}
	
	vi ans(N, 0LL);
	for (ll id = 1, pos = ep; id <= N; id += 2, pos += 2)
		ans[pos % N] = id;
	for (ll id = 2, pos = op; id <= N; id += 2, pos += 2)
		ans[pos % N] = id;
	
	for (int i = 0; i < N; ++i)
		cout << ans[i] << " \n"[i + 1 == N];
	
	return 0;
}
