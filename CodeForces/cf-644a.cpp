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
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N, A, B;
	scanf("%d %d %d", &N, &A, &B);
	if (N > A * B) {
		cout << -1 << endl;
	} else {
		vvi b(A, vi(B, 0LL));
		for (int r = 0; N > 0 && r < A; ++r) {
			for (int c = ((r&1)?0:B-1); c != -1 && c != B && N > 0;
				c += ((r&1)?1:-1))
				b[r][c] = N--;
		}
		for (int r = 0; r < A; ++r)
			for (int c = 0; c < B; ++c)
				cout << b[r][c] << " \n"[c + 1 == B];
	}
	
	return 0;
}
