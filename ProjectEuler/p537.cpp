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
#include <complex>

using namespace std;
using ll = unsigned long long;
using ld = long double;
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

constexpr ll MOD = 1004535809;

/*
inline int next_power_of_2(int x) {
	x = (x - 1) | ((x - 1) >> 1);
	x |= x >> 2; x |= x >> 4;
	x |= x >> 8; x |= x >> 16;
	return x + 1;
}

inline int brinc(int x, int k) {
	int I = k - 1, s = 1 << I;
	x ^= s;
	if ((x & s) != s) {
		I--; s >>= 1;
		while (I >= 0 && ((x & s) == s)) {
			x = x &~ s;
			I--;
			s >>= 1;
		}
		if (I >= 0) x |= s;
	}
	return x;
}

struct Complex {
	long double u,v;
	Complex operator+(Complex r) const { return {u+r.u, v+r.v}; }
	Complex operator-(Complex r) const { return {u-r.u, v-r.v}; }
	Complex operator*(Complex r) const {
		return {u * r.u - v * r.v, u * r.v + v * r.u};
	}
	Complex operator/(Complex r) {
		auto norm = r.u*r.u+r.v*r.v;
		return {(u * r.u + v * r.v) / norm, (v * r.u - u * r.v) / norm};
	}
	static
	Complex exp(complex<ld> c){ c = std::exp(c); return {c.real(), c.imag()}; }
};

#define MY_PI 3.14159265358979323846

// A.size() = N = 2^p
void fft(vector<Complex> &A, int N, int p, bool inv = false) {
	for(int i = 0, r = 0; i < N; ++i, r = brinc(r, p))
		if (i < r) swap(A[i], A[r]);
	for (int m = 2; m <= N; m <<= 1) {
		Complex w, w_m = Complex::exp(complex<ld>(0, 2*MY_PI/m*(inv?-1:1)));
		for (int k = 0; k < N; k += m) {
			w = {1, 0};
			for (int j = 0; j < m / 2; ++j) {
				Complex t = w * A[k + j + m / 2];
				A[k + j + m / 2] = A[k + j] - t;
				A[k + j] = A[k + j] + t;
				w = w * w_m;
			}
		}
	}
	if (inv) for (int i = 0; i < N; ++i) {
		A[i].u /= N; A[i].v /= N;
	}
}

void convolution(vector<Complex> &A,vector<Complex> &B,vector<Complex> &C){
	// Pad with zeroes
	int N = 2 * max(next_power_of_2(A.size()), next_power_of_2(B.size()));
	A.reserve(N); B.reserve(N); C.reserve(N);
	for (int i = A.size(); i < N; ++i) A.push_back({0, 0});
	for (int i = B.size(); i < N; ++i) B.push_back({0, 0});
	int p = int(log2(N) + 0.5);
	// Transform A and B
	fft(A, N, p, false);
	fft(B, N, p, false);
	// Calculate the convolution in C
	for (int i = 0; i < N; ++i) C.push_back(A[i] * B[i]);
	fft(C, N, p, true);
}

void square_inplace(vector<Complex> &A) {
	int N = 2 * next_power_of_2(A.size());
	A.reserve(N);
	for (int i = A.size(); i < N; ++i) A.push_back({0, 0});
	int p = int(log2(N) + 0.5);
	fft(A, N, p, false);
	for (int i = 0; i < N; ++i) A[i] = A[i] * A[i];
	fft(A, N, p, true);
}
*/
constexpr ll SIZE = 3e5+10;
bitset<SIZE + 1> bs;
vector<ll> primes;

void sieve() { // call at start in main!
	bs.set();
	bs[0] = bs[1] = 0;
	for (ll i = 2; i <= SIZE; i++) if (bs[i]) {
		for (ll j = i * i; j <= SIZE; j += i) bs[j] = 0;
		primes.push_back(i);
	}
}

void quadratic_convolution(vector<ll> &A, vector<ll> &B, vector<ll> &C, int cap) {
	C.assign(min(int(A.size() + B.size()) - 1, cap), 0LL);
	for (int i = 0; i < A.size(); ++i)
		for (int j = 0; j < B.size() && i + j < cap; ++j) {
			C[i + j] += A[i] * B[j];
			C[i + j] %= MOD;
		}
}

void bin_pow_cap_at(vector<ll> &a, int k, int cap, vector<ll> &res) {
	if (k == 0) {
		res.assign(cap, 0LL);
		res[0] = 1LL;
	} else if (k == 1) {
		res.assign(cap, 0LL);
		for (int i = 0; i < min(int(a.size()), cap); ++i)
			res[i] = a[i] % MOD;
	} else if (!(k&1)) {
		vector<ll> aa;
		quadratic_convolution(a, a, aa, cap);
		bin_pow_cap_at(aa, k / 2, cap, res);
	} else {
		vector<ll> aa, tmp;
		quadratic_convolution(a, a, aa, cap);
		bin_pow_cap_at(aa, k / 2, cap, tmp);
		quadratic_convolution(a, tmp, res, cap);
	}
}

/*
void bin_pow_cap_at(vector<ll> &a, int k, int cap, vector<ll> &res) {
	if (k == 0) {
		res.assign(cap, 0LL);
		res[0] = 1LL;
	} else if (k == 1) {
		// done!
		res.assign(cap, 0LL);
		for (int i = 0; i < min(int(a.size()), cap); ++i)
			res[i] = a[i] % MOD;
	} else if (!(k&1)) {
		vector<Complex> A(a.size(), {0, 0}), B(a.size(), {0, 0}), C;
		for (int i = 0; i < a.size(); ++i)
			A[i] = B[i] = {a[i] % MOD, 0};
		convolution(A, B, C);
		a.assign(cap, 0LL);
		for (int i = 0; i < min(int(C.size()), cap); ++i) {
			C[i].u -= floor(C[i].u / MOD) * MOD;
//			while (C[i].u > MOD * MOD) C[i].u -= MOD * MOD;
			a[i] = ll(C[i].u + 0.5) % MOD;
		}
		bin_pow_cap_at(a, k / 2, cap, res);
	} else {
		vector<Complex> A(a.size(), {0, 0}), B, C;
		for (int i = 0; i < a.size(); ++i)
			A[i] = {a[i] % MOD, 0};
		bin_pow_cap_at(a, k - 1, cap, res);
		B.assign(res.size(), {0, 0});
		for (int i = 0; i < res.size(); ++i)
			B[i] = {res[i] % MOD, 0};
		convolution(A, B, C);
		res.assign(cap, 0);
		for (int i = 0; i < min(int(C.size()), cap); ++i) {
			C[i].u -= floor(C[i].u / MOD) * MOD;
//			while (C[i].u > MOD * MOD) C[i].u -= MOD * MOD;
			res[i] = ll(C[i].u + 0.5) % MOD;
		}
	}
}*/

int main() {
	
	int n, k;
	scanf("%d %d", &n, &k);
	
	sieve();
	
	// For each i=0..n, calculate all numbers j
	// such that pi(j) = i
	vector<ll> pic(n + 1, 0);
	for (int i = 0; i < int(primes.size()) && i <= n; ++i) {
		pic[i] = primes[i] - (i > 0 ? primes[i - 1] : 1);
	}
	
	vector<ll> res;
	bin_pow_cap_at(pic, k, n + 1, res);
	cout << (res[n] % MOD) << endl;
	
	return 0;
}
