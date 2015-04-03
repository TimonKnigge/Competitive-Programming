#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <complex>
#include <algorithm>
#include <vector>

using namespace std;

typedef long double ld;
typedef complex<ld> cmpx;

inline int next_power_of_2(int x) {
	x--; x |= x >> 1;
	x |= x >> 2; x |= x >> 4;
	x |= x >> 8; x |= x >> 16;
	x++; return x;
}

inline int nbit_reverse(int x, int n) {
	for (int i = 0, d = n - 1; i < n / 2; ++i, d -= 2) {
		int l = (x & (1 << i)), r = (x & (1 << (n - 1 - i)));
		x ^= (l << d ^ r) | (r >> d ^ l);
	}
	return x;
}

// A.size() = N = 2^p
void fft(vector<cmpx>& A, int N, int p, bool inv = false) {
	for (int i = 0, r = 0; i < N; ++i, r = nbit_reverse(i, p))
		if (i < r) swap(A[i], A[r]);
	for (int m = 2; m <= N; m <<= 1) {
		cmpx w_m = exp(cmpx(0, 2 * M_PI / m * (inv ? -1 : 1))), w;
		for (int k = 0; k < N; k += m) {
			w = cmpx(1, 0);
			for (int j = 0; j < m / 2; ++j) {
				cmpx t = w * A[k + j + m / 2];
				A[k + j + m / 2] = A[k + j] - t;
				A[k + j] += t;
				w = w * w_m;
			}
		}
	}
	if (inv) for (int i = 0; i < N; ++i) A[i] /= cmpx(N, 0);
}

void convolution(vector<cmpx>& A, vector<cmpx>& B, vector<cmpx>& C) {
	/// Pad with zeroes
	int N = 2 * max(next_power_of_2(A.size()), next_power_of_2(B.size()));
	A.reserve(N); B.reserve(N); C.reserve(N);
	for (int i = A.size(); i < N; ++i) A.push_back(0);
	for (int i = B.size(); i < N; ++i) B.push_back(0);
	int p = (int)round(log2(N));
	// Transform A and B
	fft(A, N, p, false);
	fft(B, N, p, false);
	// Calculate the convolution in C
	for (int i = 0; i < N; ++i) C.push_back(A[i] * B[i]);
	fft(C, N, p, true);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int T; 
	cin >> T;
	for (int t = 1; t <= T; ++t) {
		int n1, n2;
		cin >> n1; n1++;
		vector<cmpx> A(n1), C;
		for (int i = 0; i < n1; ++i) {
			int d;
			cin >> d;
			A[i] = cmpx(d, 0);
		}
		cin >> n2; n2++;
		vector<cmpx> B(n2);
		for (int i = 0; i < n2; ++i) {
			int d;
			cin >> d;
			B[i] = cmpx(d, 0);
		}

		convolution(A, B, C);
		vector<int> Ci(C.size());
		for (int i = 0; i < C.size(); ++i) Ci[i] = (int)round(real(C[i]));
		int e = C.size() - 1;
		while (e > 0 && Ci[e] == 0) e--;
		cout << e << endl;
		for (int i = 0; i <= e; ++i) cout << Ci[i] << " \n"[i == e];
	}

	return 0;
}