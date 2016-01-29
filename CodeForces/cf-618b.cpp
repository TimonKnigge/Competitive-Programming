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

void solve(int I, int N, vi &P, vi &R, vvi &B) {
	int loc = 0;
	for (int i = 0; i < int(R.size()); ++i) {
		bool m = true;
		for (int j = 0; j < int(R.size()); ++j) {
			if (j == i) continue;
			m = m && (B[R[i]][R[j]] == I);
		}
		if (m) loc = i;
	}
	
	P[R[loc]] = I;
	if (I == N) return;
	else {
		R.erase(R.begin() + loc);
		solve(I + 1, N, P, R, B);
	}
}

int main() {
	
	int N;
	scanf("%d", &N);
	
	vvi B(N, vi(N, 0));
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			scanf("%d", &B[i][j]);
	
	vi P(N, -1);
	vi R(N, -1);
	for (int i = 0; i < N; ++i)
		R[i] = i;
	
	solve(1, N, P, R, B);
	
	for (int i = 0; i < N; ++i)
		cout << P[i] << " \n"[i == N - 1];
	
	return 0;
}
