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
	
	int n;
	cin >> n;
	
	vi zib;
	int z = 1;
	bool fo = false;
	for (int i = 0; i < n; ++i) {
		int v;
		cin >> v;
		if (v == 0) z++;
		else {
			if (fo)	zib.push_back(z);
			else	fo = true;
			z = 1;
		}
	}
	
	ll res = 0LL;
	if (fo) {
		res = 1LL;
		for (int i = 0; i < int(zib.size()); ++i)
			res *= ll(zib[i]);
	}
	
	cout << res << endl;
	
	return 0;
}
