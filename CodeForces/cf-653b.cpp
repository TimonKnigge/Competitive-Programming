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

ll dfs(int i, vvi &E, int c) {
	if (c == 0) return 1LL;
	ll ret = 0;
	for (int j : E[i])
		ret += dfs(j, E, c - 1);
	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N, Q;
	cin >> N >> Q;
	
	vvi E(6, vi());
	while (Q--) {
		string a, b;
		cin >> a >> b;
		E[b[0] - 'a'].push_back(a[0] - 'a');
	}
	
	cout << dfs(0, E, N - 1) << endl;
	
	return 0;
}
