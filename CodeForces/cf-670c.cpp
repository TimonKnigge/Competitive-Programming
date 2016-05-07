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
	
	map<int, int> kn;
	for (int i = 0, a; i < n; ++i) {
		cin >> a;
		auto it = kn.find(a);
		if (it == kn.end())
			kn.insert({a, 1});
		else	it->second++;
	}
	
	int m;
	cin >> m;
	vii mov(m, {0LL, 0LL});
	for (int i = 0, b; i < m; ++i) {
		cin >> b;
		auto it = kn.find(b);
		if (it != kn.end())
			mov[i].first = it->second;
	}
	for (int i = 0, c; i < m; ++i) {
		cin >> c;
		auto it = kn.find(c);
		if (it != kn.end())
			mov[i].second = it->second;
	}
	
	int ans = 0;
	for (int i = 1; i < m; ++i)
		if (mov[i] > mov[ans]) ans = i;
	
	cout << (ans + 1) << endl;
	
	return 0;
}
