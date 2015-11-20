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
	vi h(n, 0);
	for (int i = 0; i < n; ++i)
		scanf("%d", &h[i]);
	
	vii seq;
	for (int i = 0; i < n; ++i)
		seq.push_back({h[i], i});
	sort(seq.begin(), seq.end());
	
	vi mapsto(n, -1);
	vi comesfrom(n, -1);
	for (int i = 0; i < seq.size(); ++i)
		mapsto[seq[i].second] = i;
	for (int i = 0; i < seq.size(); ++i)
		comesfrom[i] = seq[i].second;
	
	int ans = 0;
	int r = 0;
	for (int l = 0; l < n; ++l) {
		r = max(comesfrom[l], max(r, mapsto[l]));
		if (l == r) ans++;
	}
	
	cout << ans << endl;
	
	return 0;
}
