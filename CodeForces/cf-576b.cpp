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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	vector<int> p(n, 0);
	for (int i = 0; i < n; ++i) {
		cin >> p[i];
		p[i]--;
	}
	
	vector<int> cyclelength(n, -1);
	vector<ii> cycles;
	for (int i = 0; i < n; ++i) {
		if (cyclelength[i] != -1) continue;
		int s = p[i], len = 1;
		while (s != i) { s = p[s]; len++; }
		s = i;
		while (cyclelength[s] == -1) {
			cyclelength[s] = len;
			s = p[s];
		}
		cycles.push_back({len, i});
	}
	
	sort(cycles.begin(), cycles.end());
	bool possible = true;
	if (cycles[0].first > 2) possible = false;
	
	vector<int> cycoflen(n + 3, -1);
	vector<ii> edges;
	// Root the tree
	int fi = cycles[0].second, flen = cycles[0].first;
	if (flen == 1) {
		cycoflen[1] = fi;
	} else { 
		edges.push_back({fi, p[fi]});
		cycoflen[2] = fi;
	}
		
	for (size_t ji = 1; ji < cycles.size() && possible; ++ji) {
		// Find suitable divisors
		int i = cycles[ji].second, len = cycles[ji].first, d = 1;
		for (d = 1; d <= len; ++d) {
			if (len % d == 0 && cycoflen[d] >= 0) break;
		}
		if (cycoflen[d] == -1) { possible = false; break; }
		
		// Attach cycle i to cycle cycoflen[d]
		int s = i, s2 = cycoflen[d];
		for (int C = 0; C < len; ++C) {
			edges.push_back({s, s2});
			s = p[s];
			s2 = p[s2];
		}
		cycoflen[len] = i;
	}
	
	if (!possible) cout << "NO" << endl;
	else {
		cout << "YES\n";
		for (size_t i = 0; i < edges.size(); ++i) {
			cout << (1 + edges[i].first) << ' ';
			cout << (1 + edges[i].second) << '\n';
		}
		cout << flush;
	}
	
	return 0;
}
