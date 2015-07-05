#include <iostream>
#include <iomanip>
#include <algorithm>
#include <math.h>

using namespace std;

typedef long long ll;

#define LLINF 9000000000000000000LL

ll solve_single(ll c, ll a, ll b, ll L, ll U) {
	if (c <= 0) return max(0LL, L);
	else return min(U, b / a);
}

ll cdiv(ll a, ll b) {
	return (ll)(ceil(a / (long double)b));
}

pair<ll, ll> KP(ll c1, ll c2, ll a1, ll a2, ll b, ll L, ll U) {
	// Trivial solutions
	if (b < 0) return{ -LLINF, -LLINF };
	if (c1 <= 0) return{ L, solve_single(c2, a2, b - a1 * L, 0, LLINF) };
	if (c2 <= 0) return{ solve_single(c1, a1, b, L, U), 0 };
	if (a1 == 0) return{ U, solve_single(c2, a2, b, 0, LLINF) };
	if (a2 == 0) return{ 0, LLINF };
	if (L == U) return{ L, solve_single(c2, a2, b - a1 * L, 0, LLINF) };
	if (b == 0) return{ 0, 0 };
	// Bound U:
	if (U != LLINF) U = min(U, b / a1);
	if (L != 0 || U != LLINF) {
		pair<ll, ll>
			kp = KP(c1, c2, a1, a2, b - cdiv(b - a1 * U, a2) * a2 - a1 * L, 0, LLINF),
			s1 = { U, (b - a1 * U) / a2 },
			s2 = { L + kp.first, cdiv(b - a1 * U, a2) + kp.second };
		return (c1 * s1.first + c2 * s1.second > c1 * s2.first + c2 * s2.second ? s1 : s2);
	}
	else if (a1 < a2) {
		pair<ll, ll> s = KP(c2, c1, a2, a1, b, 0, LLINF);
		return pair<ll, ll>(s.second, s.first);
	}
	else {
		ll k = a1 / a2, p = a1 - k * a2;
		pair<ll, ll> kp = KP(c1 - c2 * k, c2, p, a2, b - k * (b / a1) * a2, 0, b / a1);
		return{ kp.first, kp.second - k * kp.first + k * (b / a1) };
	}
}

int main() {
	ll C, Hr, Hb, Wr, Wb;
	cin >> C >> Hr >> Hb >> Wr >> Wb;
	pair<ll, ll> s = KP(Hr, Hb, Wr, Wb, C, 0, LLINF);
	cout << (Hr * s.first + Hb * s.second) << endl;
	return 0;
}