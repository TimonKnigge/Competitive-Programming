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
	
	vvi cyc;
	while (n > 4) {
		int a = n - 1, b = n - 2;
		n -= 2;
		int m = n;
		while (m > 2) {
			int c = m - 1, d = m - 2;
			m -= 2;
			cyc.push_back({a, c, b, d});
			cyc.push_back({a, c, b, d});
		}
		if (m == 1) {
			cyc.push_back({0, a, b});
			cyc.push_back({0, a, b});
		} else {
			cyc.push_back({0, a, 1, b});
			cyc.push_back({0, a, b});
			cyc.push_back({1, a, b});
		}
	}
	if (n == 4) {
		cyc.push_back({0, 1, 2, 3});
		cyc.push_back({0, 1, 3, 2});
		cyc.push_back({0, 2, 1, 3});
	} else {
		cyc.push_back({0, 1, 2});
		cyc.push_back({0, 1, 2});
	}

	cout << cyc.size() << endl;
	for (vi &c : cyc) {
		cout << c.size();
		for (ll v : c) cout << ' ' << v+1;
		cout << '\n';
	}
	
	return 0;
}
