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
	
	freopen("cardgame.in", "r", stdin);
	freopen("cardgame.out","w", stdout);
	
	int N;
	scanf("%d", &N);
	
	vb has(2 * N, true);
	vi r1, r2;
	for (int i = 0; i < N/2; ++i) {
		int v;
		scanf("%d", &v);
		--v;
		has[v] = false;
		r1.push_back(v);
	}
	for (int i = 0; i < N/2; ++i) {
		int v;
		scanf("%d", &v);
		--v;
		has[v] = false;
		r2.push_back(v);
	}
	
	vi b;
	for (int i = 0; i < N * 2; ++i)
		if (has[i]) b.push_back(i);
	
	sort(r1.begin(), r1.end());
	sort(r2.begin(), r2.end());
	sort(b.begin(), b.end());
	
	int ans = 0;
	while (r1.size() > 0) {
		if (b.back() > r1.back()) {
			ans++;
			b.pop_back();
		}
		r1.pop_back();
	}
	
	int j = 0;
	for (int i = 0; i < r2.size(); ++i) {
		if (j < b.size() && b[j] < r2[i]) {
			j++;
			ans++;
		}
	}
	cout << ans << endl;
	
	return 0;
}
