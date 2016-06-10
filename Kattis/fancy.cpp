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
const ll LLINF = 9000000000000000;

ll det(ll x1, ll y1, ll x2, ll y2) {
	return x1*y2 - x2*y1;
}
ll det(ll x1, ll y1, ll x2, ll y2, ll x3, ll y3) {
	return det(x1-x3,y1-y3,x2-x3,y2-y3);
}

void minpow(vvi &A, int k, vvi &R) {
	if (k == 1) {
		R.assign(A.size(), vi(A.size(), 0LL));
		for (size_t i = 0; i < A.size(); ++i)
			for (size_t j = 0; j < A.size(); ++j)
				R[i][j] = A[i][j];
		return;
	}
	vvi AA(A.size(), vi(A.size(), LLINF));
	for (size_t m = 0; m < A.size(); ++m)
		for (size_t f = 0; f < A.size(); ++f)
			for (size_t l = 0; l < A.size(); ++l)
				AA[f][l] = min(AA[f][l], A[f][m] + A[m][l]);
	if (k&1) {
		vvi F;
		minpow(AA, k/2, F);
		R.assign(A.size(), vi(A.size(), LLINF));
		for (size_t m = 0; m < A.size(); ++m)
			for (size_t f = 0; f < A.size(); ++f)
				for (size_t l = 0; l < A.size(); ++l)
					R[f][l] = min(R[f][l], F[f][m] + A[m][l]);
	} else minpow(AA, k/2, R);
}

int main() {
	
	int N, M, K;
	scanf("%d %d %d", &N, &M, &K);
	
	vii onions;
	for (int n = 0, x, y; n < N; ++n)
		scanf("%d %d", &x, &y),
		onions.push_back({ll(x), ll(y)});
	
	//cw
	vii fence;
	for (int m = 0, x, y; m < M; ++m)
		scanf("%d %d", &x, &y),
		fence.push_back({ll(x), ll(y)});
	
	vii ronions;
	for (ii on : onions) {
		bool y = true;
		for (int i = 0; i < M; ++i)
			y = y && !(det(fence[(i+1)%M].first, fence[(i+1)%M].second, on.first, on.second, fence[i].first, fence[i].second) >= 0);
		if (y) ronions.push_back(on);
	}
	
	cerr << "Onions fixed, " << ronions.size() << " left" << endl;
	
	vvi cutoff(M, vi(M, LLINF));
	for (int i = 0; i < M; ++i)
		for (int j = 0; j < M; ++j) {
			if (i == j) continue;
			cutoff[i][j] = 0LL;
			for (ii on : ronions) {
				if (det(fence[j].first, fence[j].second, on.first, on.second, fence[i].first, fence[i].second) >= 0)
					++cutoff[i][j];
			}
		}
	
	cerr << "Cutoff calculated" << endl;
	
//	for (size_t i = 0; i < cutoff.size(); ++i) {
//		for (size_t j = 0; j < cutoff.size(); ++j)
//			cerr << ' ' << cutoff[i][j];
//		cerr << endl;
//	}
	
	vvi R;
	minpow(cutoff, K, R);
	
//	for (size_t i = 0; i < R.size(); ++i) {
//		for (size_t j = 0; j < R.size(); ++j)
//			cerr << ' ' << R[i][j];
//		cerr << endl;
//	}
	
	ll ans = ronions.size();
	for (size_t i = 0; i < R.size(); ++i)
		ans = min(ans, R[i][i]);
	
	cout << (int(ronions.size()) - ans) << endl;
	
	return 0;
}
