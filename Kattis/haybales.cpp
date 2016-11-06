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

ll inr(vi &v, int l, int r) { return v[r] - (l > 0 ? v[l - 1] : 0); }

ll cost(ll pl, ll cr) {
	if (pl % 2 == 0) return cr * (pl/2);
	if (cr % 2 == 0) return pl * (cr/2);
	return (pl+1)/2 + pl * ((cr-1)/2);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	string S;
	cin >> S;
	
	int N = (int)S.length();
	
	vvi fx(N, vi(N, LLINF));
	for (int i = 0; i < N; ++i) {
		fx[i][i] = 0LL;
		if (i + 1 < N) 
			fx[i][i + 1] = (S[i] == 'C' || S[i+1] == 'P') ? 0 : 1;
		if (i + 2 < N)
			fx[i][i + 2] = is_sorted(S.begin()+i, S.begin()+i+3)
						? 0 : 1;
	}
	
	vi Ps(N, 0LL), Cs(N, 0LL);
	for (int i = 0; i < N; ++i) {
		if (i > 0) Ps[i] += Ps[i - 1];
		if (i > 0) Cs[i] += Cs[i - 1];
		if (S[i] == 'P') ++Ps[i];
		if (S[i] == 'C') ++Cs[i];
	}
	
	for (int l = N - 1; l >= 0; --l)
		for (int r = l + 3; r < N; ++r) {
			fx[l][r] = LLINF;
			for (int m = l + 1; m <= r; ++m) {
				int pl = inr(Ps, l, m-1), cr = inr(Cs, m, r);
				ll tt = fx[l][m-1] + fx[m][r] + cost(pl, cr);
				if (tt < fx[l][r]) fx[l][r] = tt;
			}
		}
	
	cout << fx[0][N - 1] << endl;
	
	return 0;
}
