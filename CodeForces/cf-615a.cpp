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
	vb on(m, false);
	int c = m;
	while (n--) {
		int x;
		scanf("%d", &x);
		for (int i = 0; i < x; ++i) {
			int v;
			scanf("%d", &v);
			--v;
			if (!on[v]) {
				--c;
				on[v] = true;
			}
		}
	}
	
	cout << (c == 0 ? "YES" : "NO") << endl;
	
	return 0;
}
