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

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N;
	scanf("%d", &N);
	vector<ll> B(N, 0LL);
	for (int i = 0; i < N; ++i)
		scanf("%lld", &B[i]);
	
	vector<ll> A(N, 0);
	if (N % 3 != 0) {
		vector<ll> from(N, 0);
		for (int i = 1; i < N; ++i) {
			from[(3 * i) % N] = from[(3 * (i-1)) % N]
				+ (B[(3 * i - 1 + N) % N]
				-  B[(3 * i - 2 + N) % N]);
		}
		ll diffsum = 0, fullsum = 0;
		for (int i = 0; i < N; ++i) {
			diffsum += from[i];
			fullsum += B[i];
		}
		fullsum /= 3;
		
		// fullsum = N * V + diffsum
		ll V = (fullsum - diffsum) / N;
		for (int i = 0; i < N; ++i) {
			A[i] = V + from[i];
		}
	} else {
		vector<ll> from(N, 0);
		ll rmin[3];
		for (int a = 0; a < 3; ++a) {
			rmin[a] = 0;
			for (int i = 1; i < N / 3; ++i) {
				from[3*i + a] = from[3*(i-1) + a]
					+ B[3 * i + a - 1]
					- B[3 * i + a - 2];
				rmin[a] = min(rmin[a], from[3 * i + a]);
			}
		}
		A[0] = 1 - rmin[0];
		A[1] = 1 - rmin[1];
		for (int i = 2; i < N; ++i)
			A[i] = B[i - 1] - A[i - 2] - A[i - 1];
	}

	for (int i = 0; i < N; ++i) cout << A[i] << '\n';
	cout << flush;
	
	return 0;
}
