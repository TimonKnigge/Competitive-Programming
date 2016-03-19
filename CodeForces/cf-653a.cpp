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
	
	int N;
	cin >> N;
	
	vb h(1001, false);
	while (N--) {
		int v;
		cin >> v;
		h[v] = true;
	}
	
	bool p = false;
	for (int i = 1; i + 2 <= 1000; ++i)
		p = p || (h[i] && h[i+1] && h[i+2]);
	
	cout << (p ? "YES" : "NO") << endl;
	
	return 0;
}
