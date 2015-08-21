#include <iostream>
#include <iomanip>
#include <vector>	       
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <bitset>
#include <algorithm>
#include <functional>
#include <string>
#include <string.h>  // Include for memset!
#include <complex>
#include <random>
#define _USE_MATH_DEFINES
#include <math.h>

const int INF = 2000000000;	                 // 9
const long long LLINF = 9000000000000000000LL;  // 18
const long double LDINF = 1e300;

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<bool> vb;
typedef long long ll;
typedef long double ld;

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
	long double u, v;
	Complex operator+(Complex r) const { return {u+r.u, v+r.v}; }
	Complex operator-(Complex r) const { return {u-r.u, v-r.v}; }
	Complex operator*(Complex r) const {
		return {u * r.u - v * r.v, u * r.v + v * r.u};
	}
	static Complex exp(complex<ld> c) {
		c = std::exp(c); return {c.real(), c.imag()};
	}
};

const ld MY_PI = 3.14159265358979323846;

void fft(vector<Complex> &A, int N, int p, bool inv = false) {
	for (int i = 0, r = 0; i < N; ++i, r = brinc(r, p))
		if (i < r) swap(A[i], A[r]);
	for (int m = 2; m <= N; m <<= 1) {
		Complex w, w_m = Complex::exp(complex<ld>(0, 2 * MY_PI / m * (inv?-1:1)));
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

void convolution(vector<Complex> &A, vector<Complex> &B, vector<Complex> &C) {
	int p = 1, N = 2;
	while (N < 2 * A.size()) N *= 2, ++p;
	A.reserve(N); B.reserve(N); C.reserve(N);
	for (int i = A.size(); i < N; ++i) A.push_back({0, 0});
	for (int i = B.size(); i < N; ++i) B.push_back({0, 0});
	fft(A, N, p, false);
	fft(B, N, p, false);
	for (int i = 0; i < N; ++i) C.push_back(A[i] * B[i]);
	fft(C, N, p, true);
}

void square_in_place(vector<Complex> &A) {
	int N = 2 * next_power_of_2(A.size());
	A.reserve(N);
	for (int i = A.size(); i < N; ++i) A.push_back({0, 0});
	int p = int(log2(N) + 0.5);
	fft(A, N, p, false);
	for (int i = 0; i < N; ++i) A[i] = A[i] * A[i];
	fft(A, N, p, true);
}

ll pw(ll i, int k, ll n) {
	if (k == 0) return 1;
	if (k == 1) return i % n;
	if (k % 2 == 0) return pw((i*i) % n, k / 2, n);
	else return (i * pw((i*i) % n, k / 2, n)) % n;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, k;
	cin >> n >> k;

	vector<ll> sq(n, 0), dsq(n, 0);
	for (ll i = 1; i < n; ++i) {
		sq[pw(i, k, n) % n]++;
		dsq[(pw(i, k, n) * 2) % n]++;
	}

	vector<Complex> A, B, C;
	for (int i = 0; i < n; ++i) {
//		cerr << i << ": " << sq[i] << ' ' <<dsq[i] <<endl;
		A.push_back({ld(sq[i]), 0});
		B.push_back({ld(sq[i]), 0});
	}

	ll ans = 0;
	convolution(A, B, C);
//	square_in_place(A);
	vector<ll> pairz(n, 0);
	for (int i = 0; i < C.size(); ++i) {
		pairz[i % n] += ll(C[i].u + 0.5);
	}
	for (int i = 0; i < n; ++i) {
		ll sum = pairz[i];
		sum = (sum - dsq[i]) / 2 + dsq[i];
		ans += sum * sq[i];
	}

	cout << ans << endl;
	
	return 0;
}
