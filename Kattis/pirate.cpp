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

void all_nearest_smaller_values1(vi &a, vi &b) {
	b[0] = -1;
	for (int i = 1; i < b.size(); ++i) {
		b[i] = i - 1;
		while (b[i] >= 0 && a[i] <= a[b[i]])
			b[i] = b[b[i]];
	}
}
void all_nearest_smaller_values2(vi &a, vi &b) {
	b[a.size() - 1] = a.size();
	for (int i = int(b.size()) - 2; i >= 0; --i) {
		b[i] = i + 1;
		while (b[i] < a.size() && a[i] <= a[b[i]])
			b[i] = b[b[i]];
	}
}

inline ll solve_single(ll w, ll b, ll d, ll M, ll N) {
	ld h = ld(d) / (1.0 - ld(w*b) / ld(M*N));
	ll H = ll(h) - 1;
	while (H + 1 < d + ((H + 1) * w * b) / (M * N)
		|| (H + 1 == d + ((H + 1) * w * b) / (M * N)
		 && (H + 1) * w * b % (M * N) > 0LL))
		++H;
	return w * b * H;
}

ll solve(ll A, ll B, ll M, ll N, vvi &D) {
	
	ll opt = 0LL;
	vi D_c(N, LLINF), ansvl(N, 0LL), ansvr(N, 0LL);
	
	for (int l = 0; l < M; ++l) {
		
		for (int i = 0; i < N; ++i)
			D_c[i] = LLINF;
		
		for (int r = l; r < M; ++r) {
			
			for (int i = 0; i < N; ++i)
				D_c[i] = min(D_c[i], D[r][i]);
			
			all_nearest_smaller_values1(D_c, ansvl);
			all_nearest_smaller_values2(D_c, ansvr);
			
			for (int i = 0; i < N; ++i) {
				ll d = D_c[i];
				ll w = r - l + 1;
				ll b = ansvr[i] - ansvl[i] - 1;
				
				opt = max(opt, max(
					solve_single(min(w, A), min(b, B), d, M, N),
					solve_single(min(w, B), min(b, A), d, M, N)));
			}
		}
	}
			
	return opt;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int A, B, M, N;
	scanf("%d %d %d %d", &A, &B, &M, &N);
	
	vvi D(M, vi(N, 0LL));
	for (int i = 0; i < M; ++i)
		for (int j = 0, v; j < N; ++j)
			scanf("%d", &v), D[i][j] = ll(v);
	
	cout << solve(A, B, M, N, D) << endl;
	
	return 0;
}
