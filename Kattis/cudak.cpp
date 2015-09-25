#include <iostream> 
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

ll dp[15][136];

ll calc(ll A, ll S) {
	if (A == 0) return 0;
	
	vector<int> digit;
	while (A > 0) { digit.push_back(A % 10); A /= 10; }
	
	ll ans = 0LL;
	int sum = 0;
	for (int i = digit.size() - 1; i >= 0; --i) {
		for (int d = 0; d < digit[i]; ++d) {
			if (S - sum - d >= 0)
				ans += dp[i][S - sum - d];
		}
		sum += digit[i];
	}
	if (sum == S) ans++;
	return ans;
}

ll gen_next(ll A, ll B, ll S) {
	ll l = A, r = B;
	while (l < r) {
		ll M = (l + r) / 2;
		if (calc(M, S) - calc(A - 1, S) > 0) r = M;
		else l = M + 1;
	}
	return l;
}

int main() {
	for (int i = 0; i < 15; ++i)
		for (int j = 0; j < 136; ++j)
			dp[i][j] = 0LL;
	dp[0][0] = 1LL;
	for (int d = 1; d < 15; ++d)
		for (int s = 0; s < 136; ++s)
			for (int i = 0; i < 10; ++i)
				if (s - i >= 0)
					dp[d][s] += dp[d - 1][s - i];
	
	long long A, B, S;
	cin >> A >> B >> S;
	
	cout << (calc(B, S) - calc(A - 1, S)) << endl;
	cout << gen_next(A, B, S) << endl;
	
	return 0;
}

