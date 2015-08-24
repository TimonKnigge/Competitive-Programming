#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <stack>

using namespace std;

//  3
// 1256
//  4
struct die {
	int v1, v2, v3, v4, v5, v6;
	die(int const &v1, int const &v2, int const &v3, 
	    int const &v4, int const &v5, int const &v6)
		: v1(v1), v2(v2), v3(v3), v4(v4), v5(v5), v6(v6) { }
};
bool operator<(die const &l, die const &r) { 
	if (l.v1 != r.v1) return l.v1 < r.v1;
	if (l.v2 != r.v2) return l.v2 < r.v2;
	if (l.v3 != r.v3) return l.v3 < r.v3;
	if (l.v4 != r.v4) return l.v4 < r.v4;
	if (l.v5 != r.v5) return l.v5 < r.v5;
	return l.v6 < r.v6;
}
die left(die const &d, int const &nt) {
	return die(d.v2, nt, d.v3, d.v4, d.v6, d.v1); }
die right(die const &d, int const &nt) {
	return die(d.v6, nt, d.v3, d.v4, d.v2, d.v5); }
die up(die const &d, int const &nt) {
	return die(d.v1, nt, d.v2, d.v6, d.v5, d.v3); }
die down(die const &d, int const &nt) {
	return die(d.v1, nt, d.v6, d.v2, d.v5, d.v4); }

#define STACK

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int m, n;
	cin >> m >> n;
	int b[101][101];
	for (int j = 0; j < m; ++j) {
		for (int i = 0; i < n; ++i) {
			cin >> b[i][j];
		}
	}

	if (n == 1 && m == 1) { cout << "YES" << endl; return 0; }

#ifdef STACK
	stack<pair<pair<int, int>, die> > q;
#else
	queue<pair<pair<int, int>, die> > q;
#endif
	set<pair<pair<int, int>, die> > mp;
	mp.insert({{0, 0}, die(-1, b[0][0], -1, -1, -1, -1)});
	q.push({{0, 0}, die(-1, b[0][0], -1, -1, -1, -1)});
	int i, j; die d(0,0,0,0,0,0); bool pos = false;
	while (!q.empty()) {
#ifdef STACK
		i = q.top().first.first;
		j = q.top().first.second;
		d = q.top().second;
#else
		i = q.front().first.first;
		j = q.front().first.second;
		d = q.front().second
#endif
		q.pop();

//		cout << i << ' ' << j << ' ' << d << endl;

		//  3
		// 1256
		//  4

		// move left/right/up/down
		if (i < n - 1 && (b[i + 1][j] == d.v1 || d.v1 == -1)) {
			if (i + 1 == n - 1 && j == m - 1) {
				pos = true;
				break;
			}
			pair<pair<int, int>, die> nw
			 = {{i + 1, j}, right(d, b[i + 1][j])};
			if (mp.insert(nw).second)
				q.push(nw);
		}
		if (i > 0 && (b[i - 1][j] == d.v5 || d.v5 == -1)) {
			pair<pair<int, int>, die> nw
			 = {{i - 1, j}, left(d, b[i - 1][j])};
			if (mp.insert(nw).second)
				q.push(nw);
		}
		if (j > 0 && (b[i][j - 1] == d.v4 || d.v4 == -1)) {
			pair<pair<int, int>, die> nw
			 = {{i, j - 1}, up(d, b[i][j - 1])};
			if (mp.insert(nw).second)
				q.push(nw);
		}
		if (j < m - 1 && (b[i][j + 1] == d.v3 || d.v3 == -1)) {
			if (i == n - 1 && j + 1 == m - 1) {
				pos = true;
				break;
			}
			pair<pair<int, int>, die> nw
			 = {{i, j + 1}, down(d, b[i][j + 1])};
			if (mp.insert(nw).second)
				q.push(nw);
		}
	}

	cout << (pos ? "YES" : "NO") << endl;
	
	return 0;
}
