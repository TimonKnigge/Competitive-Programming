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

constexpr ll MOD = 1e9+7;

#define ITERATE_MATRIX(w) for (int r = 0; r < (w); ++r) \
			  for (int c = 0; c < (w); ++c)
template <class T, int N>
struct M {
	array<array<T,N>,N> m;
	M() { ITERATE_MATRIX(N) m[r][c] = 0; }
	static M id() {
		M I; for (int i = 0; i < N; ++i) I.m[i][i] = 1; return I;
	}
	M operator*(const M &rhs) const {
		M out;
		ITERATE_MATRIX(N) for (int i = 0; i < N; ++i)
				out.m[r][c] = (out.m[r][c] + m[r][i] * rhs.m[i][c]) % MOD;
		return out;
	}
	M raise(ll n) const {
		if(n == 0) return id();
		if(n == 1) return *this;
		auto r = (*this**this).raise(n / 2);
		return (n%2 ? *this*r : r);
	}
};

void f() {
	ll n;
	string d;
	cin >> n >> d;
	size_t L = d.length();
	
	// Build a state machine for d.
	vi sm[2];
	sm[0].assign(L+1, -1LL);
	sm[1].assign(L+1, -1LL);
	sm[0][L] = sm[1][L] = L;

	for (size_t i = 0; i < L; ++i) {
		for (char c = '0'; c <= '1'; ++c) {
			// We are in state i, have matched all characters
			// <i and now find a c at i.
			if (c == d[i])
				sm[c-'0'][i] = i + 1;
			else {
				sm[c-'0'][i] = 0;
				for (size_t l = 0; l < i; ++l) {
					if (d[l] != c) continue;
					bool y = true;
					for (size_t j = 0; j < l && y; ++j)
						y = y && d[j] == d[i-l+j];
					if (y) sm[c-'0'][i] = l+1;
				}
			}
		}
	}
/*
	cerr << "State machine: " << endl;
	for (size_t i = 0; i <= L; ++i)
		cerr << ' ' << sm[0][i];
	cerr << endl;
	for (size_t i = 0; i <= L; ++i)
		cerr << ' ' << sm[1][i];
	cerr << endl;
*/	
	// Build the matrix
	M<ll, 11> mat;
	for (size_t i = 0; i <= L; ++i)
		mat.m[i][sm[0][i]] += 1,
		mat.m[i][sm[1][i]] += 1;
/*	
	cerr << "Matrix: " << endl;
	for (size_t r = 0; r <= L; ++r) {
		for (size_t c = 0; c <= L; ++c)
			cerr << ' ' << mat.m[r][c];
		cerr << endl;
	}
*/	
	M<ll, 11> matr = mat.raise(n);
/*
	cerr << "Matrix: " << endl;
	for (size_t r = 0; r <= L; ++r) {
		for (size_t c = 0; c <= L; ++c)
			cerr << ' ' << matr.m[r][c];
		cerr << endl;
	}
*/
	ll ans = 0LL;
	for (size_t i = 0; i < L; ++i)
		ans = (ans + matr.m[0][i]) % MOD;
	cout << ans << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int T;
	cin >> T;
	while (T--) f();
	
	return 0;
}
