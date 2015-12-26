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
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

int main() {
	
	int n;
	scanf("%d", &n);
	vi p(n, -1);
	for (int i = 0; i < n; ++i) {
		int v;
		scanf("%d", &v);
		p[v - 1] = i;
	}

	ll ans = 0LL;
	for (int i = 0; i + 1 < n; ++i)
		ans += (p[i] > p[i + 1] ? -1 : 1) * (p[i + 1] - p[i]);
	
	cout << ans << endl;
	
	return 0;
}
