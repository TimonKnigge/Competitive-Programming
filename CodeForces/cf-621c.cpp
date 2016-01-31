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
	
	int N;
	ll P;
	cin >> N >> P;
	
	vector<ll> L(N+1, 0LL), R(N+1, 0LL);
	for (int i = 0; i < N; ++i) {
		int l, r;
		cin >> l >> r;
		L[i] = l;
		R[i] = r;
	}
	L[N] = L[0];
	R[N] = R[0];
	
	ld exp = 0.0;
	for (int i = 0; i < N; ++i) {
		ll t1 = R[i] - L[i] + 1, t2 = R[i+1] - L[i+1] + 1;
		ll p1 = R[i]   / P - (L[i] - 1) / P,
		   p2 = R[i+1] / P - (L[i+1]-1) / P;
		ld prob = 1.0 - (1.0 - ld(p1) / ld(t1)) * (1.0 - ld(p2) / ld(t2));
		exp += prob * 2000.0;
	}
	
	printf("%.7lf\n", double(exp));
	
	return 0;
}
