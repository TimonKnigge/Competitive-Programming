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

// FFT
ll next_power_of_2(ll x) {	// used in FFT
	x  = (x - 1) | ((x - 1) >> 1);
	x |= x >> 2; x |= x >> 4; x |= x >> 8; x |= x >> 16;
	return x + 1;
}
ll brinc(ll x, ll k) {
	ll i = k - 1, s = 1 << i;
	x ^= s;
	if ((x & s) != s) {
		--i; s >>= 1;
		while (i >= 0 && ((x & s) == s))
			x = x &~ s, --i, s >>= 1;
		if (i >= 0) x |= s;
	}
	return x;
}

constexpr ld pi = 3.1415926535897932384626433;
struct Complex { using T = Complex; ld u,v;
	Complex(ld u=0, ld v=0) : u{u}, v{v} {}
	T operator+(T r) const { return {u+r.u, v+r.v}; }
	T operator-(T r) const { return {u-r.u, v-r.v}; }
	T operator*(T r) const { return {u*r.u - v*r.v, u*r.v + v*r.u}; }
	T operator/(T r) {
		auto norm = r.u*r.u+r.v*r.v;
		return {(u*r.u + v*r.v)/norm, (v*r.u - u*r.v)/norm};
	}
	T inv(){ return T{1,0}/ *this; }
	static T root(ll k){ return {cos(2*pi/k), sin(2*pi/k)}; }
};
using T = Complex;	// using T=F1,F2,F3
void fft(vector<T> &A, int p, bool inv = false) {
	int N = 1<<p;
	for(int i = 0, r = 0; i < N; ++i, r = brinc(r, p))
		if (i < r) swap(A[i], A[r]);
	for (int m = 2; m <= N; m <<= 1) {
		T w, w_m = T::root(inv ? -m : m);
		for (int k = 0; k < N; k += m) {
			w = T{1};
			for (int j = 0; j < m/2; ++j) {
				T t = w * A[k + j + m/2];
				A[k + j + m/2] = A[k + j] - t;
				A[k + j] = A[k + j] + t;
				w = w * w_m;
			}
		}
	}
	if(inv){ T inverse = T(N).inv(); for(auto &x : A) x = x*inverse; }
}
void square_inplace(vector<T> &A) {
	int s = 2*A.size()-1, q = 32 - __builtin_clz(s-1), N=1<<q;
	A.resize(N,{}); fft(A, q, false);
	for(auto &x : A) x = x*x;
	fft(A, q, true); A.resize(s);
}
// -FFT

constexpr ll M = 50000;

int main() {
	int N;
	scanf("%d", &N);
	
	vi C(M+M+1, 0LL);
	vector<Complex> AB(M+M+1, Complex());
	ll zeroes = 0LL;
	while (N--) {
		int v;
		scanf("%d", &v);
		if (v == 0)
			++zeroes;
		else {
			C[v + M]++;
			AB[v + M].u += 1;
		}
	}
	
	square_inplace(AB);
	
	ll ans = 0LL;
	for (ll i = 0; i <= M+M; ++i) {
		if (C[i] == 0LL) continue;
		ll add = 0LL;
		if (i % 2 == 0LL) {
			ll half = (i - M) / 2LL + M;
			if (half >= 0 && half <= M+M)
				add -= C[half];
		}
		ll nw = i + M;
		if (nw < ll(AB.size()))
			add += ll(AB[nw].u + 0.5);
		add *= C[i];
		ans += add;
	}
	
	// Account for the zeroes
	if (zeroes > 0LL) {
		for (ll i = 0; i < M; ++i) {
			ans += 2LL * zeroes * (C[i] * (C[i] - 1LL)
				+ C[M+M-i] * (C[M+M-i] - 1LL)
				+ C[i] * C[M+M-i]);
		}
		ans += zeroes * (zeroes - 1LL) * (zeroes - 2LL);
	}
	
	cout << ans << endl;
	
	return 0;
}
