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
	
	int k;
	cin >> k;
	
	vector<vb> f(1 << k, vb(1 << k, false));
	for (int c = 0; c < k; ++c) {
		int cc = 1 << c;
		for (int i = 0; i < cc; ++i)
			for (int j = 0; j < cc; ++j) {
				f[i     ][j + cc] =  f[i][j];
				f[i + cc][j     ] =  f[i][j];
				f[i + cc][j + cc] = !f[i][j];
			}
	}
	for (int i = 0; i < (1<<k); ++i) {
		for (int j = 0; j < (1<<k); ++j)
			cout << (f[i][j] ? '+' : '*');
		cout << endl;
	}
	
	return 0;
}
