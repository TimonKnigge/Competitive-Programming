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

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int m, n;
	cin >> m >> n;
	
	vector<vb> p(26, vb(26, false));
	while (m--) {
		char a, b;
		cin >> a >> b;
		p[a-'a'][b-'a'] = true;
	}
	for (int i = 0; i < 26; ++i) {
		p[i][i] = true;
		queue<int> q;
		for (int j = 0; j < 26; ++j) if (p[i][j]) q.push(j);
		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (int v = 0; v < 26; ++v) {
				if (p[u][v] && !p[i][v]) {
					q.push(v);
					p[i][v] = true;
				}
			}
		}
	}
	
	while (n--) {
		string a, b;
		cin >> a >> b;
		bool ps = a.length() == b.length();
		for (size_t i = 0; i < a.length() && ps; ++i) {
			ps = ps && p[a[i]-'a'][b[i]-'a'];
		}
		cout << (ps?"yes":"no") << endl;
	}
	
	return 0;
}
