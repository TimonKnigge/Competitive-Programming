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

unsigned int c[1000002];

int main() {
	
	int N, ans = 0, v;
	scanf("%d", &N);
	
	while (N--) {
		scanf("%d", &v);
		++c[v];
		if (c[++v] > 0)
			--c[v];
		else	++ans;
	}
	
	printf("%d\n", ans);
	
	return 0;
}
