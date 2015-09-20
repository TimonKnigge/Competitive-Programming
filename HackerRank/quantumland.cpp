#include <iostream> 
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
	vector<int> indeg(n, 0), w(n, -1), p(n, -1);
	for (int i = 0; i < n; ++i) {
		scanf("%d %d", &w[i], &p[i]);
		w[i]--;
		indeg[w[i]]++;
	}
	
	vector<bool> active(n, true);
	queue<int> q;
	for (int i = 0; i < n; ++i) {
		if (indeg[i] == 0) q.push(i);
	}
	
	while (!q.empty()) {
		int u = q.front(); q.pop();
		if (!active[u]) continue;
		active[u] = false;
		indeg[w[u]]--;
		if (indeg[w[u]] == 0) q.push(w[u]);
	}
	
	long double ans = 0.0;
	for (int i = 0; i < n; ++i) {
		if (!active[i]) continue;
		long double prob = 1.0;
		int j = i;
		while (true) {
			prob *= p[j] / 100.0;
			active[j] = false;
			j = w[j];
			if (j == i) break;
		}
		ans += prob;
	}
	
	printf("%.2lf\n", double(ans));
	
	return 0;
}
