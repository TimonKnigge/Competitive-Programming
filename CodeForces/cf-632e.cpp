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
	int N = 2 * max(next_power_of_2(A.size()), next_power_of_2(B.size()));
	A.reserve(N); B.reserve(N); C.reserve(N);
	for (int i = A.size(); i < N; ++i) A.push_back({0, 0});
	for (int i = B.size(); i < N; ++i) B.push_back({0, 0});
	int p = int(log2(N) + 0.5);
	fft(A, N, p, false);
	fft(B, N, p, false);
	for (int i = 0; i < N; ++i) C.push_back(A[i] * B[i]);
	fft(C, N, p, true);
}
void convolution(vector<vector<Complex>> &ps, vector<Complex> &C){
	int ts=0; for(auto &p : ps) ts+=p.size(); ts-=ps.size()-1;
	int q = 32-__builtin_clz(ts-1), N=1<<q; C.assign(N,{1,0});
	for(auto &p : ps) p.resize(N,{0,0}), fft(p,N,q,false),
		transform(p.begin(),p.end(),C.begin(),C.begin(),
			multiplies<Complex>());
	fft(C, N, q, true); C.resize(ts);
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
void convolution_inplace(vector<Complex> &A, vector<Complex> &B){
	int N = 2 * max(next_power_of_2(A.size()), next_power_of_2(B.size()));
	A.reserve(N); B.reserve(N);
	for (int i = A.size(); i < N; ++i) A.push_back({0, 0});
	for (int i = B.size(); i < N; ++i) B.push_back({0, 0});
	int p = int(log2(N) + 0.5);
	fft(A, N, p, false);
	fft(B, N, p, false);
	for (int i = 0; i < N; ++i) A[i] = A[i] * B[i];
	fft(A, N, p, true);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N, K;
	cin >> N >> K;
	
	vector<Complex> V(1001, {0.0, 0.0});
	while (N--) {
		int v;
		cin >> v;
		V[v].u = 1.0;
	}
	
	vector<Complex> E(1, {1.0, 0.0});
	for (int i = 10; i >= 0; --i) {
		
		square_inplace(E);
		
		if ((K >> i)&1) {
			vector<Complex> V2(V);
			convolution_inplace(E, V2);
		}
		
		while (E.size() > 1 && (E.back().u < 0.5 || E.size() > 1e6+1))
			E.pop_back();
		for (size_t j = 0; j < E.size(); ++j) {
			E[j].u = (E[j].u < 0.5 ? 0.0 : 1.0);
			E[j].v = 0.0;
		}
	}
	
	bool b = false;
	for (size_t i = 1; i < E.size(); ++i) {
		if (E[i].u < 0.5) continue;
		if (b) cout << ' '; else b = true;
		cout << i;
	}
	cout << endl;
	
	return 0;
}
