#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using vi = vector<ll>;
constexpr int INF = 2000000010;
constexpr ll LLINF = 9000000000000000010LL;

constexpr ld pi = 3.1415926535897932384626433;
struct Complex { using T = Complex; ld u,v;
	Complex(ld u=0, ld v=0) : u{u}, v{v} {}
	T operator+(T r) const { return {u+r.u, v+r.v}; }
	T operator-(T r) const { return {u-r.u, v-r.v}; }
	T operator*(T r) const { return {u*r.u - v*r.v, u*r.v + v*r.u}; }
	T operator/(T r) const {
		auto norm = r.u*r.u+r.v*r.v;
		return {(u*r.u + v*r.v)/norm, (v*r.u - u*r.v)/norm};
	}
	T operator*(ld r) const { return T{u*r, v*r}; }
	T operator/(ld r) const { return T{u/r, v/r}; }
	T inv() const { return T{1,0}/ *this; }
	T conj() const { return T{u, -v}; }
	static T root(ll k){ return {cos(2*pi/k), sin(2*pi/k)}; }
	bool zero() const { return max(abs(u), abs(v)) < 1e-6; }
};

void brinc(int &x, int k) {
	int i = k - 1, s = 1 << i;
	x ^= s;
	if ((x & s) != s) {
		--i; s >>= 1;
		while (i >= 0 && ((x & s) == s))
			x = x &~ s, --i, s >>= 1;
		if (i >= 0) x |= s;
	}
}
using T = Complex;	// using T=F1,F2,F3
vector<T> roots;
void root_cache(int N) {
	if (N == (int)roots.size()) return;
	roots.assign(N, T{0});
	for (int i = 0; i < N; ++i)
		roots[i] = ((i&-i) == i)
			? T{cos(2.0*pi*i/N), sin(2.0*pi*i/N)}
			: roots[i&-i] * roots[i-(i&-i)];
}
void fft(vector<T> &A, int p, bool inv = false) {
	int N = 1<<p;
	for(int i = 0, r = 0; i < N; ++i, brinc(r, p))
		if (i < r) swap(A[i], A[r]);
//	Uncomment to precompute roots (for T=Complex). Slower but more precise.
	root_cache(N);
	for (int m = 2, sh = p-1; m <= N; m <<= 1, --sh) {
		for (int k = 0; k < N; k += m) {
			for (int j = 0; j < m/2; ++j) {
				T w = (!inv ? roots[j<<sh] : roots[j<<sh].conj());
				T t = w * A[k + j + m/2];
				A[k + j + m/2] = A[k + j] - t;
				A[k + j] = A[k + j] + t;
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
void square_inplace(vector<T> &A) {
	int s = 2*A.size()-1, q = 32 - __builtin_clz(s-1), N=1<<q;
	A.resize(N,{}); fft(A, q, false);
	for(auto &x : A) x = x*x;
	fft(A, q, true); A.resize(s);
}
// Convolution modulo a prime. Note that we break the input up in
// blocks of 15 bits, so it should not be much larger than 1<<30.
void pconvolution(const vi &A, const vi &B, vi &C) {
	int s = A.size() + B.size() - 1; ll m15 = (1LL<<15)-1LL;
	int q = 32 - __builtin_clz(s-1), N=1<<q;	// fails if s=1
	vector<T> Ac(N), Bc(N), R1(N), R2(N);
	for (size_t i = 0; i < A.size(); ++i) Ac[i] = T{A[i]&m15, A[i]>>15};
	for (size_t i = 0; i < B.size(); ++i) Bc[i] = T{B[i]&m15, B[i]>>15};
	fft(Ac, q, false); fft(Bc, q, false);
	for (int i = 0, j = 0; i < N; ++i, j = (N-1)&(N-i)) {
		T as = (Ac[i] + Ac[j].conj()) / 2;
		T al = (Ac[i] - Ac[j].conj()) / T{0, 2};
		T bs = (Bc[i] + Bc[j].conj()) / 2;
		T bl = (Bc[i] - Bc[j].conj()) / T{0, 2};
		R1[i] = as*bs + al*bl*T{0,1}, R2[i] = as*bl + al*bs;
	}
	fft(R1, q, true); fft(R2, q, true);
	C.resize(s);
	for (int i = 0; i < s; ++i) {
		ll l = llround(R1[i].u), m = llround(R2[i].u), h = llround(R1[i].v);
		C[i] = (l + (m<<15) + (h<<30));
	}
}

ll c(char c) { return ll(c-'0'); }

ll parse(const string &s, size_t i) {
	return c(s[i]) + 10*c(s[i+1]) + 100*c(s[i+2])
		+ 1000*c(s[i+3]) + 10000*c(s[i+4])
		+ 100000*c(s[i+5]);
}

void solve() {
	string a, b;
	cin >> a >> b;
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	if (a.length() % 6 != 0) a = a + string(6-a.length()%6, '0');
	if (b.length() % 6 != 0) b = b + string(6-b.length()%6, '0');

	vi l(a.length()/6), r(b.length()/6);
	for (size_t i = 0; i < a.length(); i += 6)
		l[i/6] = parse(a, i);//, cout << l[i/6] << endl;
	for (size_t j = 0; j < b.length(); j += 6)
		r[j/6] = parse(b, j);//, cout << r[j/6] << endl;

	vi p;
	pconvolution(l, r, p);
	p.resize(p.size()+5);
	p.push_back(0), p.push_back(0);
	for (size_t k = 0; k < p.size(); ++k) {
//		cout << ' ' << p[k] << endl;
		if (p[k] >= 1000000LL) {
			ll add = p[k] / 1000000LL;
			p[k] -= add * 1000000LL;
			p[k+1] += add;
		}
//		cout << '>' << p[k] << endl;
	}
	while (p.size() > 1 && p.back() == 0) p.pop_back();
	reverse(p.begin(), p.end());
	for (size_t i = 0; i < p.size(); ++i) {
		if (i == 0)
			cout << p[i];
		else
			cout << setfill('0') << setw(6) << p[i];
	}
	cout << setfill(' ') << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout << fixed << setprecision(12);
	
	int n;
	cin >> n >> ws;
	while (n--) solve();
	
	return 0;
}
