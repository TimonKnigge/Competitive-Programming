#include <iostream> 
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
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int T;
	cin >> T;
	while (T--) {
		int N, E;
		cin >> N >> E;
		
		vector<ll> V(N, 0);
		for (int i = 0; i < N; ++i) { cin >> V[i]; }
		
		vector<vector<pair<int, ll> > > e(N, vector<pair<int,ll> >());
		vi indeg(N, 0);
		for (int i = 0; i < E; ++i) {
			int a, b, c;
			cin >> a >> b >> c;
			a--; b--;
			e[a].push_back({b, c});
			indeg[b]++;
		}
		
		vector<ll> C(N, -LLINF);
		vi par(N, -1);
		C[0] = V[0];
		
		queue<int> q;
		q.push(0);
		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (auto vw : e[u]) {
				int v = vw.first; ll w = vw.second;
				ll cst = C[u] + V[v] - w;
				if (cst > C[v]) { C[v] = cst; par[v] = u; }
				indeg[v]--;
				if (indeg[v] == 0) q.push(v);
			}
		}
		
		int ep = 0;
		for (int i = 1; i < N; ++i) if (C[i] > C[ep]) ep = i;
		ll optimal = C[ep];

		vector<int> route;
		while (ep != -1) {
			route.push_back(ep);
			ep = par[ep];
		}
		
		cout << optimal << ' ' << route.size() << endl;
		for (int i = route.size() - 1; i >= 0; --i) {
			cout << (1 + route[i]);
			if (i != 0) cout << ' ';
		}
		cout << endl;
	}
	
	return 0;
}
