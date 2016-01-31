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

ll mod(ll a, ll m) {
	return (((a%m)+m)%m);
}
ll MOD = 1e9 + 7;

#define ITERATE_MATRIX(w) for (int r = 0; r < (w); ++r) \
			  for (int c = 0; c < (w); ++c)
template <class T, int N>
struct M {
	array<array<T,N>,N> m;
	M() { ITERATE_MATRIX(N) m[r][c] = 0; }
	static M id() {
		M I; for (int i = 0; i < N; ++i) I.m[i][i] = 1; return I;
	}
	M operator*(const M &rhs) const {
		M out;
		ITERATE_MATRIX(N) for (int i = 0; i < N; ++i)
			out.m[r][c] = mod(out.m[r][c] + mod(m[r][i] * rhs.m[i][c], MOD), MOD);
		return out;
	}
	M raise(int n) const {
		if(n == 0) return id();
		if(n == 1) return *this;
		auto r = (*this**this).raise(n / 2);
		return (n%2 ? *this*r : r);
	}
};

int main() {
	
	int N, B, K, X;
	scanf("%d %d %d %d", &N, &B, &K, &X);
	
	vi dig(10, 0);
	for (int i = 0; i < N; ++i) {
		int d;
		scanf("%d", &d);
		dig[d]++;
	}
	
	M<ll, 100> mat;
	for (int a = 0; a < X; ++a) {
		for (int d = 1; d < 10; ++d) {
			int b = mod(10 * a + d, X);
			mat.m[a][b] += dig[d];
		}
	}
	
	M<ll, 100> mres = mat.raise(B);
	cout << mres.m[0][K] << endl;
	
	return 0;
}
