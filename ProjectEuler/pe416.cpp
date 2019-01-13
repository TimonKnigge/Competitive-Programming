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

constexpr ll MOD = 1e9;

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
		ITERATE_MATRIX(N) {
			for (int i = 0; i < N; ++i)
				out.m[r][c] += m[r][i] * rhs.m[i][c] % MOD;
			out.m[r][c] %= MOD;
		}
		return out;
	}
	M raise(ll n) const {
		if(n == 0) return id();
		if(n == 1) return *this;
		auto r = (*this**this).raise(n / 2);
		return (n%2 ? *this*r : r);
	}
};

ll h(ll a, ll b, ll c, ll m) {
	return a + (m+1)*b + (m+1)*(m+1)*c;
}

ll F(ll m, ll n) {
	vvi nCk(2*m+1, vi(2*m+1));
	for (ll i = 0; i <= 2*m; ++i)
		nCk[0][i] = 0, nCk[i][0] = 1;
	for (ll n = 1; n <= 2*m; ++n)
		for (ll k = 1; k <= 2*m; ++k)
			nCk[n][k] = (nCk[n-1][k-1] + nCk[n-1][k]) % MOD;

	unordered_map<ll, size_t> id;
	vi bya, byb, byc;
	size_t cnt = 0;
	for (ll a = 0LL; a <= 2*m; ++a)
		for (ll b = 0LL; a+b <= 2*m; ++b)
			id[h(a, b, 2*m-a-b, 2*m)] = cnt++,
			bya.push_back(a),
			byb.push_back(b),
			byc.push_back(2*m-a-b);

	assert(cnt <= 231);
	assert(cnt == bya.size());
	M<ll, 2*231> mat;
	for (size_t i = 0; i < cnt; ++i) {
		ll a = bya[i], b = byb[i], c = byc[i];
		for (ll ta = 0; ta <= a; ++ta)
			for (ll tb = 0; ta+tb <= a; ++tb) {
				ll tc = a-ta-tb;
				ll hsh = h(b+ta, c+tb, tc, 2*m);
				assert(id.find(hsh) != id.end());
				size_t j = id[hsh];

				ll ways = nCk[a][ta] * nCk[a-ta][tb] % MOD;

				if (a == 0) {
					mat.m[2*i][2*j+1] = (mat.m[2*i][2*j+1] + ways) % MOD;
				} else {
					mat.m[2*i][2*j] = (mat.m[2*i][2*j] + ways) % MOD;
					mat.m[2*i+1][2*j+1] = (mat.m[2*i+1][2*j+1] + ways) % MOD;
				}
			}
	}


	size_t k = id[h(2*m, 0, 0, 2*m)];
	mat = mat.raise(n-1);
	cerr << mat.m[2*k][2*k] << " + " << mat.m[2*k][2*k+1] << " = ";
	return (mat.m[2*k][2*k] + mat.m[2*k][2*k+1]) % MOD;
}

void solve() {
	cout << "F(1, 1) = " << F(1, 1) << endl;
	cout << "F(1, 2) = " << F(1, 2) << endl;
	cout << "F(1, 3) = " << F(1, 3) << endl;
	cout << "F(1, 4) = " << F(1, 4) << endl;
	cout << "F(1, 5) = " << F(1, 5) << endl;
	cout << "F(2, 3) = " << F(2, 3) << endl;
	cout << "F(2, 100) = " << F(2, 100) << endl;
	cout << "F(10, 1e12) = " << F(10, 1000000LL * 1000000LL) << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout << fixed << setprecision(12);
	
	solve();
	
	return 0;
}
