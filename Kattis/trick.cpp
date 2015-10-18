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
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

int main() {
	
	long double d;
	cin >> d;
	bool sol = false;
	ll front = 1;
	if (d < 10)
	for (int k = 0; k < 8; ++k) {
		for (int a = 1; a < 10; ++a) {
			long double bd = a * (d * front - 1) / (10 - d);
			if (bd >= front) continue;
			ll b = ll(round(bd));
			for (ll bb = max(0LL, b - 1); bb <= min(front - 1, b+1); ++bb)
				if (abs(d * (front * a + bb) - (10 * bb + a)) < 1e-5){
					cout << (front * a + bb) << '\n';
					sol = true;
				}
		}
		front *= 10;
	}
	
	if (!sol) cout << "No solution\n";
	cout << flush;
	
	return 0;
}
