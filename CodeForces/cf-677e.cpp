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

constexpr int MX = 11;
int dx[8] = { 0, 0,-1, 1,-1,-1, 1, 1};
int dy[8] = {-1, 1, 0, 0,-1, 1,-1, 1};
int prod[8][MX][1000][1000];

int N;

inline int calc(int da, int i, int j) {
	int mx = INF;
	for (int a = 0; a < 4; ++a) {
		int d = 0;
		for (int L = MX-1; L >= 0; --L) {
			if (prod[da+a][L][i + d * dx[a+da]][j + d * dy[a + da]] == -1) continue;
			if (i + d * dx[a + da] < 0 || i + d * dx[a + da] >= N)
				continue;
			if (j + d * dy[a + da] < 0 || j + d * dy[a + da] >= N)
				continue;
			d += (1<<L);
		}
		mx = min(mx, d);
	}
	return mx;
}

inline int calcv(int a, int i, int j, int dd) {
	int v = 0;
	int d = 0;
	for (int L = MX-1; L >= 0; --L) {
		if (((dd>>L)&1) != 1) continue;
		v += prod[a][L][i + d * dx[a]][j + d * dy[a]];
		d += (1<<L);
	}
	return v;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> N >> ws;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			char c;
			cin >> c;
			int v = c-'0';
			for (int d = 0; d < 8; ++d) {
				if (v == 0) prod[d][0][i][j] = -1;
				if (v == 1) prod[d][0][i][j] = 0;
				if (v == 2) prod[d][0][i][j] = 1;
				if (v == 3) prod[d][0][i][j] = (1 << (MX));
			}
		}
	}
	
	for (int d = 0; d < 8; ++d)
		for (int l = 1, m = 1; l < MX; ++l, m <<= 1) {
			for (int i = 0; i < N; ++i)
				for (int j = 0; j < N; ++j) {
					if (i + dx[d] * m < 0 || i + dx[d] * m >= N) {
						prod[d][l][i][j] = -1;
						continue;
					}
					if (j + dy[d] * m < 0 || j + dy[d] * m >= N) {
						prod[d][l][i][j] = -1;
						continue;
					}
					int v1 = prod[d][l-1][i][j], v2 = prod[d][l-1][i + dx[d]*m][j + dy[d]*m];
					if (v1 == -1 || v2 == -1)
						prod[d][l][i][j] = -1;
					else	prod[d][l][i][j] = v1+v2;
				}
		}
	
	int vand = (1<<MX)-1;
	
	set<ii> vals;
	
	for (int da = 0; da < 2; ++da)
	for (int i = 0; i < N; ++i)
	for (int j = 0; j < N; ++j) {
		if (prod[0][0][i][j] == -1) continue;
		int d = calc(4*da, i, j);
		int twos = 0, threes = 0;
		if (prod[0][0][i][j] == 1) twos -= 3;
		if (prod[0][0][i][j]  > 1) threes -= 3;
		for (int a = 0; a < 4; ++a) {
			int v = calcv(4*da + a, i, j, d);
			twos += (v&vand);
			threes += ((v>>MX)&vand);
		}
//		cerr << i << ' '<<j << ' '<<d << ' ' << twos << ' ' << threes<< endl;
		vals.insert({twos, threes});
	}
	
	if (vals.size() == 0) cout << 0 << endl;
	else {
		ii best = *vals.begin();
		ld l2l3 = 0.630929753571457437099;
		for (ii v : vals) {
			if (ld(best.second - v.second) < l2l3 * ld(v.first - best.first))
				best = v;
		}
		
		ll ans = 1LL, MOD = 1e9+7;;
		for (int i = 0; i < best.first; ++i)
			ans = (ans*2LL) % MOD;
		for (int i = 0; i < best.second; ++i)
			ans = (ans*3LL) % MOD;
		cout << ans << endl;
	}
	
	return 0;
}
