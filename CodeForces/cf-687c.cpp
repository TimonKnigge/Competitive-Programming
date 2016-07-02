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

bool dp[501][501];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, k;
	cin >> n >> k;
	
	for (int i = 0; i <= k; ++i)
		for (int j = 0; j <= k; ++j)
			dp[i][j] = false;
	dp[0][0] = true;
	
	while (n--) {
		int v;
		cin >> v;
		for (int i = k - v; i >= 0; --i)
			for (int j = k; j >= 0; --j)
				if (!dp[i][j]) continue;
				else {
					dp[i+v][j] = true;
					if (j + v <= k)
						dp[i+v][j+v] = true;
				}
	}
	
	vi ans;
	for (int i = 0; i <= k; ++i)
		if (dp[k][i]) ans.push_back(i);
	cout << ans.size() << endl;
	for (size_t i = 0; i < ans.size(); ++i)
		cout << ans[i] << " \n"[i + 1 == ans.size()];
	
	return 0;
}
