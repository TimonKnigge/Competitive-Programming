#include <iostream>
#include <iomanip>
#include <vector>	       
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <bitset>
#include <algorithm>
#include <functional>
#include <string>
#include <string.h>  // Include for memset!
#include <complex>
#include <random>
#define _USE_MATH_DEFINES
#include <math.h>

const int INF = 2000000000;	                 // 9
const long long LLINF = 9000000000000000000LL;  // 18
const long double LDINF = 1e300;

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<bool> vb;
typedef long long ll;
typedef long double ld;

const int MOD = 10007;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int T;
	cin >> T;
	for (int t = 1; t <= T; ++t) {
		int n;
		cin >> n;
		vvi edges(n, vi());
		vi par(n, -1);
		for (int i = 0; i < n - 1; ++i) {
			int u, v;
			cin >> u >> v;
			edges[u - 1].push_back(v - 1);
			edges[v - 1].push_back(u - 1);
		}
		
		// root the tree at 0, toposort
		stack<int> st;
		vector<int> topo(n, -1);
		st.push(0);
		int t_ix = 0;
		while (!st.empty()) {
			int u = st.top(); st.pop();
			topo[t_ix] = u;
			t_ix++;
			for (int v : edges[u]) {
				if (v == par[u]) continue;
				par[v] = u;
				st.push(v);
			}
		}
		
		vector<int> op_on(n, INF), op_off(n, INF);
		vector<ll> op_on_ways(n, 0), op_off_ways(n, 0);
		for (int j = n - 1; j >= 0; --j) {
			int u = topo[j];
			op_on[u] = 1;
			op_on_ways[u] = 1;
			op_off[u] = 0;
			op_off_ways[u] = 1;
			for (int v : edges[u]) {
				if (v == par[u]) continue;
				if (op_on[v] > op_off[v]) {
					op_on[u] += op_off[v];
					op_on_ways[u] = (op_on_ways[u] * op_off_ways[v]) % MOD;
				} else if (op_on[v] < op_off[v]) {
					op_on[u] += op_on[v];
					op_on_ways[u] = (op_on_ways[u] * op_on_ways[v]) % MOD;
				} else {
					op_on[u] += op_off[v];
					op_on_ways[u] = (op_on_ways[u] * ((op_on_ways[v] + op_off_ways[v]) % MOD)) % MOD;
				}
				op_off[u] += op_on[v];
				op_off_ways[u] = (op_off_ways[u] * op_on_ways[v]) % MOD;
			}
		}
		
		int op = op_on[0];
		ll ways = op_on_ways[0];
		if (op_off[0] < op) {
			op = op_off[0];
			ways = op_off_ways[0];
		} else if (op_off[0] == op) {
			ways = (ways + op_off_ways[0]) % MOD;
		}
		cout << op << ' ' << ways << endl;
	}
	
	return 0;
}
