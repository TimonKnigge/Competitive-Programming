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

ll gcd(ll a, ll b) { while (b) { a %= b; swap(a, b); } return a; }
ll lcm(ll a, ll b) { return (a / gcd(a, b)) * b; }
ll mod(ll a, ll b) { return ((a % b) + b) % b; }
// Finds x, y s.t. ax + by = d = gcd(a, b).
void extended_euclid(ll a, ll b, ll &x, ll &y, ll &d) {
	ll xx = y = 0;
	ll yy = x = 1;
	while (b) {
		ll q = a / b;
		ll t = b; b = a % b; a = t;
		t = xx; xx = x - q * xx; x = t;
		t = yy; yy = y - q * yy; y = t;
	}
	d = a;
}
// solves ab = 1 (mod n), -1 on failure
ll mod_inverse(ll a, ll n) {
	ll x, y, d;
	extended_euclid(a, n, x, y, d);
	return (d > 1 ? -1 : mod(x, n));
}
// All modular inverses of [1..n] mod P in O(n) time.
vi inverses(ll n, ll P) {
	vi I(n+1, 1LL);
	for (ll i = 2; i <= n; ++i)
		I[i] = mod(-(P/i) * I[P%i], P);
	return I;
}
// (a*b)%m
ll mulmod(ll a, ll b, ll m){
	ll x = 0, y=a%m;
	while(b>0){
		if(b&1) x = (x+y)%m;
		y = (2*y)%m, b /= 2;
	}
	return x % m;
}
// Finds b^e % m in O(lg n) time, ensure that b < m to avoid overflow!
ll powmod(ll b, ll e, ll m) {
	ll p = e<2 ? 1 : powmod((b*b)%m,e/2,m);
	return e&1 ? p*b%m : p;
}
// Solve ax + by = c, returns false on failure.
bool linear_diophantine(ll a, ll b, ll c, ll &x, ll &y) {
	ll d = gcd(a, b);
	if (c % d) {
		return false;
	} else {
		x = c / d * mod_inverse(a / d, b / d);
		y = (c - a * x) / b;
		return true;
	}
}


constexpr double pi = 3.1415926535897932384626433; // or std::acos(-1)
template<ll p,ll w> // prime, primitive root
struct Field { using T = Field; ll x; Field(ll x=0) : x{x} {}
	T operator+(T r) const { return {(x+r.x)%p}; }
	T operator-(T r) const { return {(x-r.x+p)%p}; }
	T operator*(T r) const { return {(x*r.x)%p}; }
	T operator/(T r) const { return (*this)*r.inv(); }
	T inv() const { return {mod_inverse(x,p)}; }
	static T root(ll k) { assert( (p-1)%k==0 );		// (p-1)%k == 0?
		auto r = powmod(w,(p-1)/abs(k),p);			// k-th root of unity
		return k>=0 ? T{r} : T{r}.inv();
	}
	bool zero() const { return x == 0LL; }
};
constexpr ll MOD = 1e9+7;
using T = Field<MOD, 2LL>;

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
void fft(vector<T> &A, int p, bool inv = false) {
	int N = 1<<p;
	for(int i = 0, r = 0; i < N; ++i, brinc(r, p))
		if (i < r) swap(A[i], A[r]);
//	Uncomment to precompute roots (for T=Complex). Slower but more precise.
	for (int m = 2; m <= N; m <<= 1) { // len = m/2
		for (int k = 0; k < N; k += m) {
			for (int j = 0; j < m/2; ++j) {
//				T w = (!inv ? roots[j<<sh] : roots[j<<sh].conj());
				T t = /*w */ A[k + j + m/2];
				A[k + j + m/2] = A[k + j] - t;
				A[k + j] = A[k + j] + t;
			}
		}
	}
	if(inv){ T inverse = T(N).inv(); for(auto &x : A) x = x*inverse; }
}
void convolution(vector<T> &A, vector<T> &B, vector<T> &C){
	int s = A.size() + B.size() - 1;
	int q = 32 - __builtin_clz(s-1), N=1<<q;	// fails if s=1
	A.resize(N,{}); B.resize(N,{}); C.resize(N,{});
	fft(A, q, false); fft(B, q, false);
	for (int i = 0; i < N; ++i) C[i] = A[i] * B[i];
	fft(C, q, true); C.resize(s);
}
ll mod(ll a) { return (a%MOD+MOD)%MOD; }
void convolution_mod(const vi &A, const vi &B, ll MOD, vi &C) {
	vector<T> cA(A.size()), cB(B.size());
	for (size_t i = 0; i < A.size(); ++i) cA[i] = T{A[i]};
	for (size_t i = 0; i < B.size(); ++i) cB[i] = T{B[i]};
	convolution(cA, cB, cA);
	C.resize(A.size()+B.size()-1);
	for (size_t i = 0; i < C.size(); ++i)
		C[i] = mod(cA[i].x);
	return;
}

vi make_G(ll N) {
	vi smpf(N+1);
	iota(smpf.begin(), smpf.end(), 0LL);
	for (ll n = 2; n <= N; ++n) {
		if (smpf[n] != n) continue;
		for (ll d = n*n; d <= N; d += n)
			if (smpf[d] == d)
				smpf[d] = n;
	}

	vi G(N+1);
	G[1] = 1;
	G[2] = 0;
	int next = 2;
	for (ll n = 3; n <= N; ++n) {
		if (smpf[n] == n)
			G[n] = next++;
		else
			G[n] = G[smpf[n]];
	}
	return G;
}

vi prod(const vi &A, ll m) {
	cerr << m << endl;
	if (m == 0) {
		vi r(1<<20, 0LL);
		r[0] = 1LL;
		return r;
	}
	if (m == 1) return A;
	vi AA;
	convolution_mod(A, A, MOD, AA);
	AA.resize(A.size());
	AA = prod(AA, m/2);
	AA.resize(A.size());
	if (m&1)
		convolution_mod(AA, A, MOD, AA);
	AA.resize(A.size());
	return AA;
}

ll L(ll N, ll M) {
	vi G = make_G(N);

	vi A(1<<20);
	for (ll n = 1; n < N; ++n)
		A[G[n]]++;

	return prod(A, M)[0];
}

void solve() {
	cout << "L(5, 2) = " << L(5, 2) << endl;
	cout << "L(10, 5) = " << L(10, 5) << endl;
	cout << "L(10, 10) = " << L(10, 10) << endl;
	cout << "L(1e3, 1e3) = " << L(1e3, 1e3) << endl;
	cout << "L(1e7, 1e7) = " << L(1e7, 1e7) << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout << fixed << setprecision(12);
	
	solve();
	
	return 0;
}
