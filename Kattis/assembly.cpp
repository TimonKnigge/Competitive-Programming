#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int map(char c, char t) {
	if (c == '0' && t == '0') return -1;
	return (t == '+' ? 0 : 26) + (c - 'A');
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	scanf("%d", &n);
	vector<vector<bool>> ch(52, vector<bool>(52, false));
	for (int i = 0; i < n; ++i) {
		int v[4];
		for (int j = 0; j < 4; ++j) {
			char l, r;
			scanf(" %c", &l);
			scanf(" %c", &r);
			v[j] = map(l, r);
			if (v[j] == -1) continue;
			for (int k = 0; k < j; ++k) {
				if (v[k] == -1) continue;
				ch[v[j]][(v[k] + 26) % 52] = true;
				ch[v[k]][(v[j] + 26) % 52] = true;
			}
		}
	}
	
	for (int b = 0; b < 52; ++b)
		for (int c = 0; c < 52; ++c)
			for (int a = 0; a < 52; ++a)
				ch[c][a] = ch[c][a] || (ch[c][b] && ch[b][a]);

	bool unb = false;
	for (int i = 0; i < 52; ++i) {
		unb = unb || ch[i][i];
	}

	printf(unb ? "unbounded\n" : "bounded\n");
	
	return 0;
}
