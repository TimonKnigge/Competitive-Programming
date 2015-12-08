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
const ll LLINF = 9000000000000000000LL;

int main() {
	
	int n;
	scanf("%d", &n);
	
	int ans = 0;
	char last = 'a';
	for (int i = 0; i < n; ++i) {
		char c;
		scanf(" %c", &c);
		if (c != last) ans++;
		last = c;
	}
	
	printf("%d\n", min(n, ans + 2));
	
	return 0;
}
