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
#include <unordered_map>
#include <unordered_set>

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
	
	int n, m;
	cin >> n >> m >> ws;
	
	unordered_set<string> h;
	for (int i = 0; i < n; ++i) {
		string s;
		getline(cin, s);
		h.insert(s);
	}
	
	int o = 0;
	for (int i = 0; i < m; ++i) {
		string s;
		getline(cin, s);
		if (h.find(s) != h.end()) ++o;
	}
	
	m -= o;
	if (o&1) --o;
	n -= o;
	
	cout << (n > m ? "YES" : "NO") << endl;
	
	return 0;
}
