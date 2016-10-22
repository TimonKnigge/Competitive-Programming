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

ll costs(ll t1, ll t2, ll boats) {
	ll lopen = t1 + 30*60;
	ll eclose = max(lopen+20*boats, t2+20);
	return 120 + (eclose-lopen);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N;
	cin >> N;
	vi T(N, 0LL);
	for (int i = 0; i < N; ++i) cin >> T[i];
	
	vi dp(N+1, LLINF);
	dp[0] = 0LL;
	
	for (int i = 0; i < N; ++i) {
		//last boat is boat i
		for (int j = 0; j <= i; ++j) {
			//first boat is boat j
			dp[i+1] = min(dp[i + 1],
				dp[j] + costs(T[j], T[i], i - j + 1));
		}
	}
	
	cout << dp[N] << endl;
	
	return 0;
}
