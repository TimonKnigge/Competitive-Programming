#include <bits/stdc++.h>

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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N, T;
	cin >> N >> T;
	vi D(N, 0LL), S(N, 0LL);
	for (int i = 0; i < N; ++i) cin >> D[i] >> S[i];
	
	ld lb = -1e12;
	for (int i = 0; i < N; ++i) lb = max(lb, ld(-S[i]) + 1e-8);
	ld ub = 1e12;
	while (ub-lb>1e-9) {
		ld m = (lb+ub)/2.0, tt = 0.0;
		for (int i = 0; i < N; ++i) {
			tt += ld(D[i])/ld(S[i]+m);
		}
		if (tt < T)
			ub = m;
		else	lb = m;
	}
	printf("%.10lf\n", double((ub+lb)/2.0));
	
	return 0;
}
