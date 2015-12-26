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
	
	freopen("bcount.in", "r", stdin);
	freopen("bcount.out", "w", stdout);
	
	int N, Q;
	scanf("%d %d", &N, &Q);
	vi type(N, 0);
	for (int i = 0; i < N; ++i) {
		int v;
		scanf("%d", &v);
		type[i] = v - 1;
	}
	
	vi p[3];
	for (int i = 0; i < 3; ++i) {
		p[i].assign(N + 1, 0);
		for (int j = 0; j < N; ++j)
			p[i][j + 1] = p[i][j] + (type[j] == i ? 1 : 0);
	}
	
	while (Q--) {
		int l, r;
		scanf("%d %d", &l, &r);
		cout << (p[0][r]-p[0][l-1]) << ' ';
		cout << (p[1][r]-p[1][l-1]) << ' ';
		cout << (p[2][r]-p[2][l-1]) <<'\n';
	}
	cout << flush;
	
	return 0;
}
