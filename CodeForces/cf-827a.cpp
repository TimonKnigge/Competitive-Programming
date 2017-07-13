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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;

	int L = 0;
	vector<string> t(n, "");
	vvi pos(n, vi());
	for (int i = 0; i < n; ++i) {
		int k;
		cin >> t[i] >> k;
		pos[i].resize(k);
		for (int j = 0; j < k; ++j) {
			cin >> pos[i][j];
			--pos[i][j];
			L = max(L, (int)pos[i][j] + (int)t[i].length());
		}
	}

	string res(L, ' ');
	set<int> free;
	for (int i = 0; i < L; ++i) free.insert(i);
	for (int i = 0; i < n && !free.empty(); ++i) {
		int l = (int)t[i].length();
		for (int p : pos[i]) {
			while (true) {
				auto it = free.lower_bound(p);
				if (it == free.end()) break;
				int j = *it;
				if (p + l <= j) break;
				res[j] = t[i][j - p];
				free.erase(it);
			}
		}
	}
	for (int i : free) res[i] = 'a';
	
	cout << res << endl;
	
	return 0;
}
