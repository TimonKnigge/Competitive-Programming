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
	int m, n, k;
	scanf("%d %d %d", &m, &n, &k);
	
	vb has(n, false);
	int ans = 0, covered = 0;
	for (int i = 0; i < m; ++i) {
		bool cov = false;
		for (int j = 0; j < n; ++j) {
			int x;
			scanf("%d", &x);
			if (!has[j] && x == 0) {
				cov = true;
				has[j] = true;
				covered++;
			}
		}
		if (cov)
			ans++;
	}
	cout << ((ans <= k && covered == n )? "yes" : "no") << endl;
	
	return 0;
}
