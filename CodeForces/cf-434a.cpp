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
	
	int n, m;
	cin >> n >> m;
	
	vi A(m, 0);
	for (int i = 0; i < m; ++i)
		cin >> A[i], --A[i];
	
	ll opt = 0LL;
	vvi mv(n, vi());
	for (int i = 0; i + 1 < m; ++i) {
		if (A[i] != A[i+1]) {
			mv[A[i]].push_back(A[i + 1]);
			mv[A[i + 1]].push_back(A[i]);
		}
		opt += ll(A[i] > A[i+1] ? A[i] - A[i+1] : A[i+1] - A[i]);
	}
	ll inv = opt;
//	cerr << "inv\t" << inv << endl;
	for (int i = 0; i < n; ++i) {
		sort(mv[i].begin(), mv[i].end());
		ll diff = 0LL;
		for (ll j = 0; j < mv[i].size(); ++j) {
			diff += (mv[i][j] - mv[i][0])
				- (  i  > mv[i][j] 
				 ?   i  - mv[i][j] 
				 : mv[i][j] - i  );
		}
		opt = min(opt, inv + diff);
		for (size_t j = 1; j < mv[i].size(); ++j) {
			diff += ll(mv[i][j] - mv[i][j-1]) * j;
			diff += ll(mv[i][j-1] - mv[i][j]) * ll(mv[i].size() - j);
			opt = min(opt, inv + diff);
		}
	}
	
	cout << opt << endl;
	
	return 0;
}
