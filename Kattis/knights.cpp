#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ii = pair<ll, ll>;
using vi = vector<ll>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

constexpr ll MOD = 1e9 + 9;

inline bool bit(int mask, int i) { return bool((mask>>i)&1); }

bool compute(int s, int t, int n) {
	int H = (1<<n) - 1;
	if ((s >> n) != (t & H)) return false;
	for (int i = 0; i < n; ++i) {
		if (i + 1 < n && bit(s, i) && bit(t, i+n+1)) return false;
		if (i > 0 && bit(s, i) && bit(t, i+n-1)) return false;
		if (i + 2 < n && bit(s, i+n) && bit(t, i+n+2)) return false;
		if (i > 1 && bit(s, i+n) && bit(t, i+n-2)) return false;
	}
	return true;
}

vvi build_matrix(int n) {
	int SZ = (1 << (n + n));
	vvi M(SZ, vi(SZ, 0LL));
	for (int s = 0; s < SZ; ++s) {
		for (int t = 0; t < SZ; ++t) {
			M[s][t] = compute(s, t, n);
		}
	}
	
	map<int, int> index;
	for (int i = 0; i < SZ; ++i)
		if (M[0][i])
			index.insert({int(index.size()), i});
		else for (int j = 0; j < SZ; ++j)
			if (M[0][j] && M[j][i]) {
				index.insert({int(index.size()), i});
				break;
			}
	
	vvi Mr(index.size(), vi(index.size(), 0LL));
	for (size_t i = 0; i < index.size(); ++i)
		for (size_t j = 0; j < index.size(); ++j)
			Mr[i][j] = M[index[i]][index[j]];
	
	return Mr;
}

vvi multiply(const vvi &lhs, const vvi &rhs) {
	vvi prod(lhs.size(), vi(lhs.back().size(), 0LL));
	for (size_t i = 0; i < lhs.size(); ++i)
		for (size_t k = 0; k < lhs.size(); ++k)
			for (size_t j = 0; j < rhs.size(); ++j)
				prod[i][k] = (prod[i][k] + 
					lhs[i][j] * rhs[j][k]) % MOD;
	return prod;
}

int main() {
	int n, m;
	cin >> n >> m;
	
	vector<vvi> powers_of_two;
	powers_of_two.push_back(build_matrix(n));
	while ((1 << (powers_of_two.size() - 1)) <= m)
		powers_of_two.push_back(
			multiply(
				powers_of_two.back(),
				powers_of_two.back()));
	
	vvi res;
	for (size_t i = 0; (1<<i) <= m; ++i) {
		if (!((m>>i)&1)) continue;
		if (res.empty())
			swap(res, powers_of_two[i]);
		else	res = multiply(res, powers_of_two[i]);
	}
	
	ll ans = 0LL;
	for (size_t i = 0; i < res.size(); ++i)
		ans = (ans + res[0][i]) % MOD;
	cout << ans << endl;
	
	return 0;
}
