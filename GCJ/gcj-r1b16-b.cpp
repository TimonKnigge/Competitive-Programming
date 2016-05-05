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

vi p10;

void tryopt(ll ac, ll aj, ll &dopt, ll &copt, ll &jopt) {
//	cerr << ac << ' ' << aj << ' '<<dopt << endl;
	if (dopt == -1 || dopt > abs(ac-aj)
		|| (dopt == abs(ac-aj) && (copt > ac || (copt == ac
			&& jopt > aj)))) {
		dopt = abs(ac-aj);
		copt = ac;
		jopt = aj;
	}
}

void solve(int t) {
	string C, J;
	cin >> C >> J;
	int N = C.length();
	
	vii MCmJ(N + 2, {0LL, 0LL});
	vii mCMJ(N + 2, {0LL, 0LL});
	for (ll v = 1LL, i = N - 1; i >= 0; --i, v *= 10LL) {
		MCmJ[i] = MCmJ[i + 1];
		mCMJ[i] = mCMJ[i + 1];
		if (C[i] == '?') {
			MCmJ[i].first += v * 9LL;
		} else {
			MCmJ[i].first += v * (C[i] - '0');
			mCMJ[i].first += v * (C[i] - '0');
		}
		if (J[i] == '?') {
			mCMJ[i].second += v * 9LL;
		} else {
			MCmJ[i].second += v * (J[i] - '0');
			mCMJ[i].second += v * (J[i] - '0');
		}
	}
	
	ll M = p10[N - 1];
	ll dopt = -1LL, copt = -1, jopt = -1LL;
	ll Cn = 0LL, Jn = 0LL;
	
	C = C + '0';
	J = J + '0';
	for (int i = 0; i <= N; ++i) {
		if (C[i] == '?' && J[i] == '?') {
			tryopt(
				Cn + M + mCMJ[i+1].first,
				Jn +     mCMJ[i+1].second,
				dopt, copt, jopt);
			tryopt(
				Cn +     MCmJ[i+1].first,
				Jn + M + MCmJ[i+1].second,
				dopt, copt, jopt);
		} else if (C[i] == '?') {
			ll jv = J[i] - '0';
			if (jv > 0)
				tryopt(
					Cn + M*(jv-1) + MCmJ[i+1].first,
					Jn + M * jv   + MCmJ[i+1].second,
					dopt, copt, jopt);
			if (jv < 9)
				tryopt(
					Cn + M*(jv+1) + mCMJ[i+1].first,
					Jn + M * jv   + mCMJ[i+1].second,
					dopt, copt, jopt);
			Cn += M * jv;
			Jn += M * jv;
		} else if (J[i] == '?') {
			ll cv = C[i] - '0';
			if (cv > 0)
				tryopt(
					Cn + M * cv   + mCMJ[i+1].first,
					Jn + M*(cv-1) + mCMJ[i+1].second,
					dopt, copt, jopt);
			if (cv < 9)
				tryopt(
					Cn + M * cv   + MCmJ[i+1].first,
					Jn + M*(cv+1) + MCmJ[i+1].second,
					dopt, copt, jopt);
			Cn += M * cv;
			Jn += M * cv;
		} else {
			ll jv = J[i] - '0';
			ll cv = C[i] - '0';
			tryopt(	Cn + M * cv + MCmJ[i+1].first,
				Jn + M * jv + MCmJ[i+1].second,
				dopt, copt, jopt);
			tryopt(	Cn + M * cv + mCMJ[i+1].first,
				Jn + M * jv + mCMJ[i+1].second,
				dopt, copt, jopt);
			Cn += M * cv;
			Jn += M * jv;
		}
		
		M /= 10LL;
	}
	
	M = p10[N - 1];
	C.pop_back();
	J.pop_back();
	for (int i = 0; i < N; ++i) {
		if (C[i] == '?')
			C[i] = char(copt / M + '0');
		if (J[i] == '?')
			J[i] = char(jopt / M + '0');
		jopt %= M;
		copt %= M;
		M /= 10LL;
	}
	
	cout << "Case #" <<  t << ": " << C << ' ' << J << '\n';
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	p10.assign(19, 1LL);
	for (int i = 1; i < 19; ++i)
		p10[i] = 10LL * p10[i - 1];
	
	int T;
	cin >> T;
	for (int t = 1; t <= T; ++t) solve(t);
	
	return 0;
}
