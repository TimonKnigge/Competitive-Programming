#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
using ll = long long;
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

constexpr double pi = 3.1415926535897932384626433; // or std::acos(-1)
struct Complex { using T = Complex; double u,v;
	Complex(double u=0, double v=0) : u{u}, v{v} {}
	T operator+(T r) const { return {u+r.u, v+r.v}; }
	T operator-(T r) const { return {u-r.u, v-r.v}; }
	T operator*(T r) const { return {u*r.u - v*r.v, u*r.v + v*r.u}; }
	T operator/(T r) const {
		auto norm = r.u*r.u+r.v*r.v;
		return {(u*r.u + v*r.v)/norm, (v*r.u - u*r.v)/norm};
	}
	T operator*(double r) const { return T{u*r, v*r}; }
	T operator/(double r) const { return T{u/r, v/r}; }
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
//	root_cache(N);
//				, sh=p-1		, --sh
	for (int m = 2; m <= N; m <<= 1) {
		T w, w_m = T::root(inv ? -m : m);
		for (int k = 0; k < N; k += m) {
			w = T{1};
			for (int j = 0; j < m/2; ++j) {
//				T w = (!inv ? roots[j<<sh] : roots[j<<sh].conj());
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
void square_inplace(vector<T> &A) {
	int s = 2*A.size()-1, q = 32 - __builtin_clz(s-1), N=1<<q;
	A.resize(N,{}); fft(A, q, false);
	for(auto &x : A) x = x*x;
	fft(A, q, true); A.resize(s);
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
	for (int i = 0; i < s; ++i) {
		ll l = llround(R1[i].u), m = llround(R2[i].u), h = llround(R1[i].v);
		C[i] = (l + (m%MOD<<15) + (h%MOD<<30)) % MOD;
	}
}

constexpr ll MOD = 1000000000LL;

unordered_map<int, vi> cache;
vi &getpoly(int d, int N) {
	vi &ret = cache[d];
	if (ret.empty()) {
		cerr << d << endl;
		if (d == 0) {
			ret = vi{1};
		} else if (d == 1) {
			ret = vi{0, 1};
		} else if (d == 2) {
			ret = vi{1, MOD-1, 1};
		} else if (d == 3) {
			ret = vi{0, 2, MOD-2, 1};
		} else {
			vi &pl1 = getpoly(d/2, N);
			vi &pl2 = getpoly(d/2-1, N);
			vi &pr1 = getpoly((d+1)/2, N);
			vi &pr2 = getpoly((d+1)/2-1, N);

			vi prod1, prod2;
			convolution_mod(pl1, pr1, MOD, prod1);
			convolution_mod(pl2, pr2, MOD, prod2);
			prod1.resize(N+1);
			prod2.resize(N+1);
			ret.resize(N+1);
			for (int i = 0; i <= N; ++i) {
				ret[i] = prod1[i] + prod2[i];
				if (ret[i] >= MOD) ret[i] -= MOD;
				if (i > 0) ret[i] = MOD + ret[i] - prod2[i-1];
				if (ret[i] >= MOD) ret[i] -= MOD;
			}
		}
	}
	return ret;
}

void solve() {
	int N;
	cin >> N;
	vi jp(N+1, 0), a(N+1, 0);
	jp[0] = 1;
	for (int i = 1;; ++i) {
		// Multiply j by 1-\rho for the probability of
		// skipping i^2
		for (int k = N; k > 0; --k)
			jp[k] = (jp[k] - jp[k-1] + MOD) % MOD;
		bool any = false;
		for (int k = 0; k <= N; ++k)
			a[k] = (a[k] + jp[k]) % MOD,
			any = any || jp[k];
		if (!any) break;

		// Generate the polynomial for jumping from i^2 + 1 to (i+1)^2 - 1
		int d = 2*i-1;
		vi &jp2 = getpoly(d, N), jp3;
		convolution_mod(jp, jp2, MOD, jp3);
		swap(jp, jp3);
		jp.resize(N+1);
	}

	cout << "a[0..N] = " << accumulate(a.begin(), a.end(), 0LL)%MOD << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout << fixed << setprecision(12);
	
	solve();
	
	return 0;
}
