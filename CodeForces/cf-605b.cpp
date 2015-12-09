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
	
	int n, m;
	scanf("%d %d", &n, &m);
	
	vector<pair<ll, int> > mst, e;
	for (int i = 0; i < m; ++i) {
		int a,b;
		scanf("%d %d", &a, &b);
		if (b == 1) mst.push_back({a, i});
		else e.push_back({a, i});
	}
	
	sort(e.begin(), e.end());
	sort(mst.begin(), mst.end());
	
	vii edges;
	for (int r = 2; r < n && edges.size() < m; ++r)
		for (int l = 0; l < r - 1 && edges.size() < m; ++l)
			edges.push_back({l, r});
	
	vii res(m, {-1, -1});
	for (int i = 0; i < mst.size(); ++i)
		res[mst[i].second] = {i, i + 1};
	vvi wout(n, vi());
	for (int i = 0; i < e.size(); ++i) {
		res[e[i].second] = edges[i];
		wout[edges[i].second].push_back(e[i].first);
	}
	
	bool possible = true;
	for (int j = 1; j < n; ++j) {
		for (int o : wout[j])
			possible = possible && (o >= mst[j - 1].first);
	}
	
	if (!possible) cout << -1 << endl;
	else {
		for (int j = 0; j < res.size(); ++j) {
			cout << (1+res[j].first) << ' '<< (1+res[j].second) << '\n';
		}
		cout << flush;
	}
	
	return 0;
}
