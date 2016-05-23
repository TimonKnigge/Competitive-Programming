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
// convolution leaves A and B in frequency domain state
// C may be equal to A or B for in-place convolution
void convolution(vector<T> &A, vector<T> &B, vector<T> &C){
	int s = A.size() + B.size() - 1;
	int q = 32 - __builtin_clz(s-1), N=1<<q;	// fails if s=1
	A.resize(N,{}); B.resize(N,{}); C.resize(N,{});
	fft(A, q, false); fft(B, q, false);
	for (int i = 0; i < N; ++i) C[i] = A[i] * B[i];
	fft(C, q, true); C.resize(s);
}

constexpr int mxv = 100010;

void printvector(string name, vector<Complex> &v) {
	cout << name << ":";
	for (size_t i = 0; i < v.size(); ++i)
		cout << ' ' << int(v[i].u + 0.5);
	cout << endl;
}

int main() {
	
	int N;
	scanf("%d", &N);
	
	vi A(mxv, 0LL);
	for (int i = 0, v; i < N; ++i)
		scanf("%d", &v),
		A[v]++;
	
	vector<Complex> L(mxv, {0.0, 0.0}), R(mxv, {0.0, 0.0}), res;
	for (int i = 0; i < mxv; ++i)
		L[i] 		= {ld(A[i]), 0.0},
		R[mxv - i - 1]	= {ld(A[i]), 0.0};
	
	convolution(L, R, res);
	
	int ans = 0;
	for (int i = mxv; i < int(res.size()); ++i)
		if (res[i].u > 0.5) ++ans;
	
	if (int(res[mxv - 1].u + 0.5) > N) ++ans; 
	
	printf("%d\n", ans);
	
	return 0;
}
