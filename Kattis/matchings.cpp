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

template<class T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<class TIn, class TOut = null_type>
using order_tree = tree<TIn, TOut, less<TIn>, rb_tree_tag,
	tree_order_statistics_node_update>;

constexpr int INF = 2000000010;
constexpr ll LLINF = 9000000000000000010LL;

constexpr ld pi = 3.1415926535897932384626433;
struct Complex { using T = Complex; ld u = 0.0, v = 0.0;
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

ll next_power_of_2(ll x) {
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

// Leaves in swapped state.
void fft2d(vector<vector<Complex>> &A, int p, bool inv = false) {
	for (auto &row : A) fft(row, p, inv);
	for (int r = 0; r < (1 << p); ++r)
		for (int c = r + 1; c < (1 << p); ++c)
			swap(A[r][c], A[c][r]);
	for (auto &row : A) fft(row, p, inv);
}

void resize(vector<vector<Complex>> &A, int N) {
	for (auto &row : A) row.resize(N, {});
	A.resize(N, vector<Complex>(N));
}

vector<vector<Complex>> convolution2d(vector<vector<Complex>> &A,
		vector<vector<Complex>> &B) {
	int s = max(A.size()+B.size(), A[0].size()+B[0].size()) - 1;
	int q = 32 - __builtin_clz(s - 1);
	int N = (1 << q);
	vector<vector<Complex>> C(N, vector<Complex>(N));
	resize(A, N); resize(B, N);
	fft2d(A, q, false); fft2d(B, q, false);
	for (int r = 0; r < N; ++r)
		for (int c = 0; c < N; ++c)
			C[r][c] = A[r][c] * B[r][c];
	fft2d(C, q, true);
	resize(C, s);
	return C;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int ci, ri;
	cin >> ci >> ri;
	vector<vector<vector<Complex>>> I(2, vector<vector<Complex>>(ri));
	for (int r = 0; r < ri; ++r) {
		I[0][r].resize(ci);
		I[1][r].resize(ci);
		for (int c = 0, v; c < ci; ++c) cin >> v, I[v][r][c] = {1.0, 0.0};
		reverse(I[0][r].begin(), I[0][r].end());
		reverse(I[1][r].begin(), I[1][r].end());
	}
	reverse(I[0].begin(), I[0].end());
	reverse(I[1].begin(), I[1].end());

	int cp, rp;
	cin >> cp >> rp;
	vector<vector<vector<Complex>>> P(2, vector<vector<Complex>>(rp));
	for (int r = 0; r < rp; ++r) {
		P[0][r].resize(cp);
		P[1][r].resize(cp);
		for (int c = 0, v; c < cp; ++c) cin >> v, P[v][r][c] = {1.0, 0.0};
	}

	vector<vector<vector<Complex>>> IP(2);
	IP[0] = convolution2d(I[0], P[0]);
	IP[1] = convolution2d(I[1], P[1]);

	vii bestv;
	int bestc = 0;
	for (int r = 0; r + ri <= rp; ++r) {
		for (int c = 0; c + ci <= cp; ++c) {
			int v = int(IP[0][r+ri-1][c+ci-1].u+0.5)
				+ int(IP[1][r+ri-1][c+ci-1].u+0.5);
			if (v == bestc)
				bestv.push_back({c, r});
			else if (v > bestc)
				bestc = v,
				bestv.assign(1, {c, r});
		}
	}

	sort(bestv.begin(), bestv.end());
	for (const ii &pr : bestv) cout << pr.first << ' ' << pr.second << endl;

	return 0;
}
