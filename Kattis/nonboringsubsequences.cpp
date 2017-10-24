#include <iostream> 
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <unordered_map>
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

bool divcon(int lo, int hi, vi &l, vi &r) {
	if (hi - lo < 3) {
		bool y = true;
		for (int i = lo; i < hi; ++i) y = y && r[i] != i + 1;
		return y;
	}
	// Find a unique value in [lo, hi]
	int midpoint = -1;
	for (int d = 0; d < hi - lo; ++d) {
		// check lo + d and hi - d to achieve O(n) running time
		int j = lo + d;
		if (l[j] < lo && r[j] > hi) {
			midpoint = lo + d;
			break;
		}
		j = hi - d;
		if (l[j] < lo && r[j] > hi) {
			midpoint = hi - d;
			break;
		}
	}
	if (midpoint == -1) return false;
	else return divcon(lo, midpoint - 1, l, r) 
		&& divcon(midpoint + 1, hi, l, r);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int T;
	cin >> T;
	while (T--) {
		int n;
		cin >> n;
		vi a(n, 0), l(n, -1), r(n, INF);
		unordered_map<int, int> last;
		for (int i = 0; i < n; ++i) {
			cin >> a[i];
			l[i] = last[a[i]] - 1;
			if (l[i] >= 0) r[l[i]] = i;
			last[a[i]] = i + 1;
		}
		
		bool possible = divcon(0, n - 1, l, r);
		cout << (possible ? "non-boring" : "boring") << endl;
	}
	
	return 0;
}
