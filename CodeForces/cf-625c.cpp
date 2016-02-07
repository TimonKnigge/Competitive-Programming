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
	
	int N, K;
	scanf("%d %d", &N, &K);
	--K;
	
	vvi table(N, vi(N, -1));
	int L = 1;
	for (int r = 0; r < N; ++r) {
		for (int c = 0; c < K; ++c)
			table[r][c] = L++;
	}
	for (int r = 0; r < N; ++r) {
		for (int c = K; c < N; ++c)
			table[r][c] = L++;
	}
	
	int sum = 0;
	for (int r = 0; r < N; ++r)
		sum += table[r][K];
	cout << sum << endl;
	for (int r = 0; r < N; ++r)
		for (int c = 0; c < N; ++c)
			cout << table[r][c] << " \n"[c == N - 1];
	
	return 0;
}
