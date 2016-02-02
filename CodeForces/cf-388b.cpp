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
	
	ll k;
	cin >> k;
	
	if (k == 0) {
		cout << 2 << endl << "NN" << endl << "NN" << endl;
		return 0;
	}
	
	int vibt = 0;
	ll c = 1;
	while (c < k) { c *= 2; vibt++; }
	
	int V = 2;
	vvi adj(2, vi());
	
	vi pleft(vibt + 3, -1);
	for (ll m = 1, d = 0; k > 0; ++d, m *= 2) {
		if ((k&m) == 0LL) continue;
		
		// We add m=2^d paths
		// so d layers, rest singles
		int ll = 0, lr = -1;
		bool joined = false;
		for (int l = 0; l < vibt; ++l) {
			if (l < d) {
				adj.push_back(vi());
				adj.push_back(vi());
				adj[ll].push_back(V);
				adj[ll].push_back(V+1);
				if (lr != -1) {
					adj[lr].push_back(V);
					adj[lr].push_back(V+1);
				}
				ll = V;
				lr = V + 1;
				V += 2;
			} else {
				if (pleft[l] != -1) {
					adj[ll].push_back(pleft[l]);
					if (lr != -1)
						adj[lr].push_back(pleft[l]);
					joined = true;
					break;
				} else {
					adj.push_back(vi());
					adj[ll].push_back(V);
					if (lr != -1)
						adj[lr].push_back(V);
					ll = V;
					lr = -1;
					pleft[l] = V;
					++V;
				}
			}
		}
		
		if (!joined) {
			adj[ll].push_back(1);
			if (lr != -1)
				adj[lr].push_back(1);
		}
		k -= m;
	}
	
	vector<vb> mat(V, vb(V, false));
	for (int i = 0; i < V; ++i)
		for (int j : adj[i])
			mat[i][j] = mat[j][i] = true;
	cout << V << '\n';
	for (int i = 0; i < V; ++i) {
		for (int j = 0; j < V; ++j)
			cout << (mat[i][j] ? 'Y' : 'N');
		cout << '\n';
	}
	cout << flush;
	
	return 0;
}
