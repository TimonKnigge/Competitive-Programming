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

ll MOD = 1e9 + 7;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N, K;
	cin >> N >> K;
	
	string S;
	cin >> S;
	
	vi sum(S.length(), 0);
	vi last(K, -1LL);
	
	for (size_t i = 0; i < S.length(); ++i) {
		ll dp = 0LL;
		if (i > 0)
			dp += sum[i-1];
		else	dp += 1LL;
		if (last[S[i] - 'a'] > 0)
			dp -= sum[last[S[i] - 'a'] - 1];
		else if (last[S[i] - 'a'] == 0)
			dp -= 1LL;
		dp = (dp % MOD) + MOD;
		sum[i] = (i > 0 ? sum[i - 1] : 1LL) + dp;
		sum[i] %= MOD;
		last[S[i] - 'a'] = i;
	}
	
	priority_queue<ii, vector<ii>, greater<ii> > pq;
	for (int i = 0; i < K; ++i)
		pq.push({last[i], i});
	
	for (int i = S.length(); i < S.length() + N; ++i) {
		ii tp = pq.top(); pq.pop();
		int c = tp.second;
		pq.push({ll(i), ll(c)});
		
		ll dp = sum[i - 1];
		if (last[c] > 0)
			dp -= sum[last[c] - 1];
		else if (last[c] == 0)
			dp -= 1LL;
		
		dp = (dp % MOD) + MOD;
		sum.push_back((sum[i-1] + dp) % MOD);
		last[c] = i;
	}
	
	cout << sum.back() << endl;
	
	return 0;
}
