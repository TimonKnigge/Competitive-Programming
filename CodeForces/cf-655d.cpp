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

void dfs(int i, vvi &E, vi &revtopo, vb &open, int &free) {
	open[i] = true;
	
	for (int v : E[i])
		if (!open[v]) dfs(v, E, revtopo, open, free);
	
	revtopo[free++] = i;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N, M;
	cin >> N >> M;
	
	vii given(M, {0LL, 0LL});
	for (int i = 0; i < M; ++i)
		cin >> given[i].first >> given[i].second,
		--given[i].first, --given[i].second;
	
	int l = 0, r = M;
	while (l < r) {
		int m = (l+r) / 2;
		
		set<ii> arcs;
		vvi E(N, vi());
		for (int i = 0; i <= m; ++i) {
			arcs.insert(given[i]);
			E[given[i].first].push_back(given[i].second);
		}
		
		vi revtopo(N, -1LL);
		vb open(N, false);
		int free = 0;
		for (int i = 0; i < N; ++i) {
			if (!open[i])
				dfs(i, E, revtopo, open, free);
		}
		
		bool pos = true;
		for (int i = 0; i + 1 < N; ++i)
			pos = pos && (arcs.find({ll(revtopo[i+1]), revtopo[i]}) != arcs.end());
		
		if (pos)r = m;
		else	l = m + 1;
	}
	
	cout << (l == M ? -1 : l+1) << endl;
	
	return 0;
}
