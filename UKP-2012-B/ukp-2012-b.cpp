#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <bitset>
#include <algorithm>
#include <functional>
#include <string>
#include <math.h>

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef long long ll;

int n, k, m;
vvi edges;
vi deg;
vector<bool> keep;

int nextTheory() {
	int degout = -1, u = -1;
	for (int i = 0; i < n; ++i) {
		if (keep[i] && deg[i] > degout) {
			degout = deg[i];
			u = i;
		}
	}
	return u;
}

int main(){
	int T;
	cin >> T;

	for (int t = 1; t <= T; ++t){
		cin >> n >> k >> m;

		edges = vvi(n);
		deg = vi(n);
		for (int i = 0; i < m; ++i) {
			int xi, yi;
			cin >> xi >> yi;
			xi--;
			yi--;
			edges[xi].push_back(yi);
			edges[yi].push_back(xi);
			deg[xi]++;
			deg[yi]++;
		}

		int theories = 0;
		keep = vector<bool>(n, true);
		while (true) {
			int rm = nextTheory();
			if (deg[rm] == 0) 
				break;
			else {
				theories++;
				keep[rm] = false;
				for (int v : edges[rm])
					deg[v]--;
			}
		}

		if (theories > k)
			cout << "IMPOSSIBLE" << endl;
		else
			cout << theories << endl;
	}

	return 0;
}