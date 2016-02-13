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

void dfs(int u, int p, vvi &e, vvi &ch) {
	for (int v : e[u]) {
		if (v == p) continue;
		ch[u].push_back(v);
		dfs(v, u, e, ch);
	}
}

using pq = priority_queue<ll>;

void find_depths(int u, vvi &e, pq &q, ll d) {
	if (e[u].size() == 0)
		q.push(d);
	else {
		for (int v : e[u]) {
			find_depths(v, e, q, d + 1);
		}
	}
}

ll find(int u, vvi &e) {
	pq q;
	find_depths(u, e, q, 0LL);
	
	ll T = 0LL;
	ll ret = 0LL;
	while (!q.empty()) {
		ll d = q.top();
		q.pop();
		ret = max(ret, d + T);
		++T;
	}
	return ret;
}

int main() {
	
	int N;
	scanf("%d", &N);
	
	vvi e(N, vi());
	for (int i = 0; i + 1 < N; ++i) {
		int a, b;
		scanf("%d %d", &a, &b);
		--a;
		--b;
		e[a].push_back(b);
		e[b].push_back(a);
	}
	
	vvi ch(N, vi());
	dfs(0, -1, e, ch); // set root
	
	ll time = 0LL;
	for (int v : e[0]) {
		time = max(time, 1LL + find(v, ch));
	}
	
	cout << time << endl;
	
	return 0;
}
