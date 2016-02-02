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
	
	vi a(n, 0);
	for (int i = 0; i < n; ++i)
		scanf("%d", &a[i]);
	sort(a.begin(), a.end());
	
	vi c(n+2, 0);
	for (int i = 0, j; i < n; ++i) {
		for (j = 0; c[j] > a[i]; ++j);
		c[j]++;
	}
	
	int k = 0;
	while (c[k] > 0) ++k;
	cout << k << endl;
	
	return 0;
}
