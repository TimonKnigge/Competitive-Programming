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
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N, M;
	cin >> N >> M;
	vector<string> v(N, "");
	for (int i = 0; i < N; ++i) {
		cin >> v[i];
	}
	
	vvi comp(N, vi(M, 0));
	vi comp_size(1, 0);
	int C = 1;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (comp[i][j] != 0 || v[i][j] == '*') continue;
			comp_size.push_back(0);
			queue<ii> q;
			q.push({i, j});
			while (!q.empty()) {
				int x = q.front().first, y = q.front().second;
				q.pop();
				if (comp[x][y] > 0) continue;
				comp_size[C]++;
				comp[x][y] = C;
				if (x > 0 && v[x-1][y] == '.') q.push({x-1,y});
				if (y > 0 && v[x][y-1] == '.') q.push({x,y-1});
				if (x<N-1 && v[x+1][y] == '.') q.push({x+1,y});
				if (y<M-1 && v[x][y+1] == '.') q.push({x,y+1});
			}
			++C;
		}
	}
	
	int D[8] = {0, -1, 0, 1, 1, 0, -1, 0};
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (v[i][j] == '*') {
				set<int> st;
				int ans = 1;
				for (int k = 0; k < 4; ++k) {
					if (i+D[k*2] >= 0 && i+D[k*2]<N &&
					    j+D[k*2+1] >= 0 && j+D[k*2+1]<M) {
						if (st.find(comp[i+D[k*2]][j+D[k*2+1]]) != st.end())
							continue;
						st.insert(comp[i+D[k*2]][j+D[k*2+1]]);
						ans += comp_size[comp[i+D[k*2]][j+D[k*2+1]]];
					}
				}
				v[i][j] = char('0' + (ans % 10));
			}
		}
		cout << v[i] << '\n';
	}
	
	return 0;
}
