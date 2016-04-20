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
	
bool optimal(int N, vvii &E, int &opt, vb &flip) {
	bool consistent = true;
	vi status(N, -1LL);
	vi comp(N, -1LL);
	int C = 0;
	for (int u = 0; u < N; ++u) {
		if (status[u] >= 0) continue;
		
		comp[u] = C;
		status[u] = 0LL;
		queue<int> q;
		q.push(u);
		while (!q.empty()) {
			int v = q.front();
			q.pop();
			
			for (ii wt : E[v]) {
				int w = wt.first, t = wt.second;
				if (status[w] == -1LL) {
					status[w] = (status[v] + t) % 2;
					comp[w] = C;
					q.push(w);
				} else {
					if (t == 0 && status[w] != status[v])
						consistent = false;
					if (t == 1 && status[w] == status[v])
						consistent = false;
				}
			}
		}
		++C;
	}
	
	vvi side(2, vi(C, 0LL));
	for (int u = 0; u < N; ++u) {
		side[status[u]][comp[u]]++;
	}
	
	opt = 0;
	flip.assign(N, false);
	vb comp_flip(C, false);
	for (int c = 0; c < C; ++c) {
		if (side[0][c] > side[1][c]) comp_flip[c] = true;
		opt += min(side[0][c], side[1][c]);
	}
	
	for (int u = 0; u < N; ++u) {
		if (status[u] == 0 && !comp_flip[comp[u]])
			flip[u] = true;
		if (status[u] == 1 && comp_flip[comp[u]])
			flip[u] = true;
	}
	
	return consistent;
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	ll N, M;
	cin >> N >> M;
	
	vvii E(N, vii());
	while (M--) {
		int u, v;
		char c;
		cin >> u >> v >> c;
		--u; --v;
		E[u].push_back({v, (c == 'R' ? 1 : 0)});
		E[v].push_back({u, (c == 'R' ? 1 : 0)});
	}
	/*
	
bool optimal(int N, vvii &E, int &opt, vb &flip) {
	
	*/
	
	int boptv = INF, roptv = INF;
	vb bflip, rflip;
	
	bool bopt = optimal(N, E, boptv, bflip);
	for (int u = 0; u < N; ++u) {
		for (size_t i = 0; i < E[u].size(); ++i)
			E[u][i].second = 1 - E[u][i].second;
	}
	bool ropt = optimal(N, E, roptv, rflip);
	
	if (!bopt && !ropt) cout << -1 << endl;
	else {
		vb &ans = bflip;
		if (!bopt || (ropt && roptv < boptv)) {
			ans = rflip;
		}
		vi ansv;
		for (int i = 0; i < N; ++i)
			if (ans[i]) ansv.push_back(i + 1);
		cout << ansv.size() << endl;
		for (size_t i = 0; i < ansv.size(); ++i)
			cout << ansv[i] << " \n"[i + 1 == ansv.size()];
	}
	
	return 0;
}
