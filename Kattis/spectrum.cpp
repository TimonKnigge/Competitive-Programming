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

ld range[200][200];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N, M;
	cin >> N >> M;
	
	vector<ld> A(N, 0LL);
	vector<ld> P(N, 0LL);
	vector<ld> S(N, 0LL);
	vector<ld> SQ(N, 0LL);
	for (int i = 1; i <= N; ++i) {
		cin >> A[i-1];
		P[i-1] = A[i-1] + (i > 1 ? P[i - 2] : 0LL);
		S[i-1] = A[i-1] * i + (i > 1 ? S[i-2] : 0LL);
		SQ[i-1] = A[i-1]*i*i + (i > 1 ? SQ[i-2] : 0LL);
	}
	
	for (int l = 0; l < N; ++l)
		for (int r = l; r < N; ++r) {
			ld a = P[r] - (l > 0 ? P[l-1] : 0LL);
			ld b = -2LL * (S[r] - (l > 0 ? S[l-1] : 0LL));
			ld c = SQ[r] - (l > 0 ? SQ[l-1] : 0LL);
			if (abs(a) < 1e-6)
				range[l][r] = 0.0;
			else	range[l][r] = - b*b / (4.0*a)
						+ c;
		}
	
	vector<vector<ld> > opt(M, vector<ld>(N, 1e300));
	for (int r = 0; r < N; ++r) {
		opt[0][r] = range[0][r];
	}
	
	for (int i = 1; i < M; ++i) {
		for (int r = 0; r < N; ++r) {
			opt[i][r] = range[0][r];
			for (int l = 1; l <= r; ++l)
				opt[i][r] = min(opt[i][r],
					range[l][r] + (l > 0 ?
						opt[i-1][l-1] : 0.0));
		}
	}
	printf("%.10lf\n", double(opt[M - 1][N - 1]));

	return 0;
}
