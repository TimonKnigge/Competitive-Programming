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
	
	int n, k;
	scanf("%d %d", &n, &k);
	
	vi s(n, 0);
	for (int i = 0; i < n; ++i)
		scanf("%d", &s[i]);
	
	int mx = 0;
	
	for (int j = 0; j < (n - k); ++j)
		mx = max(mx, s[j] + s[2 * (n - k) - 1 - j]);
	
	for (int j = max(0, n - k); j < n; ++j)
		mx = max(mx, s[j]);
	
	cout << mx << endl;
	
	return 0;
}
