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

int main() {
	
	int N, M, K;
	scanf("%d %d %d", &N, &M, &K);
	
	vvi col(2, vi()), time(2, vi());
	col[0].assign(N, 0LL);
	col[1].assign(M, 0LL);
	time[0].assign(N, INF);
	time[1].assign(M, INF);
	
	while (K--) {
		int t, id, a;	
		scanf("%d %d %d", &t, &id, &a);
		col[t-1][id-1] = a;
		time[t-1][id-1] = K;
	}
	
	for (int r = 0; r < N; ++r) {
		for (int c = 0; c < M; ++c) {
			if (c > 0) cout << ' ';
			cout << (time[0][r] < time[1][c] ? col[0][r] : col[1][c]);
		}
		cout << endl;
	}
	
	return 0;
}
