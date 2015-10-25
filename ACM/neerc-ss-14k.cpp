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
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

int main() {
	
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; ++t) {
		int N;	
		scanf("%d", &N);
		
		vvi lst(N, vi(N, -1));
		vvi inv(N, vi(N, -1));
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				int x;
				scanf("%d", &x);
				x--;
				lst[i][j] = x;
				inv[i][x] = j;
			}
		}
		
		vii e;
		vi rel(N, 1);
		vb cut(N, false);
		
		vi laststop(N, 0);
		queue<int> q;
		for (int i = 0; i < N; ++i) q.push(i);
		
		while (!q.empty()) {
			int i = q.front(); q.pop();
			if (cut[i]) continue;
			
			while (rel[i] < N && cut[lst[i][rel[i]]]) rel[i]++;
			if (rel[i] == N) continue;
			int j = lst[i][rel[i]];
			// Is i a leaf connected to j?
			// For all uncut vertices we want
			// inv[i] > inv[j]
			bool success = true;
			for (int k = laststop[i]; success && k < N; ++k) {
				if (k == i) continue;
				if (cut[k]) continue;
				if (inv[k][i] > inv[k][j]) continue;
				success = false;
				laststop[i] = k;
			}
			if (success) {
				e.push_back({i, j});
				cut[i] = true;
			} else q.push(i);
		}
		
		for (ii uv : e) printf("%d %d\n", uv.first + 1, 1 + uv.second);
		if (t < T) printf("\n");
	}
	
	return 0;
}
