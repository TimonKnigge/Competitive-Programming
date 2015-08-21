#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;

struct uint128 {
	unsigned long long i1, i2;
	uint128(long long i1 = 1, long long i2 = 0)
		: i1(i1), i2(i2) { }
};
uint128 operator&(uint128 const &lhs, uint128 const &rhs) {
	return uint128(lhs.i1 & rhs.i1, lhs.i2 & rhs.i2);
}
uint128 operator|(uint128 const &lhs, uint128 const &rhs) {
	return uint128(lhs.i1 | rhs.i1, lhs.i2 | rhs.i2);
}
uint128 operator~(uint128 const &v) {
	return uint128(~v.i1, ~v.i2);
}

// Useful helpers
bool iszero(uint128 const &v) {
	return v.i1 == 0 && v.i2 == 0;
}
int fnonzero(uint128 const &v) {
	// Assumes !iszero(v)!
	int i = 0;
	unsigned long long u = (v.i1 == 0 ? v.i2 : v.i1);
	for (; i < 64; ++i) {
		if ((u&1)==1) break;
		u >>= 1;
	}
	return (i + (v.i1 == 0 ? 64 : 0));
}
bool bitset(uint128 const &v, int b) {
	if (b < 64) return (((v.i1 >> b) & 1) == 1);
	else return (((v.i2 >> (b - 64)) & 1) == 1);
}
uint128 set1(int v) {
	return uint128(v < 64 ? (1ULL << v) : 0, v < 64 ? 0 : (1ULL << (v - 64)));
}
uint128 set(uint128 const &v, int b) {
	if (b < 64) return uint128(v.i1 | (1ULL << b), v.i2);
	else return uint128(v.i1, v.i2 | (1ULL << (b - 64)));
}

bool adj[128][128];
uint128 N[128];
int n;

struct RPX {
	uint128 R, P, X;
};

int BronKerbosch2(uint128 P) {
	uint128 R(0, 0), X(0, 0);
	int r = 0;
	stack<RPX> st;
	st.push({R, P, X});
	while (!st.empty()) {
		RPX rpx = st.top();
		st.pop();
		if (iszero(rpx.P) && iszero(rpx.X))
			r++;
		else {
			int u = fnonzero(rpx.P | X);
			for (int v = 0; v < n; ++v) {
				if (!bitset(rpx.P, v)) continue;
				if (adj[u][v]) continue;
				uint128 vv = set1(v);
				st.push({rpx.R | vv, rpx.P & N[v], rpx.X & N[v]});
				rpx.P = (rpx.P &~ vv);
				rpx.X = (X | vv);
			}
		}
		
		if (r > 1000) return r;
	}
	return r;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	while (cin >> n) {
		int m;
		cin >> m;
		if (n == 0 && m == 0) break;
		
		uint128 P(0, 0);
		for (int i = 0; i < n; ++i) {
			for (int j = i; j < n; ++j)
				adj[i][j] = adj[j][i] = false;
			N[i] = uint128(0, 0);
			P = (P | set1(i));
		}

		for (int i = 0; i < m; ++i) {
			int a, b;
			cin >> a >> b;
			a--; b--;
			adj[a][b] = true;
			N[a] = (N[a] | set1(b));
			N[b] = (N[b] | set1(a));
		}

		int res = BronKerbosch2(P); //uint128(0, 0), P, uint128(0, 0));
		if (res > 1000)
			cout << "Too many maximal sets of friends.\n";
		else
			cout << res << '\n';
		cout << flush;
	}
	
	return 0;
}

