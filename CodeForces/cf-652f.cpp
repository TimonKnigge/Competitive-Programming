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

// Brings v into range [1, M]
void fix_mod(ll &v, ll M) {
	v = ((v - 1) % M + M) % M + 1;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N;
	ll M, T;
	cin >> N >> M >> T;
	
	// tuples {starting position of ant i, i}
	vii Si(N, {0LL, 0LL});
	// final positions
	vi pos(N, 0LL);
	
	ll shift = 0;
	for (int i = 0; i < N; ++i) {
		ll x;
		char c;
		cin >> x >> c;
		
		ll slope = (c == 'L' ? -1 : 1), ic = (slope == 1 ? 1 - x : x);
		shift += ((T / M) % N) * slope;
		fix_mod(ic, M);
		if (ic <= T % M) shift += slope;
		
		Si[i] = {x, i};
		pos[i] = x + (T % M) * slope;
		fix_mod(pos[i], M);
	}
	
	sort(Si.begin(), Si.end());
	sort(pos.begin(), pos.end());
	fix_mod(shift, N);
	
	// Map answers back into the ordering they had in the input
	vi ans(N, 0LL);
	for (int i = 0; i < N; ++i)
		ans[Si[i].second] = pos[(i + shift) % N];
	
	for (int i = 0; i < N; ++i)
		cout << ans[i] << " \n"[i + 1 == N];
	
	return 0;
}
