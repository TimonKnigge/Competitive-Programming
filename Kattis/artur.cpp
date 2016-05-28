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

struct pt {
	ll x1;
	ll y1;
	ll x2;
	ll y2;
};

ll det(ll x1, ll y1, ll x2, ll y2) {
	return x1*y2 - x2*y1;
}

void dfs(int u, vvi &E, vi &ans, vb &vis) {
	vis[u] = true;
	for (int v : E[u]) 
		if (!vis[v]) dfs(v, E, ans, vis);
	ans.push_back(u);
}

int main() {
	
	int N;
	scanf("%d", &N);
	
	vector<pt> S;
	S.reserve(N);
	for (int i = 0, x1, y1, x2, y2; i < N; ++i) {
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		if (x1 > x2 || (x1 == x2 && y1 > y2)) {
			swap(x1, x2); swap(y1, y2);
		}
		S.push_back({x1, y1, x2, y2});
	}
	
	vvi E(N, vi());
	for (int i = 0; i < N; ++i)
		for (int j = i+1; j < N; ++j) {
			if (S[i].x2 < S[j].x1 || S[j].x2 < S[i].x1) continue;
			if (S[i].x1 <= S[j].x1 && S[j].x1 <= S[i].x2) {
				if (S[i].x1 == S[i].x2)
					if (S[i].y2 < S[j].y1)
						E[i].push_back(j);
					else	E[j].push_back(i);
				else
				if (det(S[i].x2-S[i].x1, S[i].y2-S[i].y1,
					S[j].x1-S[i].x1, S[j].y1-S[i].y1)
					> 0LL)
					E[i].push_back(j);
				else	E[j].push_back(i);
			} else if (S[i].x1 <= S[j].x2 && S[j].x2 <= S[i].x2) {
				if (S[i].x1 == S[i].x2)
					if (S[i].y2 < S[j].y2)
						E[i].push_back(j);
					else	E[j].push_back(i);
				else
				if (det(S[i].x2-S[i].x1, S[i].y2-S[i].y1,
					S[j].x2-S[i].x1, S[j].y2-S[i].y1)
					> 0LL)
					E[i].push_back(j);
				else	E[j].push_back(i);
			} else if (S[j].x1 <= S[i].x1 && S[i].x1 <= S[j].x2) {
				if (S[j].x1 == S[j].x2)
					if (S[j].y2 < S[i].y1)
						E[j].push_back(i);
					else	E[i].push_back(j);
				else
				if (det(S[j].x2-S[j].x1, S[j].y2-S[j].y1,
					S[i].x1-S[j].x1, S[i].y1-S[j].y1)
					> 0LL)
					E[j].push_back(i);
				else	E[i].push_back(j);
			} else if (S[j].x1 <= S[i].x2 && S[i].x2 <= S[j].x2) {
				if (S[j].x1 == S[j].x2)
					if (S[j].y2 < S[i].y2)
						E[j].push_back(i);
					else	E[i].push_back(j);
				else
				if (det(S[j].x2-S[j].x1, S[j].y2-S[j].y1,
					S[i].x2-S[j].x1, S[i].y2-S[j].y1)
					> 0LL)
					E[j].push_back(i);
				else	E[i].push_back(j);
			}
		}
	
//	for (int i = 0; i < N; ++i)
//		for (int j : E[i])
//			cout << "(" << i+1 << "," << j+1 << ") ";
//	cout << endl;
	
	vi ans;
	vb vis(N, false);
	for (int i = 0; i < N; ++i)
		if (!vis[i]) dfs(i, E, ans, vis);
	
	for (int i = N - 1; i >= 0; --i) cout << (1+ans[i]) << " \n"[i==0];
	
	return 0;
}
