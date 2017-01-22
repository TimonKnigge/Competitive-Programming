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
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N;
	cin >> N;
	
	vi P(N, 0LL), B(N, 0LL);
	for (ll &v : P) cin >> v, --v;
	for (ll &v : B) cin >> v;
	
	int cycs = 0;
	vb vis(N, false);
	for (int i = 0; i < N; ++i) {
		if (vis[i]) continue;
		++cycs;
		int j = i;
		while (!vis[j]) { vis[j] = true; j = P[j]; }
	}
	if (cycs == 1) cycs--;
	
	int ans = cycs + int(accumulate(B.begin(), B.end(), 1LL) % 2LL);
	cout << ans << endl;
	
	return 0;
}
