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

ll maxb(ll N, ll B, ll C) {
	return 3LL + N / B + max(0LL, (N - B) / (B - C));
}

ll profit(ll N, ll A, ll B, ll C, ll Bs) {
	ll ret = 0LL;
	if (N - B >= B - C) {
		ll d = (N - B) / (B - C);
		d = min(Bs, d);
		Bs -= d;
		ret += d;
		N -= d * (B - C);
	}
	while (Bs > 0) {
		ll tk = N / B;
		if (tk == 0) return -1;
		if (tk > Bs) tk = Bs;
		Bs -= tk;
		ret += tk;
		N -= B * tk;
		N += C * tk;
	}
	ret += N / A;
	return ret;
}

ll MAGIC_CONSTANT = 1000;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	ll N, A, B, C;
	cin >> N >> A >> B >> C;
	
	ll L = 0LL, R = maxb(N, B, C);
	while (R - L > MAGIC_CONSTANT) {
		ll LM = (2LL * L + R) / 3LL;
		ll RM = (L + 2LL * R) / 3LL;
		
		if (profit(N, A, B, C, LM) > profit(N, A, B, C, RM))
			R = RM;
		else	L = LM;
	}
	
	ll opt = 0LL;
	while (L <= R) {
		opt = max(opt, profit(N, A, B, C, L));
		++L;
	}
	cout << opt << endl;
	
	return 0;
}
