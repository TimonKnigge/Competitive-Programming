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
	
	int N;
	scanf("%d", &N);
	
	ll sc[2];
	sc[0] = sc[1] = 0LL;
	
	vi mids;
	for (int i = 0; i < N; ++i) {
		int k;
		scanf("%d", &k);
		for (int j = 0; j < k / 2; ++j) {
			int v;
			scanf("%d", &v);
			sc[0] += v;
		}
		if (k&1) {
			int v;
			scanf("%d", &v);
			mids.push_back(v);
		}
		for (int j = 0; j < k / 2; ++j) {
			int v;
			scanf("%d", &v);
			sc[1] += v;
		}
	}
	
	sort(mids.rbegin(), mids.rend());
	for (int j = 0; j < int(mids.size()); ++j)
		sc[j&1] += mids[j];
	
	cout << sc[0] << ' ' << sc[1] << endl;
	return 0;
}
