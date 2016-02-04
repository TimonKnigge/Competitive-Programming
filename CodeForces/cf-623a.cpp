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
	vvi e(N, vi());
	while (M--) {
		int a, b;
		scanf("%d %d", &a, &b);
		--b;
		--a;
		e[a].push_back(b);
		e[b].push_back(a);
	}
	
	vi blist;
	vb B(N, false);
	for (int i = 0; i < N; ++i)
		if (e[i].size() + 1 == N) {
			blist.push_back(i);
			B[i] = true;
		}
	
	vvi cc;
	vb vis(N, false);
	for (int i = 0; i < N; ++i) {
		vis[i] = vis[i] || B[i];
		if (vis[i]) continue;
		
		cc.push_back(vi());
		
		queue<int> q;
		q.push(i);
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			if (vis[u]) continue;
			vis[u] = true;
			cc.back().push_back(u);
			for (int v : e[u]) if (!B[v]) q.push(v);
		}
	}
	
	if (cc.size() > 2) {
		cout << "No" << endl;
		return 0;
	}
	while (cc.size() < 2) cc.push_back(vi());
	
	vi &alist = cc[0];
	vi &clist = cc[1];
	
	bool yes = true;
	for (int u : alist)
		yes = yes && (1 + e[u].size() == alist.size() + blist.size());
	for (int v : clist)
		yes = yes && (1 + e[v].size() == clist.size() + blist.size());
	
	if (!yes) cout << "No" << endl;
	else {
		cout << "Yes" << endl;
		string outs(N, 'b');
		for (int u : alist) outs[u] = 'a';
		for (int v : clist) outs[v] = 'c';
		cout << outs << endl;
	}
	
	return 0;
}
