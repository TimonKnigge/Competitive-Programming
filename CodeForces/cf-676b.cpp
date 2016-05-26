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
	
	int n, t;
	cin >> n >> t;
	vvi cnt(n+1, vi(n+1, 0LL));
	
	cnt[0][0] = t;
	int ans = 0;
	for (int l = 0, div = 1; l < n; ++l, div <<= 1) {
		for (int i = 0; i <= l; ++i) {
			if (cnt[l][i] >= div) ++ans;
			cnt[l][i] = max(0LL, cnt[l][i] - div);
			cnt[l+1][i] += cnt[l][i];
			cnt[l+1][i+1] += cnt[l][i];
		}
	}
	
	cout << ans << endl;
	
	return 0;
}
