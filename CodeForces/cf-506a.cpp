#include <iostream>
#include <iomanip>
#include <vector>           
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <bitset>
#include <algorithm>
#include <functional>
#include <string>
#include <string.h>  // Include for memset!
#include <complex>
#include <random>
#define _USE_MATH_DEFINES
#include <math.h>

const int INF = 2000000000;                     // 9
const long long LLINF = 9000000000000000000LL;  // 18
const long double LDINF = 1e300;

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<bool> vb;
typedef long long ll;
typedef long double ld;

map<ii, int> mp;

int ways(ii vl, vector<int> &p) {
	int v = vl.first, l = vl.second;
	auto it = mp.find(vl);
	if (v > 30000 || l == 0) return 0;
	if (it != mp.end()) return it->second;
	else {
		int r = p[v];
		r = max(r, p[v] + ways({v + l - 1, l - 1}, p));
		r = max(r, p[v] + ways({v + l, l}, p));
		r = max(r, p[v] + ways({v + l + 1, l + 1}, p));
		mp.insert({vl, r});
		return r;
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, d;
	cin >> n >> d;
	vector<int> p(30001, 0);
	for (int i = 0; i < n; ++i) { int _p; cin >> _p; p[_p]++; }

	cout << ways({d, d}, p) << endl;

	return 0;
}
