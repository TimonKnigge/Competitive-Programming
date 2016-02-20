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

ll MAGIC_CONSTANT = 200;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N;
	ll M;
	cin >> N >> M;
	
	vi X(N, 0LL), Y(N, 0LL), SM(N, 0LL), PM(N, 0LL), SV(N, 0LL), PV(N, 0LL);
	ll MY = 0LL;
	for (int i = 0; i < N; ++i) {
		cin >> X[i] >> Y[i] >> SM[i] >> PM[i] >> SV[i] >> PV[i];
		MY = max(MY, Y[i]);
	}
	
	ll L = 0LL, R = M + MY + 3LL;
	
	while (L < R) {
		ll C = (L + R) / 2LL;
		ll cost = 0LL;
		
		for (int i = 0; i < N; ++i) {
			ll needed = max(0LL, C * X[i] - Y[i]);
			ll l = 0LL, r = (needed + SV[i] - 1LL) / SV[i];
			while (r - l > MAGIC_CONSTANT) {
				ll lm = (2LL * l + r) / 3LL;
				ll rm = (l + 2LL * r) / 3LL;
				ll lcost = PV[i] * lm + PM[i] * (max(0LL, needed - lm * SV[i] + SM[i] - 1) / SM[i]);
				ll rcost = PV[i] * rm + PM[i] * (max(0LL, needed - rm * SV[i] + SM[i] - 1) / SM[i]);
				if (lcost < rcost)	r = rm;
				else			l = lm;
			}
			ll mcost = LLINF;
			for (; l <= r; ++l) {
				mcost = min(mcost, PV[i] * l + PM[i] * (max(0LL, needed - l * SV[i] + SM[i] - 1) / SM[i]));
			}
			cost += mcost;
		}
		if (cost <= M)	L = C + 1;
		else		R = C;
	}
	
	cout << max(0LL, L - 1) << endl;
	
	return 0;
}
