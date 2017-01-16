#include <iostream> 
#include <fstream>
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

void mf(int &v, int w) { if (v < w) v = w; }

int dp[52][52][52][52];
int f(vi &A, int N, int i, int j, int k, int l) {
	// Verify i,j,k,l
	if (i < 0 || j < 0 || k < 0 || l < 0) return 0;
	if (i >= N || j >= N || k >= N || l >= N) return 0;
	if (j > k) return 0;
	
	bool jfree = j != i && j != l;
	bool kfree = k != i && k != l;

	if (j == k) {
		return jfree && kfree && A[i] <= A[k] && A[k] <= A[l];
	}
	
	if (dp[i][j][k][l] != 0)
		return dp[i][j][k][l];
	
	// We are now considering [0..j] + [k..N-1].
	// The last value left was A[i], rigth was A[l];
	
	// Don't use j or k.
	mf(dp[i][j][k][l], f(A, N, i, j+1, k-1, l));
	mf(dp[i][j][k][l], f(A, N, i, j, k-1, l));
	
	// Don't swap
	{
		// Use j.
		if (jfree && A[i] <= A[j] && A[j] <= A[l])
			mf(dp[i][j][k][l], 1+f(A, N, j, j+1, k, l));
		// Use k.
		if (kfree && A[i] <= A[k] && A[k] <= A[l])
			mf(dp[i][j][k][l], 1+f(A, N, i, j, k-1, k));
		// Use j,k.
		if (jfree && kfree && A[i] <= A[j] && A[j] <= A[k] && A[k] <= A[l])
			mf(dp[i][j][k][l], 2+f(A, N, j, j+1, k-1, k));
	}
	// Swap j and k.
	if (jfree && kfree) {
		// Use A[j] on position k, don't use A[k] on position j.
		if (A[i] <= A[j] && A[j] <= A[l])
			mf(dp[i][j][k][l], 1+f(A, N, i, j+1, k-1, j));
		// Use A[k] on position j, don't use A[j] on position k.
		if (A[i] <= A[k] && A[k] <= A[l])
			mf(dp[i][j][k][l], 1+f(A, N, k, j+1, k-1, l));
		// Use both A[k] and A[j], on switched positions.
		if (A[i] <= A[k] && A[k] <= A[j] && A[j] <= A[l])
			mf(dp[i][j][k][l], 2+f(A, N, k, j+1, k-1, j));
	}
	
	return dp[i][j][k][l];
}

int main() {
	ifstream fin("subrev.in");
	
	int N;
	fin >> N;
	
	vi A(N, 0LL);
	for (ll &v : A) fin >> v;
	A.insert(A.begin(), -LLINF);
	A.push_back(LLINF);
	N += 2;

	for (int i = 0; i < 52; ++i)
	for (int j = 0; j < 52; ++j)
	for (int k = 0; k < 52; ++k)
	for (int l = 0; l < 52; ++l)
		dp[i][j][k][l] = 0;
	
	for (int len = 0; len < N; ++len)
	for (int j = 1, k = len + 1; k < N - 1; ++j, ++k) {
		for (int i = 0; i < N; ++i) if (i <= j || k <= i)
		for (int l = 0; l < N; ++l) if (l <= j || k <= l && l != i) {
			bool jfree = j != i && j != l;
			bool kfree = k != i && k != l;
			if (j == k) {
				dp[i][j][k][l] = jfree && kfree && A[i] <= A[k] && A[k] <= A[l];
				continue;
			}

			// We are now considering [0..j] + [k..N-1].
			// The last value left was A[i], rigth was A[l];

			// Don't use j or k.
			mf(dp[i][j][k][l], dp[i][j+1][k][l]);
			mf(dp[i][j][k][l], dp[i][j][k-1][l]);

			// Don't swap
			{
				// Use j.
				if (jfree && A[i] <= A[j] && A[j] <= A[l])
					mf(dp[i][j][k][l], 1+dp[j][j+1][k][l]);
				// Use k.
				if (kfree && A[i] <= A[k] && A[k] <= A[l])
					mf(dp[i][j][k][l], 1+dp[i][j][k-1][k]);
				// Use j,k.
				if (jfree && kfree && A[i] <= A[j] && A[j] <= A[k] && A[k] <= A[l])
					mf(dp[i][j][k][l], 2+dp[j][j+1][k-1][k]);
			}
			// Swap j and k.
			if (jfree && kfree) {
				// Use A[j] on position k, don't use A[k] on position j.
				if (A[i] <= A[j] && A[j] <= A[l])
					mf(dp[i][j][k][l], 1+dp[i][j+1][k-1][j]);
				// Use A[k] on position j, don't use A[j] on position k.
				if (A[i] <= A[k] && A[k] <= A[l])
					mf(dp[i][j][k][l], 1+dp[k][j+1][k-1][l]);
				// Use both A[k] and A[j], on switched positions.
				if (A[i] <= A[k] && A[k] <= A[j] && A[j] <= A[l])
					mf(dp[i][j][k][l], 2+dp[k][j+1][k-1][j]);
			}
		}
	}

	ofstream fout("subrev.out");
	fout << dp[0][1][N-2][N-1] << endl;
	
	return 0;
}
