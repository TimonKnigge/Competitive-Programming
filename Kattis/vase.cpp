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

ostream &operator<<(ostream &os, uint128 const &u) {
	return os << u.i1 << ' ' << u.i2;
}

// Useful helpers
bool iszero(uint128 const &v) {
	return v.i1 == 0 && v.i2 == 0;
}
int fnonzero(uint128 const &v) {
	// Assumes !iszero(v)!
	if (v.i1 == 0)
		return (64 + __builtin_ctzll(v.i2));
	else
		return __builtin_ctzll(v.i1);
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

unsigned long long f36 = (1ULL << 36) - 1ULL;

bool adj[72][72];
uint128 N[72];
int n = 72;

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
		if (iszero(rpx.P) && iszero(rpx.X)) {
			unsigned long long Ri1 = rpx.R.i1;
			unsigned long long Ri2 = rpx.R.i2;
			unsigned long long lft = (Ri1 & f36);
			int lsize = __builtin_popcountll(lft);
			int rsize = __builtin_popcountll(Ri1)
				+ __builtin_popcountll(Ri2) - lsize;
//			cout << lsize << ' ' << rsize << endl;
			r = max(r, min(lsize, rsize));
		} else {
			int u = fnonzero(rpx.P | rpx.X);
			for (int v = 0; v < n; ++v) {
				if (!bitset(rpx.P, v)) continue;
				if (adj[u][v]) continue;
				uint128 vv = set1(v);
				st.push({rpx.R | vv, rpx.P & N[v], rpx.X & N[v]});
				rpx.P = (rpx.P &~ vv);
				rpx.X = (rpx.X | vv);
			}
		}
	}
	return r;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int T;
	cin >> T;
	for (int t = 1; t <= T; ++t) {
		int m;
		cin >> m;
		
		uint128 P(0, 0);
		for (int i = 0; i < 72; ++i) N[i] = uint128(0, 0);
		for (int i = 0; i < 36; ++i) {
			for (int j = 0; j <= i; ++j) {
				adj[i][j] = adj[j][i] = (j != i);
				adj[i + 36][j] = adj[j][i + 36] = false;
				adj[i][j + 36] = adj[j + 36][i] = false;
				adj[i+36][j+36] = adj[j+36][i+36] = (j != i);
				if (j != i) {
					N[i] = (N[i] | set1(j));
					N[j] = (N[j] | set1(i));
					N[i+36] = (N[i+36] | set1(j+36));
					N[j+36] = (N[j+36] | set1(i+36));
				}
			}
			P = (P | (set1(i) | set1(i + 36)));
		}
		
		for (int i = 0; i < m; ++i) {
			int s, d;
			cin >> s >> d;
			s--; d--;
			
			if (adj[s][d+36]) continue;
			
			adj[s][d+36] = true;
			adj[d+36][s] = true;
			N[s] = (N[s] | set1(d + 36));
			N[d + 36] = (N[d + 36] | set1(s));
		}
		
		cout << BronKerbosch2(P) << '\n';
	}
	cout << flush;
	
	return 0;
}
