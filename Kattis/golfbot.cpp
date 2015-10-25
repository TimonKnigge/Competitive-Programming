#include <iostream> 
#include <cstdio>
#include <complex>
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
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;
using ld = long double;
const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

// The two functions below are used in the FFT:
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

int main() {
	
	int N;
	scanf("%d", &N);
	
	vector<Complex> A(200001, {0, 0});
	A[0] = {1, 0};
	for (int i = 0; i < N; ++i) {
		int k;
		scanf("%d", &k);
		A[k] = {1, 0};
	}
	
	square_inplace(A);
	
	int M;
	scanf("%d", &M);
	
	int ans = 0;
	for (int i = 0; i < M; ++i) {
		int d;
		scanf("%d", &d);
		if (A[d].u > 0.5) ans++;
	}
	
	printf("%d\n", ans);
	
	return 0;
}
