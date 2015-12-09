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
	
	vi a(n, 0);
	for (int i = 0; i < n; ++i) {
		int x;
		scanf("%d", &x);
		a[x - 1] = i;
	}
	
	vi seq(n, 1);
	for (int j = 1; j < n; ++j) {
		if (a[j - 1] < a[j]) seq[j] = seq[j - 1] + 1;
		else seq[j] = 1;
	}
	
	int best = n - 1;
	for (int i = 0; i < n; ++i)
		best = min(best, n - seq[i]);
	
	printf("%d\n", best);
	
	return 0;
}
