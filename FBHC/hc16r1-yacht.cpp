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
using ll =unsigned long long;
using ld = long double;
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

ld solve(ll L, ll R, ll inc, ll A, ll B) {
//	cerr << "[" << L << ", " << R << "]" << endl;
	
	ll f = (A + inc - 1) / inc;
	ll e = B / inc;
	ld ret = 0.0;
	if (e > f) {
		ret += ld(e - f) * ld(ld(R - L) * ld(R - L)) / (2.0 * ld(B - A));
	}
	if (e < f) {
		ll Li = max(A, L + e * inc);
		ll Ri = min(B, R + e * inc);
		if (Li < Ri)
			ret += ld(Ri - Li) * ld((Ri + Li - 2 * (L + e * inc))) / (2.0 * ld(B - A));
	} else {
//		cerr << e << ' ' << f << ' '<<ret << endl;
		ll Cl = f * inc;
		ll Cr = e * inc;
		if (Cl > A) {
			ll Li = max(A, Cl - inc + L);
			ll Ri = min(Cl, Cl - inc + R); // should always be 2nd
			if (Li < Ri)
				ret += ld(Ri - Li) * ld((Ri + Li - 2 * (Cl - inc + L))) / (2.0 * ld(B - A));
		}
		if (Cr < B) {
			ll Li = max(Cr, Cr + L); // should always be 2nd
			ll Ri = min(B, Cr + R);
			if (Li < Ri)
				ret += ld(Ri - Li) * ld((Ri + Li - 2 * (Cr + L))) / (2.0 * ld(B - A));
		}
	}
//	cerr << "Final " << ret << endl;
	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int T;
	cin >> T;
	for (int t = 1; t <= T; ++t) {
		int N;
		ll A, B;
		cin >> N >> A >> B;
		
		vector<ll> C(N + 1, 0LL);
		for (int i = 1; i <= N; ++i) { // Directly compute prefix sums
			cin >> C[i];
			C[i] += C[i - 1];
		}
		
		// Note: one whole yacht costs C[N]
		
		// Consider the chance of stranding before operation i
		ld ans = 0.0;
		for (int i = 1; i <= N; ++i) {
			// Intervals of the form
			// [C_0 + kC_N, C_1 + kC_N] (0<=k)
			
			ans += solve(C[i - 1], C[i], C[N], A, B);
		}
		printf("Case #%d: %.8lf\n", t, double(ans));
	}
	
	return 0;
}
