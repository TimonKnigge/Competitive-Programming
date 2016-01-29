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

ll sq(ll x) { return x * x; }
ll det(ll x1, ll y1, ll x2, ll y2) {
	return x1 * y2 - x2 * y1;
}

int main() {
	
	int N;
	scanf("%d", &N);
	
	vector<ll> X(N, 0LL), Y(N, 0LL);
	for (int i = 0; i < N; ++i) {
		int x, y;
		scanf("%d %d", &x, &y);
		X[i] = x;
		Y[i] = y;
	}
	
	int I1 = 0, I2 = -1, I3 = -1;
	ll d = LLINF;
	for (int i = 1; i < N; ++i) {
		if (d > sq(X[0] - X[i]) + sq(Y[0] - Y[i])) {
			I2 = i;
			d = sq(X[0] - X[i]) + sq(Y[0] - Y[i]);
		}
	}
	
	ll ar = LLINF;
	for (int j = 1; j < N; ++j) {
		if (j == I2) continue;
		ll tar = abs(det(X[I2] - X[I1], Y[I2] - Y[I1], X[j] - X[I1], Y[j] - Y[I1]));
		if (ar > tar && tar > 0) {
			ar = tar;
			I3 = j;
		}
	}
	
	I1++;
	I2++;
	I3++;
	
	cout << I1 << " " << I2 << " " << I3 << endl;
	
	return 0;
}
