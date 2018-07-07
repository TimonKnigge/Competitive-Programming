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

ll f() {
	ll N;
	cin >> N;
	vi W(N, 0LL);
	for (ll &v : W) cin >> v, v = (50LL + v - 1LL) / v;
	sort(W.begin(), W.end());
	
	for (ll i = 0LL, sum = 0LL; i < N; ++i) {
		sum += W[i];
		if (sum > N) return i;
	}
	return N;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int T;
	cin >> T;
	for (int t = 1; t <= T; ++t) {
		cout << "Case #" << t << ": ";
		cout << f() << '\n';
	}
	
	return 0;
}
