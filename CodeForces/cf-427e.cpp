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

int MAGIC_CONSTANT = 30;

ll distance(vi &X, int N, int m, int M) {
	
	int l = m, r = m;
	while (l >= 0 && X[l] == X[m]) --l;
	while (r  < N && X[r] == X[m]) ++r;
	
	ll cost = 0LL;
	for (int i = 0; i <= l; i += M)
		cost += 2LL * (X[m] - X[i]);
	for (int j = N - 1; j >= r; j -= M)
		cost += 2LL * (X[j] - X[m]);
	
	return cost;
}

int main() {
	
	int N, M;
	scanf("%d %d", &N, &M);
	
	vi X(N, 0);
	for (int i = 0; i < N; ++i)
		scanf("%d", &X[i]);
	
	int l = 0, r = N - 1;
	while (r - l > MAGIC_CONSTANT) {
		int m1 = (2 * l + r) / 3;
		int m2 = (l + 2 * r) / 3;
		
		if (distance(X, N, m1, M) > distance(X, N, m2, M))
			l = m1;
		else	r = m2;
	}
	
	ll best = LLINF;
	while (l <= r) {
		best = min(best, distance(X, N, l, M));
		++l;
	}
	
	cout << best << endl;
	
	return 0;
}
