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
#include <array>

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

constexpr ll MOD = 1e9 + 7;

using T = pair<ii, ii>;
T ident = {{1LL, 0LL}, {0LL, 1LL}};
T op(const T& l, const T& r) {
	T o;
	o.first.first =
		((l.first.first * r.first.first)%MOD +
		 (l.first.second * r.second.first)%MOD) % MOD;
	o.first.second =
		((l.first.first * r.first.second)%MOD +
		 (l.first.second * r.second.second)%MOD) % MOD;
	o.second.first =
		((l.second.first * r.first.first)%MOD +
		 (l.second.second * r.second.first)%MOD) % MOD;
	o.second.second =
		((l.second.first * r.first.second)%MOD +
		 (l.second.second * r.second.second)%MOD) % MOD;
	return o;
}

struct SegmentTree {
	int n; vector<T> tree;
	SegmentTree(int _n) : n(_n), tree(2 * n, ident) { }
	void update(int i, T val) {
		for (tree[i+n] = val, i = (i+n)/2; i > 0; i /= 2)
			tree[i] = op(tree[2*i], tree[2*i+1]);
	}
	T query(int l, int r) {
		T lhs = T(ident), rhs = T(ident);
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (  l&1 ) lhs = op(lhs, tree[l++]);
			if (!(r&1)) rhs = op(tree[r--], rhs);
		}
		return op(l == r ? op(lhs, tree[l]) : lhs, rhs);
	}
};

void solve(int t) {
	cerr << t << endl;
	ll N, M;
	cin >> N >> M;
	vi W(M, 0LL), D(M, 0LL), Z(M, 0LL), S(M, 0LL);
	ll Aw, Bw, Ad, Bd, As, Bs;
	cin >> W[0] >> Aw >> Bw;
	cin >> D[0] >> Ad >> Bd;
	cin >> S[0] >> As >> Bs;
	Z[0] = max(1LL, min(N, W[0] + D[0] - 1));
	for (int i = 1; i < M; ++i)
		W[i] = (Aw * W[i - 1] + Bw) % N + 1LL,
		D[i] = (Ad * D[i - 1] + Bd) % 3,
		S[i] = (As * S[i - 1] + Bs) % 1000000000LL + 1LL,
		Z[i] = max(1LL, min(N, W[i] + D[i] - 1LL));
	
	vi straight(N, 1LL), back(N, 0LL), forward(N, 0LL);
	SegmentTree st(N);
	for (int i = 0; i < N; ++i) {
		st.update(i, {{1, 0}, {1, 0}});
	}
	ll ans = 0LL;
	for (int i = 0; i < M; ++i) {
//		cerr << W[i] << ' ' << Z[i] << ' ' << S[i] << endl;
		if (W[i] == Z[i]) {
			straight[W[i]-1] += S[i];
			T mat = st.tree[N+N-W[i]];
			mat.first.first = (mat.first.first + S[i]) % MOD;
			st.update(N-W[i], mat);
		} else if (W[i] != Z[i]) {
			ll p = max(W[i], Z[i]);
			if (W[i] < Z[i]) forward[p-1] = (forward[p-1]+S[i])%MOD;
			if (W[i] > Z[i]) back[p-1] = (back[p-1]+S[i])%MOD;
			T mat = st.tree[N+N-p];
			mat.first.second = (forward[p-1] * back[p-1]) % MOD;
			st.update(N-p, mat);
		}
/*
cerr << "matrices" << endl;
for (int i = 1; i < N+N; ++i) {
cerr << i << endl;
T m = st.tree[i];
cerr << ' ' << m.first.first << ' ' << m.first.second << endl;
cerr << ' ' << m.second.first << ' ' << m.second.second << endl;
}
*/
		T mat = st.query(0, N - 1);
//		cerr << "New value: " << mat.first.first << endl;
		ans = (ans + mat.first.first) % MOD;
	}
	cout << "Case #" <<  t << ": " << ans << '\n';
	cout << flush;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int T;
	cin >> T;
	for (int t = 1; t <= T; ++t) solve(t);
	
	return 0;
}
