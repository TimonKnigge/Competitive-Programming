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
	
	vi a(n, 0);
	for (int i = 0; i < n; ++i) cin >> a[i];
	
	sort(a.begin(), a.end());
	bool p = false;
	for (int i = 2; i < n; ++i)
		p = p || (a[i] < (a[i-1] + a[i-2]));
	if (!p) cout << "im";
	cout << "possible" << endl;
	
	return 0;
}
