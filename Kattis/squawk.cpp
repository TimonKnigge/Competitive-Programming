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
				out.m[r][c] += m[r][i] * rhs.m[i][c];
		return out;
	}
	M raise(int n) const {
		if(n == 0) return id();
		if(n == 1) return (*this);
		auto r = ((*this)*(*this)).raise(n / 2);
		return (n%2 ? (*this)*r : r);
	}
};
int main() {
	
	int n, m, s, t;
	scanf("%d %d %d %d", &n, &m, &s, &t);
	
	M<ll, 100> matrix;
	for (int e = 0; e < m; ++e) {
		int u, v;
		scanf("%d %d", &u, &v);
		matrix.m[u][v]++;
		matrix.m[v][u]++;
	}
//	ITERATE_MATRIX(n) cout << matrix.m[r][c]<<" \n"[c==n-1];
	M<ll, 100> mpow = matrix.raise(t);
//	ITERATE_MATRIX(n) cout << mpow.m[r][c]<<" \n"[c==n-1];
	ll ans = 0LL;
	for (int i = 0; i < n; ++i) ans += mpow.m[s][i];
	cout << ans << endl;
	
	return 0;
}
