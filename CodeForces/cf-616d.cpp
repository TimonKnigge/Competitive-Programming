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
	
	int N, K;
	scanf("%d %d", &N, &K);
	
	vi a(N, 0);
	for (int i = 0; i < N; ++i)
		scanf("%d", &a[i]);
	
	vi count(1e6 + 1, 0);
	
	int L = 0, R = -1, vals = 0;
	for (int l = 0, r = -1; l < N; ++l) {
		while (r + 1 < N && (vals < K || count[a[r + 1]] > 0)) {
			r++;
			count[a[r]]++;
			if (count[a[r]] == 1) vals++;
		}
		
		if (r - l > R - L) { L = l; R = r; }
		
		count[a[l]]--;
		if (count[a[l]] == 0) vals--;
	}
	
	cout << (L + 1) << ' ' << (R + 1 ) << endl;
	
	return 0;
}
