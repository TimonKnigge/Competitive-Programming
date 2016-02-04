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

ll dis(vector<ll> &X, vector<ll> &Y, ll x, ll y) {
	ll ret = 0LL;
	for (size_t i = 0; i < X.size(); ++i)
		ret += (abs(X[i] - x) + abs(Y[i] - y));
	return ret;
}

pair<ll, ll> getpoint(ll p, ll m) {
	// p = x + y
	// m = x - y
	return {p+m, p - m};
}

ll sign(ll v) { return v > 0 ? 1 : -1; }

ll solve(vector<ll> &X, vector<ll> &Y, pair<ll, ll> p1, pair<ll, ll> p2) {
	if (p1.first > p2.first) swap(p1, p2);
	ll x1 = p1.first, y1 = p1.second;
	ll x2 = p2.first, y2 = p2.second;
	
	if (x1&1) {
		x1++;
		y1 += sign(y2 - y1);
	}
	if (x2&1) {
		x2--;
		y2 -= sign(y2 - y1);
	}
	
	x1 /= 2; y1 /= 2; x2 /= 2; y2 /= 2;
	ll dx = 1;
	ll dy = sign(y2 - y1);
	ll range = x2 - x1;
	
	ll l = 0, r = range;
	while (r - l > 30) {
		ll lm = (2 * l + r) / 3;
		ll rm = (l + 2 * r) / 3;
		
		ll lmv = dis(X, Y, x1 + dx * lm, y1 + dy * lm);
		ll rmv = dis(X, Y, x1 + dx * rm, y1 + dy * rm);
		if (lmv < rmv)
			r = rm;
		else	l = lm;
	}
	
	ll best = LLINF;
	for (ll v = l; v <= r; ++v)
		best = min(best, dis(X, Y, x1 + v * dx, y1 + v * dy));
	
	return best;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N;
	cin >> N;
	vector<ll> X(N, 0LL), Y(N, 0LL);
	for (int i = 0; i < N; ++i)
		cin >> X[i] >> Y[i];
	
	ll D;
	cin >> D;
	
	ll maxp = LLINF, minp = -LLINF, maxm = LLINF, minm = -LLINF;
	for (int i = 0; i < N; ++i) {
		maxp = min(maxp, X[i] + Y[i] + D);
		minp = max(minp, X[i] + Y[i] - D);
		maxm = min(maxm, X[i] - Y[i] + D);
		minm = max(minm, X[i] - Y[i] - D);
	}
	
	vector<ll> Xs(X), Ys(Y);
	sort(Xs.begin(), Xs.end());
	sort(Ys.begin(), Ys.end());
	ll Xmed = Xs[Xs.size() / 2];
	ll Ymed = Ys[Ys.size() / 2];
	
	if (maxp < minp || maxm < minm)
		cout << "impossible" << endl;
	else if (minp <= Xmed + Ymed && Xmed + Ymed <= maxp
	 && minm <= Xmed - Ymed && Xmed - Ymed <= maxm)
		cout << dis(X, Y, Xmed, Ymed) << endl;
	else {
		pair<ll, ll>
			p1 = getpoint(maxp, maxm),
			p2 = getpoint(minp, maxm),
			p3 = getpoint(maxp, minm),
			p4 = getpoint(minp, minm);
		
		ll a1 = solve(X, Y, p1, p2);
		ll a2 = solve(X, Y, p3, p4);
		ll a3 = solve(X, Y, p1, p3);
		ll a4 = solve(X, Y, p2, p4);
		
		cout << min(a1, min(a2, min(a3, a4))) << endl;
	}
	
	return 0;
}
