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
	
	int n;
	scanf("%d", &n);
	
	vi p(n, -1);
	vvi c(n, vi());
	for (int i = 1, v; i < n; ++i)
		scanf("%d", &v),
		p[i] = v - 1,
		c[p[i]].push_back(i);
	
	vi subtree(n, 1LL);
	for (int i = n - 1; i > 0; --i)
		subtree[p[i]] += subtree[i];
	
	vector<ld> time(n, 0.0);
	
	for (int i = 0; i < n; ++i) {
		time[i] += 1.0;
		for (int j : c[i]) {
			time[j] = time[i] + ld(subtree[i] - 1LL - subtree[j]) / 2.0;
		}
		if (i > 0) printf(" ");
		printf("%.7lf", double(time[i]));
	}
	printf("\n");
	
	return 0;
}
