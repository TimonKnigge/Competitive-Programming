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

struct FenwickTree {		// use 1 based indices!!!
	int n; vector<int> tree;
	FenwickTree(int n) : n(n) { tree.assign(n + 1, 0); }
	int query(int l, int r) { return query(r) - query(l - 1); }
	int query(int r) {
		int s = 0;
		for(; r > 0; r -= (r & (-r))) s += tree[r];
		return s;
	}
	void update(int i, int v) {
		for(; i <= n; i += (i & (-i))) tree[i] += v;
	}
};

int cm(char c) {
	if (c == 'A') return 0;
	if (c == 'G') return 1;
	if (c == 'T') return 2;
	return 3;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N;
	vi id;
	{
		string S;
		cin >> S;
		id.resize(S.length());
		for (size_t i = 0; i < S.length(); ++i) id[i] = cm(S[i]);
		N = (int)S.length();
	}

	vector<vector<vector<FenwickTree>>> ft(4, vector<vector<FenwickTree>>(10));
	for (int p = 1; p <= 10; ++p) {
		for (int i = 0; i < 4; ++i)
			ft[i][p - 1].assign(p, FenwickTree((N+p-1)/p));
		for (int j = 0; j < N; ++j)
			ft[id[j]][p - 1][j % p].update(1 + j / p, 1);
	}
	
	int Q;
	cin >> Q;
	while (Q--) {
		int t;
		cin >> t;
		if (t == 1) {
			int pos; char c; cin >> pos >> c; --pos;
			int o = id[pos];
			int n = id[pos] = cm(c);
			for (int p = 1; p <= 10; ++p) {
				ft[o][p - 1][pos % p].update(1 + pos / p, -1);
				ft[n][p - 1][pos % p].update(1 + pos / p,  1);
			}
		} else {
			int l, r; string t; cin >> l >> r >> t; --l; --r;
			int len = (int)t.length(), ans = 0;
			int lmod = l % len, rmod = r % len;
//cerr << "Querying " << t << " on [" << l << ',' << r << "], classes " << lmod << " and " << rmod << endl;
			for (int i = 0; i < len; ++i) {
				int v = cm(t[i]);
				int modclass = (l + i) % len;
//cerr << " Character at position " << i << " is in modclass " << modclass << endl;
				
				int lq = l / len; if (modclass < lmod) ++lq;
				int rq = r / len; if (modclass > rmod) --rq;
//cerr << " Querying for [" << lq << ',' << rq << ']' << endl;
				
				if (lq <= rq)
					ans += ft[v][len - 1][modclass]
						.query(lq + 1, rq + 1);
			}
			cout << ans << '\n';
		}
	}
	
	return 0;
}
