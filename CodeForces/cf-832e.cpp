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

constexpr int INF = 2000000000;
constexpr ll LLINF = 9000000000000000000;

int inv[5] = {0, 1, 3, 2, 4};
int mul[5][5], add[5][5], sub[5][5];

void readvec(vector<int> &v) {
	string S;
	cin >> S;
	for (size_t i = 0; i < S.length(); ++i) v[i] = S[i]-'a';
}

void solve(vector<vector<int>> &A, vi &col) {
	size_t ff = 0, i = 0;
	while (i < A[0].size() && ff < A.size()) {
		size_t j = ff;
		while (j < A.size() && A[j][i] == 0) ++j;
		if (j == A.size()) {
			++i;
			continue;
		}
		if (j != ff) swap(A[j], A[ff]);
		int tinv = inv[A[ff][i]];
		for (size_t k = i; k < A[ff].size(); ++k)
			A[ff][k] = mul[tinv][A[ff][k]];
		for (size_t k = 0; k < A.size(); ++k) {
			if (k == ff) continue;
			int tmul = A[k][i];
			for (size_t l = i; l < A[k].size(); ++l) {
				A[k][l] = sub[A[k][l]][mul[tmul][A[ff][l]]];
			}
		}
		col[i] = ll(ff++);
	}
}

constexpr ll MOD = 1e9+7;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 5; ++j) {
			add[i][j] = (i + j) % 5;
			sub[i][j] = (5+i-j) % 5;
			mul[i][j] = (i * j) % 5;
		}
	
	int n, m;
	cin >> n >> m;
	vector<vector<int>> a(n, vector<int>(m, 0));
	for (int i = 0; i < n; ++i) readvec(a[i]);
	sort(a.rbegin(), a.rend());

	vi col(m, -1LL);
	solve(a, col);

	ll mult = 1LL;
	while (a.size() > 0) {
		bool rem = true;
		for (ll v : a.back()) rem = rem && v == 0LL;
		if (!rem) break;
		a.pop_back();
		mult = (mult * 5LL) % MOD;
	}

/*	
	cout << "multiplier = " << mult << endl << "col values:";
	for (int c : col) cout << ' ' << c;
	cout << endl;
	cout << "Matrix:" << endl;
	for (vector<int> &r : a) {
		for (int v : r) cout << ' ' << v;
		cout << endl;
	}
*/
	
	int q;
	cin >> q;
	while (q--) {
		vector<int> x(m, 0), xp(m, 0);
		readvec(x);
		
		for (size_t i = 0; i < x.size(); ++i) {
			if (x[i] == 0) continue;
			if (col[i] < 0LL) continue;
			int tmul = x[i];
			for (size_t j = 0; j < xp.size(); ++j)
				xp[j] = add[xp[j]][mul[tmul][a[col[i]][j]]];
		}
		
		bool y = true;
		for (size_t i = 0; i < x.size(); ++i) y = y && xp[i] == x[i];
		cout << (y ? mult : 0LL) << '\n';
	}
	
	return 0;
}
