#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
using ll = __int128;//long long;
using ld = long double;
using ii = pair<ll, ll>;
using vi = vector<ll>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;
using vd = vector<ld>;

template<class T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<class TIn, class TOut = null_type>
using order_tree = tree<TIn, TOut, less<TIn>, rb_tree_tag,
	tree_order_statistics_node_update>;
// .find_by_order(int r) and .order_of_key(TIn v)

constexpr int INF = 2000000010;
constexpr ll LLINF = 9000000000000000010LL;
constexpr ld PI = acos(-1);

constexpr ll MOD = 1e9+7;

constexpr ld pi = PI;// 3.1415926535897932384626433; // or std::acos(-1)
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
int ffts = 0;
void fft(vector<T> &A, int p, bool inv = false) {
	++ffts;
	int N = 1<<p;
	for(int i = 0, r = 0; i < N; ++i, brinc(r, p))
		if (i < r) swap(A[i], A[r]);
//	Uncomment to precompute roots (for T=Complex). Slower but more precise.
	root_cache(N);
//				, sh=p-1		, --sh
	for (int m = 2, sh=p-1; m <= N; m <<= 1, --sh) {
		T w;//, w_m = T::root(inv ? -m : m);
		for (int k = 0; k < N; k += m) {
			w = T{1};
			for (int j = 0; j < m/2; ++j) {
				T w = (!inv ? roots[j<<sh] : roots[j<<sh].conj());
				T t = w * A[k + j + m/2];
				A[k + j + m/2] = A[k + j] - t;
				A[k + j] = A[k + j] + t;
//				w = w * w_m;
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
ll mod(ll a) { return (a%MOD+MOD)%MOD; }
ll mpw(ll a, ll b) {
	if (!b) return 1LL;
	ll r = mpw(a*a%MOD, b/2);
	if (b&1) r = r*a%MOD;
	return r;
}

void convolution_mod(const vi &A, const vi &B, ll MOD, vi &C) {
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
	ll p15 = mpw(2, 15), p30 = mpw(2, 30);
	for (int i = 0; i < s; ++i) {
		ll l = llround(R1[i].u), m = llround(R2[i].u), h = llround(R1[i].v);
		C[i] = (mod(l) + mod(m)*p15%MOD + mod(h)*p30%MOD) % MOD;
	}
}

constexpr int M = 1e5;
void convolution_mod_block(const vi &A, const vi &B, ll MOD, vi &C) {
	vi res(A.size()+B.size()-1);
	for (size_t i = 0; i < A.size(); i += M) {
		vi sA;
		for (size_t k = i; k < i + M && k < A.size(); ++k)
			sA.push_back(A[k]);
		for (size_t j = 0; j < B.size(); j += M) {
			vi sB;
			for (size_t k = j; k < j + M && k < B.size(); ++k)
				sB.push_back(B[k]);
			convolution_mod(sA, sB, MOD, sB);
			for (size_t k = 0; k < sB.size(); ++k)
				res[i+j+k] = (res[i+j+k] + sB[k]) % MOD;
		}
	}
	C.resize(res.size());
	std::copy(res.begin(), res.end(), C.begin());
}

vi vl(ll h, ll w, ll k) {
	if (w == 0) {
		vi r(h+1);
		r[0] = 1LL;
		return r;
	}
	if (w == 1) {
		vi r(h+1);
		r[0] = 1LL;
		for (ll i = 1; i <= h; ++i)
			r[i] = r[i-1]*k % MOD;
		return r;
	}
	vi l = vl(h, w/2, k);
	vi r = l;
	if (w&1) {
		vi p = vl(h, 1, k);
		ll pw = mpw(k, w/2), pr = 1LL;
		for (ll i = 0; i <= h; ++i) {
			p[i] = (p[i] * pr) % MOD;
			pr = (pr * pw) % MOD;
		}
		convolution_mod_block(p, r, MOD, r);
		r.resize(h+1);
	}

	ll pw = mpw(k, (w+1)/2), pr = 1LL;
	for (ll i = 0; i <= h; ++i) {
		l[i] = (l[i] * pr) % MOD;
		pr = (pr * pw) % MOD;
	}

	vi res;
	convolution_mod_block(l, r, MOD, res);
	res.resize(h+1);
	cerr << (long long)w << endl;
	return res;
}

long long C(ll a, ll b, ll k) {
	vi res = vl(a, b, k);
	ll ans = 0LL;
	for (ll v : res) ans = (ans + v) % MOD;
	return (long long)ans;
}

void solve() {
	cout << "C(2, 2, 1) = " << C(2, 2, 1) << endl;
	cout << "C(2, 2, 2) = " << C(2, 2, 2) << endl;
	cout << "C(10, 10, 1) = " << C(10, 10, 1) << endl;
	cout << "C(15, 10, 3) = " << C(15, 10, 3) << endl;
	cout << "C(10000, 10000, 4) = " << C(1e4L, 1e4L, 4) << endl;

	ll tk = 1LL, ans = 0LL;
	for (ll k = 1; k <= 7; ++k) {
		cerr << "Doing step " << (int)k << endl;
		tk *= 10LL;
		ll dt = C(tk+k, tk+k, k);
		cerr << " is " << (long long)dt << endl;
		ans = (ans + dt) % MOD;
	}
	cout << (long long)ans << endl;
	cerr << "Did " << ffts << " ffts" << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout << fixed << setprecision(12);
	
	solve();
	
	return 0;
}
