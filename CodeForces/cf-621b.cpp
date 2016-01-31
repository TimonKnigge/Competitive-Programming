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
	map<int, int> d1, d2;
	ll att = 0;
	for (int i = 0; i < N; ++i) {
		int x, y;
		scanf("%d %d", &x, &y);
		auto it = d1.find(x + y);
		if (it != d1.end()) {
			att += it->second;
			++it->second;
		} else d1.insert({x + y, 1});
		it = d2.find(x - y);
		if (it != d2.end()) {
			att += it->second;
			++it->second;
		} else d2.insert({x - y, 1});
	}
	
	cout << att << endl;
	
	return 0;
}
