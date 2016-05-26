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

int calc(string &S, int K) {
	
	int ret = 0, l = 0, bs = 0;
	for (int r = 0; r < int(S.length()); ++r) {
		if (S[r] == 'b') ++bs;
		
		while (l < r && bs > K) {
			if (S[l] == 'b') --bs;
			++l;
		}
		
		if (bs <= K) ret = max(ret, r - l + 1);
	}
	
	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N, K;
	string S;
	cin >> N >> K >> S;
	
	int ans = calc(S, K);
	for (int i = 0; i < N; ++i)
		S[i] = (S[i] == 'a' ? 'b' : 'a');
	ans = max(ans, calc(S, K));
	
	cout << ans << endl;
	
	return 0;
}
