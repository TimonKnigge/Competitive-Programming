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

int gcd(int l, int r) {
	int t;
	while (r) {
		t = r;
		r = l % r;
		l = t;
	}
	return l;
}

int main() {
	
	int N;
	scanf("%d", &N);
	vi A(N, 0);
	for (int i = 0; i < N; ++i) scanf("%d", &A[i]);
	
	vi maximum(N, 0);
	ll ans = 0LL;
	for (int g = 1; g < N; ++g) {
		if (N % g != 0) continue;
		
//		cerr << "g: " << g << endl;
		
		for (int r = 0; r < g; ++r) {
			int mn = A[r];
			for (int i = r + g; i < N; i += g)
				mn = max(mn, A[i]);
			maximum[r] = mn;
//			cerr << " min["<<r<<"]: " << maximum[r] << endl;
		}
		
		// Check if all elements are eligible
		bool all_eligible = true;
		for (int i = 0; i < N; ++i)
			all_eligible = all_eligible && (A[i] == maximum[i % g]);
		if (all_eligible) {
			for (int d = g; d < N; d += g) {
				if (gcd(d, N) != g) continue;
				else ans += N;
			}
			continue;
		}
		
		// Modified Kadane's to find candidate subarrays
		int l = 0, r = 0;
		while (l < N) {
			// Find a right starting point for the window
			while (l < N && (A[l] != maximum[l % g] || A[(l - 1 + N) % N] == maximum[(l - 1 + N) % g])) l++;
			if (l >= N) break;
			r = l;
			
//			cerr << "[" << l << ", ";
			
			// Find the left starting point
			while ((r+1) % N != l && A[(r+1) % N] == maximum[(r+1) % g]) r++;
			
//			cerr << r << "]" <<endl;
			
			// Iterate over all lengths
			int invlength = r - l + 1;
			for (int L = g; L <= invlength; L += g) {
				if (gcd(L, N) != g) continue;
				ans += invlength - L + 1;
			}
			
			l = r + 1;
		}
	}
	
	printf("%I64d\n", ans);
	
	return 0;
}
