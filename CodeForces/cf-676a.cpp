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
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	
	int p1 = -1, p2 = -1;
	for (int i = 0; i < n; ++i) {
		int v;
		cin >> v;
		if (v == 1) p1 = i+1;
		if (v == n) p2 = i+1;
	}
	
	if (p1 == 1 || p2 == 1 || p2 == n || p1 == n)
		cout << n-1 << endl;
	else
		cout << max(max(n-p1, n-p2), max(p1-1, p2-1)) << endl;
	
	return 0;
}
