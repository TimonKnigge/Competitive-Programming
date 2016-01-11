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
	
	int n, m;
	scanf("%d %d", &n, &m);
	
	int rm = 0;
	while (n--) {
		int mn = INF;
		for (int i = 0; i < m; ++i) {
			int cij;
			scanf("%d", &cij);
			mn = min(mn, cij);
		}
		rm = max(mn, rm);
	}
	
	printf("%d\n", rm);
	
	return 0;
}
