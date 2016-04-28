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
	
	int N, M, Q;
	cin >> N >> M >> Q;
	
	vector<vector<pair<ii, ll> > > B(N, vector<pair<ii, ll> >
		(M, {{0LL, 0LL}, 0LL}));
	for (int r = 0; r < N; ++r)
		for (int c = 0; c < M; ++c)
			B[r][c] = {{r, c}, 0LL};
	
	while (Q--) {
		int t;
		cin >> t;
		
		switch (t) {
			case 1:
				int r;
				cin >> r;
				--r;
				for (int i = 1; i < M; ++i)
					swap(B[r][i - 1], B[r][i]);
				break;
			case 2:
				int c;
				cin >> c;
				--c;
				for (int i = 1; i < N; ++i)
					swap(B[i - 1][c], B[i][c]);
				break;
			default:
				int ri, ci, xi;
				cin >> ri >> ci >> xi;
				--ri; --ci;
				B[ri][ci].second = xi;
				break;
		}
	}
	
	vvi res(N, vi(M, 0LL));
	for (int r = 0; r < N; ++r)
		for (int c = 0; c < M; ++c)
			res[B[r][c].first.first]
			   [B[r][c].first.second] = B[r][c].second;
	
	for (int r = 0; r < N; ++r)
		for (int c = 0; c < M; ++c)
			cout << res[r][c] << " \n"[c + 1 == M];
	
	return 0;
}
