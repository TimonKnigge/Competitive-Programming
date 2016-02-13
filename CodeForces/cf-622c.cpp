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
	
	int N, M;
	scanf("%d %d", &N, &M);
	
	vi A(N, 0);
	for (int i = 0; i < N; ++i) {
		scanf("%d", &A[i]);
	}
	
	vi prev(N, -1);
	for (int i = 1; i < N; ++i) {
		if (A[i] != A[i - 1])
			prev[i] = i - 1;
		else	prev[i] = prev[i - 1];
	}
	
	while (M--) {
		int l, r, x;
		scanf("%d %d %d", &l, &r, &x);
		
		--l;
		--r;
		if (A[r] != x) cout << 1+r << '\n';
		else if (l <= prev[r]) cout << 1+prev[r] << '\n';
		else cout << -1 << '\n';
	}
	cout << flush;
	
	return 0;
}
