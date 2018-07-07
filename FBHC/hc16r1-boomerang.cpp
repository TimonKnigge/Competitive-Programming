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
using uint = unsigned int;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

#define popcount(x) __builtin_popcount(x)
/*
// Iterate over all k-subsets of a set of size N
int mask = (1 << k) - 1;
while (!(mask & 1 << N)) {
	// Decode mask here
	int lo = mask & ~(mask - 1);
	int lz = (mask + lo) & ~mask;
	mask |= lz;
	mask &= ~(lz - 1);
	mask |= ((lz / lo) >> 1) - 1;
}*/

void fmax(int &l, int r) { if (l < r) l = r; }
void fmin(int &l, int r) { if (l > r) l = r; }

int la(int v, int K) {
	if (v == K) return 0;
	else return (1 << (K - v - 1));
}

int main() {
	
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; ++t) {
		int N;
		scanf("%d", &N);
		
		bool W[16][16];
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j) {
				int v;
				scanf("%d", &v);
				W[i][j] = (v == 1);
			}
		
		vvi candef(N, vi());
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j)
				if (W[i][j]) candef[i].push_back(j);
		
		vi dp(1 << N, 0);
		// dp[S]: bitmask of who can win in group S
		vi winsmax(N, 0);
		vi winsmin(N, INF); // self explanatory
		
		// Solve groups of size 1,2 in O(N^2)
		for (int i = 0; i < N; ++i) {
			dp[1 << i] = 1 << i;
			for (int j : candef[i]) {
				dp[(1<<i)|(1<<j)] = 1 << i;
				winsmin[j] = 0;
				winsmax[i] = 1;
			}
		}
		
		// Solve groups of size 4 in O(N^4)
		if (N > 2) {
			for (int i = 0; i < N; ++i)
			for (int j : candef[i])
				for (int k : candef[i])
				for (int l = 0; l < N; ++l)
					if (W[k][l]) {
						int mask = (1<<i)|
							   (1<<j)|
							   (1<<k)|
							   (1<<l);
						if (popcount(mask)!=4) continue;
						dp[mask] |= 1 << i;
						fmax(winsmax[i], 2);
						fmin(winsmin[j], 1);
					}
		}
		
		// Groups of size 8 in O(binom(N, 8)*binom(8, 4) * (4 + 4 * 8))
		if (N > 4) {
			
			// Iterate over all 8-subsets of a set of size N
			int mask = (1 << 8) - 1;
			while (!(mask & 1 << N)) {
				// retrieve groups
				vi S;
				for (int i = 0; i < N; ++i)
					if (((mask>>i)&1)==1) S.push_back(i);


				// |S| = 8
				// iterate over all 4-subsets of S
				int mask2 = (1<<4) - 1;
				while (!(mask2 & 1 << 8)) {
					int mk = 0;
					for (int j = 0; j < 8; ++j)
						if (((mask2>>j)&1)==1)
						mk |= (1<<S[j]);
					
					// mk is a 4-subset of S
					// the rest is mask&~mk
					int rest = mask &~ mk;
					for (int j : S) {
						if (((mk>>j)&1)!=1) continue;
						if (((dp[mk]>>j)&1)!=1)
							continue;
						// j \in mk
						for (int i : S) {
							if (((mk>>i)&1)==1)
								continue;
							if (!W[j][i]) continue;
							// i \in S \ mk, 
							// j defeats i
							if (((dp[rest]>>i)&1)!=1)
								continue;
							dp[mask] |= 1<<j;
							fmax(winsmax[j], 3);
							fmin(winsmin[i], 2);
						}
					}
					int lo2 = mask2 & ~(mask2 - 1);
					int lz2 = (mask2 + lo2)& ~mask2;

					mask2 |= lz2;
					mask2 &= ~(lz2 - 1);
					mask2 |= (lz2/lo2/2) - 1;
				}
				
				int lo = mask & ~(mask - 1);
				int lz = (mask + lo) & ~mask;
				mask |= lz;
				mask &= ~(lz - 1);
				mask |= (lz / lo / 2) - 1;
			}
		}
		
		// Groups of size 16 in O(binom(N, 8) * N^2)
		if (N > 8) {
			int mask = (1 << 8) - 1;
			while (!(mask & 1 << N)) {
				
				int rest = ((1<<N) - 1) &~ mask;
				for (int i = 0; i < N; ++i) {
					if (((mask>>i)&1)!=1) continue;
					if (((dp[mask]>>i)&1)!=1) continue;
					for (int j = 0; j < N; ++j) {
						if (((rest>>j)&1)!=1) continue;
						if (!W[i][j]) continue;
						if (((dp[rest]>>j)&1)!=1)
							continue;
						dp[1 << N] |= 1 << i;
						fmax(winsmax[i], 4);
						fmin(winsmin[j], 3);
					}
				}
				
				int lo = mask & ~(mask - 1);
				int lz = (mask + lo) & ~mask;
				mask |= lz;
				mask &= ~(lz - 1);
				mask |= ((lz / lo) >> 1) - 1;
			}
		}
		
		int K = 0;
		while ((1 << K) != N) ++K;
		
		cout << "Case #" << t << ":" << '\n';
		for (int i = 0; i < N; ++i) {
//			cerr << winsmin[i] << ' ' << winsmax[i] << endl;
			fmin(winsmin[i], winsmax[i]);
			fmax(winsmax[i], winsmin[i]);
			cout << (1 + la(winsmax[i], K));
			cout << " ";
			cout << (1 + la(winsmin[i], K));
			
//			cout << " (" << winsmax[i] << " " << winsmin[i] << ")";
			cout << "\n";
		}
		cout << flush;
	}
		
	return 0;
}
