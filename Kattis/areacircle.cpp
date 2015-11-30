#include <iostream> 
#include <iomanip>
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
using ld = long double;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;


#define MY_PI 3.14159265358979323846

int main() {
	
	cout << setprecision(6) << fixed;
	
	while (true) {
		long double r;
		ll c, m;
		cin >> r >> m >> c;
		
		if (c == 0 && m == 0 && r < 1e-6) break;
		
		cout << (r * r * MY_PI) << ' ';
		cout << (ld(c) / ld(m) * 4 * r * r) << '\n';
	}
	cout << flush;
	
	return 0;
}
