#include <iostream>
#include <string>

using namespace std;

int main() {
	int n, m;
	cin >> n >> m;
	
	string s;
	cin >> s;

	bool f = false;
	int ans = 0;
	for (int i = 0; i < n; ++i) {
		if (s[i] == '.') {
			if (f) ans++;
			f = true;
		} else f = false;
	}

	for (int i = 0; i < m; ++i) {
		int id; char c;
		cin >> id >> c;
		id--;
		if ((s[id] == '.' && c == '.')
		 || (s[id] != '.' && c != '.')) {
			cout << ans << '\n';
			continue;
		}
		bool ld = (id > 0 && s[id - 1] == '.');
		bool rd = (id < n - 1 && s[id + 1] == '.');
		
		ans += ((ld ? 1 : 0) + (rd ? 1 : 0)) * (c == '.' ? 1 : -1);
		s[id] = c;

		cout << ans << '\n';
	}
	cout << flush;

	return 0;
}
