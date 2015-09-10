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
#include <cstdio>

using namespace std;
using ll = long long;
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;

int d1, d2;

int main() {
	int n;
	scanf("%d", &n);
	vii pts(n, ii(0, 0));
	vi p(n, 0);
	for (int i = 0; i < n; ++i) {
		p[i] = i;
		scanf("%d", &pts[i].first);
		scanf("%d", &pts[i].second);
	}
	
	sort(p.begin(), p.end(),[&pts](int i, int j) {
		d1 = pts[i].first / 1e3; d2 = pts[j].first / 1e3;
		if (d1 != d2) return d1 < d2;
		else if ((d1&1) == 1) return pts[i].second > pts[j].second;
		else return pts[i].second < pts[j].second;
	});
	
	for (size_t i = 0; i < n; ++i)
		cout << (1 + p[i]) << " \n"[i == n - 1];
	
	return 0;
}
