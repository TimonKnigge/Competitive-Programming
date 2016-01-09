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
	
	int N, M;
	scanf("%d %d", &N, &M);
	vvi E(N, vi());
	for (int i = 0; i < M; ++i) {
		int u, v;
		scanf("%d %d", &u, &v);
		--u; --v;
		E[u].push_back(v);
		E[v].push_back(u);
	}
	
	vector<ll> tail(N, 0LL);
	ll best = 0LL;
	for (int i = 0; i < N; ++i) {
		tail[i] = 1;
		for (int j : E[i]) { 
			if (j > i) continue;
			tail[i] = max(tail[i], 1 + tail[j]);
		}
		best = max(best, tail[i] * ll(E[i].size()));
	}
	
	cout << best << endl;
	
	return 0;
}
