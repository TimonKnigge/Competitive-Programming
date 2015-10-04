#include <iostream> 
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
#include <cstdio>

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

int main() {
	
	int N, T;
	scanf("%d %d", &N, &T);
	vi A(N, 0);
	for (int i = 0; i < N; ++i) scanf("%d", &A[i]);
	
	vi count(301, 0);
	for (int i = 0; i < N; ++i) count[A[i]]++;
	vi leftof(N, 0);
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < i; ++j)
			if (A[i] == A[j])
				leftof[i]++;
	
	vvi end(N, vi(N + 1, 0));
	vvi start(N, vi(N + 1, 0));
	
	for (int b = 1; b <= N; ++b) {
		for (int i = 0; i < N; ++i) {
			int mx = 0;
			for (int j = 0; j < i; ++j)
				if (A[i] >= A[j])
					mx = max(mx, end[j][b]);
			for (int j = i; j < N; ++j)
				if (A[i] >= A[j])
					mx = max(mx, end[j][b - 1]);
			end[i][b] = mx + 1;
		}
	}
	
	for (int b = 1; b <= N; ++b) {
		for (int i = N - 1; i >= 0; --i) {
			int mx = 0;
			for (int j = i + 1; j < N; ++j)
				if (A[i] <= A[j])
					mx = max(mx, start[j][b]);
			for (int j = 0; j <= i; ++j)
				if (A[i] <= A[j])
					mx = max(mx, start[j][b - 1]);
			start[i][b] = mx + 1;
//			cerr << i << ' ' << b << ' ' <<start[i][b] << endl;
		}
	}
	
	// Now pick a sequence
	int best = 0;
	for (int i = 0; i < N; ++i)
		best = max(best, end[i][min(N, T)]);
	
	for (int l = 0; l < N; ++l) {
		for (int r = 0; r < N; ++r) {
			if (A[l] > A[r]) continue;
			if (T <= 2 * N) {
				for (int L = max(1, T - N); L <= min(T - 1, N); ++L) {
					// L blocks for the left, T - L for the right
					int v = end[l][L] + start[r][T - L];
					if (v > best) best = v;
				}
			} else {
				int v = end[l][N] + start[r][N];
				int im = T - 2 * N;
				v += im * max(count[A[l]], count[A[r]]);
				if (v > best) best = v;
			}
		}
	}
	
	printf("%d\n", best);
	
	return 0;
}
