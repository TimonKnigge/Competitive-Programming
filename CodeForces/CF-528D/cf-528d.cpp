#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <complex>
#include <string>
#include <string.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <queue>
#include <time.h>

#define MY_PI           3.14159265358979323846

using namespace std;

typedef long double ld;
typedef pair<ld, ld> cmpx;

inline int next_power_of_2(int x) {
	x = (x - 1) | ((x - 1) >> 1);
	x |= x >> 2; x |= x >> 4;
	x |= x >> 8; x |= x >> 16;
	return x + 1;
}

inline int nbit_reverse(int x, int n) {
	for (int i = 0, d = n - 1; i < n / 2; ++i, d -= 2) {
		int l = (x & (1 << i)), r = (x & (1 << (n - 1 - i)));
		x ^= (l << d ^ r) | (r >> d ^ l);
	}
	return x;
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

inline cmpx cmultiply(cmpx l, cmpx r) {
	return make_pair(l.first * r.first - l.second * r.second, l.first * r.second + l.second * r.first);
}
inline cmpx cadd(cmpx l, cmpx r) {
	return make_pair(l.first + r.first, l.second + r.second);
}
inline cmpx csub(cmpx l, cmpx r) {
	return make_pair(l.first - r.first, l.second - r.second);
}
inline cmpx fromcomplex(complex<ld> c) {
	return make_pair(real(c), imag(c));
}

void fft(vector<cmpx>& A, int N, int p, bool inv = false) {
	for (int i = 0, r = 0; i < N; ++i, r = brinc(r, p))
	if (i < r) swap(A[i], A[r]);
	for (int m = 2; m <= N; m <<= 1) {
		cmpx w_m = fromcomplex(exp(complex<ld>(0, 2 * MY_PI / m * (inv ? -1 : 1)))), w;
		for (int k = 0; k < N; k += m) {
			w = cmpx(1, 0);
			for (int j = 0; j < m / 2; ++j) {
				cmpx t = cmultiply(w, A[k + j + m / 2]);
				A[k + j + m / 2] = csub(A[k + j], t);
				A[k + j] = cadd(A[k + j], t);
				w = cmultiply(w, w_m);
			}
		}
	}
	if (inv) for (int i = 0; i < N; ++i) {
		A[i].first /= N;
		A[i].second /= N;
	}
}

void convolution(vector<cmpx>& A, vector<cmpx>& B, vector<cmpx>& C) {
	int N = 2 * max(next_power_of_2(A.size()), next_power_of_2(B.size()));
	A.reserve(N); B.reserve(N); C.reserve(N);
	for (int i = A.size(); i < N; ++i) A.push_back(make_pair(0, 0));
	for (int i = B.size(); i < N; ++i) B.push_back(make_pair(0, 0));
	int p = (int)round(log2(N));
	fft(A, N, p, false);
	fft(B, N, p, false);
	for (int i = 0; i < N; ++i) C.push_back(cmultiply(A[i], B[i]));
	fft(C, N, p, true);
}

const int _A = 0, _C = 1, _T = 2, _G = 3;
inline int mp(char c) {
	if (c == 'A') return _A;
	if (c == 'C') return _C;
	if (c == 'T') return _T;
	return _G;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int S, T, k;
	cin >> S >> T >> k;
	string s, t;
	cin >> s >> t;

	vector< vector<cmpx> >
		s_poly(4, vector<cmpx>(s.size())),
		t_poly(4, vector<cmpx>(t.size())),
		c_poly(4, vector<cmpx>());

	// Compute the bit-vectors of S
	int count[4] = { 0, 0, 0, 0 };
	for (int i = 0; i < k; ++i) {
		count[mp(s[i])]++;
	}

	for (int i = 0; i < s.size(); ++i) {
		if (i + k < s.size())
			count[mp(s[i + k])]++;

		for (int j = 0; j < 4; ++j)
			s_poly[j][i] = make_pair((count[j] > 0 ? 1 : 0), 0);

		if (i - k >= 0) 
			count[mp(s[i - k])]--;
	}

	// Compute the bit-vectors of T
	count[0] = count[1] = count[2] = count[3] = 0;
	for (int i = 0; i < t.size(); ++i) {
		for (int j = 0; j < 4; ++j) {
			t_poly[j][t.size() - 1 - i] = make_pair((mp(t[i]) == j ? 1 : 0), 0);
		}
	}

	// Convolve all polynomials
	for (int i = 0; i < 4; ++i)
		convolution(s_poly[i], t_poly[i], c_poly[i]);

	long long matches = 0;
	for (int i = 0; i < c_poly[0].size(); ++i) {
		int psum = 0;
		for (int j = 0; j < 4; ++j)
			psum += ((int)round(c_poly[j][i].first));
		if (psum == t.length())
			matches++;
	}

	cout << matches << endl;

	return 0;
}